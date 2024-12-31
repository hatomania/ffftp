#ifndef LIBFFFTP_USE_WIN32API

#ifdef LIBFFFTP_OTHER
static inline std::unique_ptr<addrinfo> getaddrinfo(std::wstring const& host, std::wstring const& port, int family = AF_UNSPEC, int flags = AI_NUMERICHOST | AI_NUMERICSERV) noexcept;
static std::unique_ptr<addrinfo> getaddrinfo(std::wstring const& host, std::wstring const& port, int family, int* CancelCheckWork);
#else  // LIBFFFTP_OTHER

#ifndef LIBFFFTP_DECL
#include <QString>

static inline std::unique_ptr<addrinfo> getaddrinfo(std::wstring const& host, std::wstring const& port, int family, int flags) noexcept {
  // ワイド文字列版getaddrinfoはC標準にはないと思うのでC標準のgetaddrinfoを使うようにする
  std::string chost = QString::fromWCharArray(host.c_str()).toStdString();
  std::string cport = QString::fromWCharArray(port.c_str()).toStdString();
  if (addrinfo hint{ flags, family }, *ai; getaddrinfo(chost.c_str(), cport.c_str(), &hint, &ai) == 0) {
    assert(family == AF_INET || family == AF_INET6 ? ai->ai_family == family : true);
    assert(ai->ai_family == AF_INET && ai->ai_addrlen == sizeof(sockaddr_in) || ai->ai_family == AF_INET6 && ai->ai_addrlen == sizeof(sockaddr_in6));
    assert(ai->ai_addr->sa_family == ai->ai_family);
    return std::unique_ptr<addrinfo>{ ai };
  }
  return std::unique_ptr<addrinfo>{};
}

static std::unique_ptr<addrinfo> getaddrinfo(std::wstring const& host, std::wstring const& port, int family, int* CancelCheckWork) {
  auto future = std::async(std::launch::async, [host, port, family] { return getaddrinfo(IdnToAscii(host), port, family, AI_NUMERICSERV);	});
  while (*CancelCheckWork == NO && future.wait_for(1ms) == std::future_status::timeout)
    if (BackgrndMessageProc() == YES)
      *CancelCheckWork = YES;
  if (*CancelCheckWork == YES)
    return {};
  return future.get();
}

/**
 * @param originalTarget FireWall使用を問わず、FTPサーバの接続先ホスト
 * @param host FireWallを使用しない場合、またはFireWallを使用する場合でもSOCKS4,SOCKS5サーバを使用する場合はFTPサーバの接続先ホスト、FireWallを使用する場合でSOCKS4,SOCKS5サーバ以外を使用する場合はFireWallサーバの接続先ホスト
 * @param port FireWallを使用しない場合、またはFireWallを使用する場合でもSOCKS4,SOCKS5サーバを使用する場合はFTPサーバの接続先ポート、FireWallを使用する場合でSOCKS4,SOCKS5サーバ以外を使用する場合はFireWallサーバの接続先ポート
 */
std::shared_ptr<SocketContext> connectsock(std::variant<std::wstring_view, std::reference_wrapper<const SocketContext>> originalTarget, std::wstring&& host, int port, int *CancelCheckWork) {
  std::variant<sockaddr_storage, std::tuple<std::wstring, int>> target;
  int const Fwall = CurHost.FireWall == YES ? FwallType : FWALL_NONE;
  if (auto ai = getaddrinfo(host, port, Fwall == FWALL_SOCKS4 ? AF_INET : AF_UNSPEC)) {
    // ホスト名がIPアドレスだった
    Notice(IDS_MSGJPN017, host, AddressPortToString(ai->ai_addr, ai->ai_addrlen));
    memcpy(&std::get<sockaddr_storage>(target), ai->ai_addr, ai->ai_addrlen);
  } else if ((Fwall == FWALL_SOCKS5_NOAUTH || Fwall == FWALL_SOCKS5_USER) && FwallResolve == YES) {
    // SOCKS5で名前解決する
    target = std::tuple{ std::move(host), port };
  } else if (ai = getaddrinfo(host, port, Fwall == FWALL_SOCKS4 ? AF_INET : AF_UNSPEC, CancelCheckWork)) {
    // 名前解決に成功
    Notice(IDS_MSGJPN017, host, AddressPortToString(ai->ai_addr, ai->ai_addrlen));
    memcpy(&std::get<sockaddr_storage>(target), ai->ai_addr, ai->ai_addrlen);
  } else {
    // 名前解決に失敗
    Notice(IDS_MSGJPN019, host);
    return {};
  }
  // target変数の中身
  // FireWall =  NO       : FTPサーバの情報
  // FireWall =  SOCKS4,5 : FTPサーバの情報
  // FireWall = !SOCKS4,5 : FireWallサーバの情報

  sockaddr_storage saConnect;
  if (Fwall == FWALL_SOCKS4 || Fwall == FWALL_SOCKS5_NOAUTH || Fwall == FWALL_SOCKS5_USER) {
    // connectで接続する先はSOCKSサーバ
    auto ai = getaddrinfo(FwallHost, FwallPort);
    if (!ai)
      ai = getaddrinfo(FwallHost, FwallPort, AF_UNSPEC, CancelCheckWork);
    if (!ai) {
      Notice(IDS_MSGJPN021, FwallHost);
      return {};
    }
    memcpy(&saConnect, ai->ai_addr, ai->ai_addrlen);
    Notice(IDS_MSGJPN022, AddressPortToString(ai->ai_addr, ai->ai_addrlen));
  } else {
    // connectで接続するのは接続先のホスト
    saConnect = std::get<sockaddr_storage>(target);
  }
  // saConnect変数の中身
  // FireWall =  NO       : FTPサーバの情報
  // FireWall =  SOCKS4,5 : FireWallサーバの情報
  // FireWall = !SOCKS4,5 : FireWallサーバの情報

  auto s = SocketContext::Create(originalTarget);
  if (!s) {
    Notice(IDS_MSGJPN027);
    return {};
  }
  s->target = target;
  int err{s->Connect(reinterpret_cast<const sockaddr*>(&saConnect), sizeof saConnect, Fwall, CancelCheckWork)};
  if (err == SOCKET_ERROR) {
    Notice(IDS_MSGJPN026);
    return {};
  } else if (err == SOCKET_PROXY_ERROR) {
    Notice(IDS_MSGJPN023);
    return {};
  }
  const QAbstractSocket::NetworkLayerProtocol proto{s->socket->peerAddress().protocol()};
  CurHost.CurNetType = proto == QAbstractSocket::IPv4Protocol ? NTYPE_IPV4 : NTYPE_IPV6;
  Notice(IDS_MSGJPN025);
  return s;
}


// リッスンソケットを取得
std::shared_ptr<SocketContext> GetFTPListenSocket(std::shared_ptr<SocketContext> ctrl_skt, int *CancelCheckWork) {
  //sockaddr_storage saListen;
  //int salen = sizeof saListen;
  //if (getsockname(ctrl_skt->handle, reinterpret_cast<sockaddr*>(&saListen), &salen) == SOCKET_ERROR) {
  //  WSAError(L"getsockname()"sv);
  //  return {};
  //}
  //auto listen_skt = SocketContext::Create(*ctrl_skt);
  //if (!listen_skt)
  //  return {};
  //if (CurHost.FireWall == YES && (FwallType == FWALL_SOCKS4 || FwallType == FWALL_SOCKS5_NOAUTH || FwallType == FWALL_SOCKS5_USER)) {
  //  Debug(L"Use SOCKS BIND."sv);
  //  // Control接続と同じアドレスに接続する
  //  salen = sizeof saListen;
  //  if (getpeername(ctrl_skt->handle, reinterpret_cast<sockaddr*>(&saListen), &salen) == SOCKET_ERROR) {
  //    WSAError(L"getpeername()"sv);
  //    return {};
  //  }
  //  if (listen_skt->Connect(reinterpret_cast<const sockaddr*>(&saListen), salen, CancelCheckWork) == SOCKET_ERROR) {
  //    return {};
  //  }
  //  if (auto result = SocksRequest(*listen_skt, SocksCommand::Bind, ctrl_skt->target, CancelCheckWork)) {
  //    saListen = *result;
  //  } else {
  //    Notice(IDS_MSGJPN023);
  //    return {};
  //  }
  //} else {
  //  Debug(L"Use normal BIND."sv);
  //  // Control接続と同じアドレス（ただしport=0）でlistenする
  //  if (saListen.ss_family == AF_INET)
  //    reinterpret_cast<sockaddr_in&>(saListen).sin_port = 0;
  //  else
  //    reinterpret_cast<sockaddr_in6&>(saListen).sin6_port = 0;
  //  if (bind(listen_skt->handle, reinterpret_cast<const sockaddr*>(&saListen), salen) == SOCKET_ERROR) {
  //    WSAError(L"bind()"sv);
  //    Notice(IDS_MSGJPN027);
  //    return {};
  //  }
  //  salen = sizeof saListen;
  //  if (getsockname(listen_skt->handle, reinterpret_cast<sockaddr*>(&saListen), &salen) == SOCKET_ERROR) {
  //    WSAError(L"getsockname()"sv);
  //    Notice(IDS_MSGJPN027);
  //    return {};
  //  }
  //  if (listen_skt->Listen(1) != 0) {
  //    WSAError(L"listen()"sv);
  //    Notice(IDS_MSGJPN027);
  //    return {};
  //  }
  //  // TODO: IPv6にUPnP NATは無意味なのでは？
  //  if (IsUPnPLoaded() == YES && UPnPEnabled == YES) {
  //    auto const port = ntohs(saListen.ss_family == AF_INET ? reinterpret_cast<sockaddr_in const&>(saListen).sin_port : reinterpret_cast<sockaddr_in6 const&>(saListen).sin6_port);
  //    // TODO: UPnP NATで外部アドレスだけ参照しているが、外部ポートが内部ポートと異なる可能性が十分にあるのでは？
  //    if (auto const ExtAdrs = AddPortMapping(AddressToString(saListen), port))
  //      if (auto ai = getaddrinfo(*ExtAdrs, port)) {
  //        memcpy(&saListen, ai->ai_addr, ai->ai_addrlen);
  //        listen_skt->mapPort = port;
  //      }
  //  }
  //}
  //int status;
  //if (saListen.ss_family == AF_INET) {
  //  auto const& sin = reinterpret_cast<sockaddr_in const&>(saListen);
  //  auto a = reinterpret_cast<const uint8_t*>(&sin.sin_addr), p = reinterpret_cast<const uint8_t*>(&sin.sin_port);
  //  status = std::get<0>(Command(ctrl_skt, CancelCheckWork, L"PORT {},{},{},{},{},{}"sv, a[0], a[1], a[2], a[3], p[0], p[1]));
  //} else {
  //  auto a = AddressToString(saListen);
  //  auto const p = reinterpret_cast<sockaddr_in6 const&>(saListen).sin6_port;
  //  status = std::get<0>(Command(ctrl_skt, CancelCheckWork, L"EPRT |2|{}|{}|"sv, a, ntohs(p)));
  //}
  //if (status / 100 != FTP_COMPLETE) {
  //  Notice(IDS_MSGJPN031, saListen.ss_family == AF_INET ? L"PORT"sv : L"EPRT"sv);
  //  if (IsUPnPLoaded() == YES)
  //    RemovePortMapping(listen_skt->mapPort);
  //  return {};
  //}
  //return listen_skt;
  return {};
}

#endif  // LIBFFFTP_DECL
#endif  // LIBFFFTP_OTHER
#endif  // LIBFFFTP_USE_WIN32API
