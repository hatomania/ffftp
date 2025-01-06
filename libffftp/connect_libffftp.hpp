//--------------------------------------------------------------------------------------------------
#ifdef LIBFFFTP_INCLUDE_CONNECT_DirectConnectProc
void DirectConnectProc(std::wstring&& unc, int Kanji, int Kana, int Fkanji, int TrMode) {
  std::wstring Host;
  std::wstring Path;
  std::wstring File;
  std::wstring User;
  std::wstring Pass;
  int Port;

  SaveBookMark();
  SaveCurrentSetToHost();

  /* 接続中なら切断する */
  if (CmdCtrlSocket)
    DisconnectProc();

  Notice(IDS_SEPARATOR);

  InitPWDcommand();
  if (SplitUNCpath(std::move(unc), Host, Path, File, User, Pass, Port)) {
    if (empty(User)) {
      User = L"anonymous"s;
      Pass = UserMailAdrs;
    }

    CopyDefaultHost(&CurHost);

    SetCurrentHost(HOSTNUM_NOENTRY);
    CurHost.HostAdrs = std::move(Host);
    CurHost.UserName = std::move(User);
    CurHost.PassWord = std::move(Pass);
    CurHost.RemoteInitDir = std::move(Path);
    AskUseFireWall(CurHost.HostAdrs, &CurHost.FireWall, &CurHost.Pasv, &CurHost.ListCmdOnly);
    CurHost.Port = Port;
    CurHost.KanjiCode = Kanji;
    CurHost.KanaCnv = Kana;
    CurHost.NameKanjiCode = Fkanji;
    CurHost.KanaCnv = YES;			/* とりあえず */
    // UTF-8対応
    CurHost.CurNameKanjiCode = CurHost.NameKanjiCode;

    SetHostKanaCnvImm(CurHost.KanaCnv);
    SetHostKanjiCodeImm(CurHost.KanjiCode);
    SetSyncMoveMode(CurHost.SyncMove);

    if(TrMode != TYPE_DEFAULT)
    {
      SetTransferTypeImm(TrMode);
      DispTransferType();
    }

//    DisableUserOpe();
    CmdCtrlSocket = DoConnect(&CurHost, CurHost.HostAdrs, CurHost.UserName, CurHost.PassWord, CurHost.Account, CurHost.Port, CurHost.FireWall, NO, CurHost.Security, &CancelFlg);
    TrnCtrlSocket = CmdCtrlSocket;

    if (CmdCtrlSocket) {
      TitleHostName = CurHost.HostAdrs;
      DispWindowTitle();
      UpdateStatusBar();
      Sound::Connected.Play();

      InitTransCurDir();
      DoCWD(CurHost.RemoteInitDir, YES, YES, YES);

      GetRemoteDirForWnd(CACHE_NORMAL, &CancelFlg);
//      EnableUserOpe();

      if (!empty(File))
        DirectDownloadProc(File);
      else
        ResetAutoExitFlg();
    }
    else
    {
      Sound::Error.Play();
//      EnableUserOpe();
    }
  }
  return;
}
#endif  // LIBFFFTP_INCLUDE_CONNECT_DirectConnectProc


//--------------------------------------------------------------------------------------------------
#ifdef LIBFFFTP_INCLUDE_CONNECT_DoConnectCrypt
static std::shared_ptr<SocketContext> DoConnectCrypt(int CryptMode, HOSTDATA* HostData, std::wstring const& Host, std::wstring& User, std::wstring& Pass, std::wstring& Acct, int Port, int Fwall, int SavePass, int Security, int *CancelCheckWork)
{
  int Sts;
  int Flg;
  int Anony;
  std::shared_ptr<SocketContext> ContSock;
  int Continue;
  int ReInPass;
  constexpr std::wstring_view SiteTbl[] = { L"SITE"sv, L"site"sv, L"OPEN"sv, L"open"sv };
  struct linger LingerOpt;
  struct tcp_keepalive KeepAlive;
  DWORD dwTmp;

  if(CryptMode == CRYPT_NONE || CryptMode == CRYPT_FTPES || CryptMode == CRYPT_FTPIS)
  {
    if(Fwall == YES)
      Fwall = FwallType;
    else
      Fwall = FWALL_NONE;

    TryConnect = YES;
    // 暗号化通信対応
//		CancelFlg = NO;
#if 0
//		WSASetBlockingHook(BlkHookFnc);
#endif

    auto [tempHost, tempPort] = FWALL_FU_FP_SITE <= Fwall && Fwall <= FWALL_OPEN || Fwall == FWALL_SIDEWINDER || Fwall == FWALL_FU_FP ? std::tuple{ FwallHost, FwallPort } : std::tuple{ Host, Port };
    if (!empty(tempHost)) {
      if (ContSock = connectsock(Host, std::move(tempHost), tempPort, CancelCheckWork)) {
        // バッファを無効
#ifdef DISABLE_CONTROL_NETWORK_BUFFERS
        constexpr int BufferSize = 0;
        setsockopt(ContSock->handle, SOL_SOCKET, SO_SNDBUF, (char*)&BufferSize, sizeof(int));
        setsockopt(ContSock->handle, SOL_SOCKET, SO_RCVBUF, (char*)&BufferSize, sizeof(int));
#endif
        if(CryptMode == CRYPT_FTPIS)
        {
          ContSock->socket->startClientEncryption();
          if (ContSock->socket->waitForEncrypted()) {
            QString r{ContSock->socket->receiveMessage()};
            Debug(L"Recv: {}", r.toStdWString());
            Sts = r.front().digitValue();
          } else {
            Sts = FTP_ERROR;
          }
          //if (ContSock->AttachSSL(CancelCheckWork)) {
          //  while((Sts = std::get<0>(ContSock->ReadReply(CancelCheckWork)) / 100) == FTP_PRELIM)
          //    ;
          //}
          //else
          //  Sts = FTP_ERROR;
        }
        else
        {
            QString r{ContSock->socket->receiveMessage()};
            Debug(L"Recv: {}", r.toStdWString());
            Sts = r.front().digitValue();
          //while((Sts = std::get<0>(ContSock->ReadReply(CancelCheckWork)) / 100) == FTP_PRELIM)
          //  ;
        }

        if(Sts == FTP_COMPLETE)
        {
          Flg = 1;
          if(setsockopt(ContSock->handle, SOL_SOCKET, SO_OOBINLINE, (LPSTR)&Flg, sizeof(Flg)) == SOCKET_ERROR)
            WSAError(L"setsockopt(SOL_SOCKET, SO_OOBINLINE)"sv);
          // データ転送用ソケットのTCP遅延転送が無効されているので念のため
          if(setsockopt(ContSock->handle, IPPROTO_TCP, TCP_NODELAY, (LPSTR)&Flg, sizeof(Flg)) == SOCKET_ERROR)
            WSAError(L"setsockopt(IPPROTO_TCP, TCP_NODELAY)"sv);
//#pragma aaa
          Flg = 1;
          if(setsockopt(ContSock->handle, SOL_SOCKET, SO_KEEPALIVE, (LPSTR)&Flg, sizeof(Flg)) == SOCKET_ERROR)
            WSAError(L"setsockopt(SOL_SOCKET, SO_KEEPALIVE)"sv);
          // 切断対策
          if(TimeOut > 0)
          {
            KeepAlive.onoff = 1;
            KeepAlive.keepalivetime = TimeOut * 1000;
            KeepAlive.keepaliveinterval = 1000;
            if(WSAIoctl(ContSock->handle, SIO_KEEPALIVE_VALS, &KeepAlive, sizeof(struct tcp_keepalive), NULL, 0, &dwTmp, NULL, NULL) == SOCKET_ERROR)
              WSAError(L"WSAIoctl(SIO_KEEPALIVE_VALS)"sv);
          }
          LingerOpt.l_onoff = 1;
          LingerOpt.l_linger = 90;
          if(setsockopt(ContSock->handle, SOL_SOCKET, SO_LINGER, (LPSTR)&LingerOpt, sizeof(LingerOpt)) == SOCKET_ERROR)
            WSAError(L"setsockopt(SOL_SOCKET, SO_LINGER)"sv);
///////


          /*===== 認証を行なう =====*/

          Sts = FTP_COMPLETE;
          if((Fwall == FWALL_FU_FP_SITE) ||
             (Fwall == FWALL_FU_FP_USER) ||
             (Fwall == FWALL_FU_FP))
          {
            if (auto [code, text] = Command(ContSock, CancelCheckWork, L"USER {}"sv, FwallUser); (Sts = code / 100) == FTP_CONTINUE) {
              auto const pass = CheckOneTimePassword(std::wstring{ FwallPass }, text, FwallSecurity);
              Sts = std::get<0>(Command(ContSock, CancelCheckWork, L"PASS {}"sv, pass)) / 100;
            }
          }
          else if(Fwall == FWALL_SIDEWINDER)
          {
            Sts = std::get<0>(Command(ContSock, CancelCheckWork, L"USER {}:{}{}{}"sv, FwallUser, FwallPass, (wchar_t)FwallDelimiter, Host)) / 100;
          }
          if((Sts != FTP_COMPLETE) && (Sts != FTP_CONTINUE))
          {
            Notice(IDS_MSGJPN006);
            ContSock.reset();
          }
          else
          {
            if((Fwall == FWALL_FU_FP_SITE) || (Fwall == FWALL_OPEN))
            {
              int const index = (Fwall == FWALL_OPEN ? 2 : 0) | (FwallLower == YES ? 1 : 0);
              auto const format = Port == IPPORT_FTP ? L"{} {}"sv : L"{} {} {}"sv;
              Sts = std::get<0>(Command(ContSock, CancelCheckWork, format, SiteTbl[index], Host)) / 100;
            }

            if((Sts != FTP_COMPLETE) && (Sts != FTP_CONTINUE))
            {
              Notice(IDS_MSGJPN007, Host);
              ContSock.reset();
            }
            else
            {
              Anony = NO;
              if (empty(User) && HostData->NoDisplayUI == NO)
                InputDialog(username_dlg, GetMainHwnd(), 0, User, USER_NAME_LEN + 1, &Anony);
              if (!empty(User)) {
                if(Anony == YES)
                {
                  User = L"anonymous"s;
                  Pass = UserMailAdrs;
                }

                auto const user = Fwall != FWALL_FU_FP_USER && Fwall != FWALL_USER ? User : Port == IPPORT_FTP ? std::format(L"{}{}{}"sv, User, (wchar_t)FwallDelimiter, Host) : std::format(L"{}{}{} {}"sv, User, (wchar_t)FwallDelimiter, Host, Port);

                // FTPES対応
                if (CryptMode == CRYPT_FTPES) {
                  if ((Sts = std::get<0>(Command(ContSock, CancelCheckWork, L"AUTH TLS"sv))) != 234 && (Sts = std::get<0>(Command(ContSock, CancelCheckWork, L"AUTH SSL"sv))) != 234)
                    Sts = FTP_ERROR;
                  else if (!ContSock->AttachSSL(CancelCheckWork))
                    Sts = FTP_ERROR;
                  else if ((Sts = std::get<0>(Command(ContSock, CancelCheckWork, L"PBSZ 0"sv))) != 200)
                    Sts = FTP_ERROR;
                  else if ((Sts = std::get<0>(Command(ContSock, CancelCheckWork, L"PROT P"sv))) != 200)
                    Sts = FTP_ERROR;
                }

                // FTPIS対応
                if (CryptMode == CRYPT_FTPIS) {
                  // "PBSZ 0"と"PROT P"は黙示的に設定されているはずだが念のため
                  if ((Sts = std::get<0>(Command(ContSock, CancelCheckWork, L"PBSZ 0"sv))) == 200)
                    Sts = std::get<0>(Command(ContSock, CancelCheckWork, L"PROT P"sv));
                }

                ReInPass = NO;
                do
                {
                  // FTPES対応
                  if(Sts == FTP_ERROR)
                    break;
                  Continue = NO;
                  if (auto [code, text] = Command(ContSock, CancelCheckWork, L"USER {}"sv, user); (Sts = code / 100) == FTP_CONTINUE)
                  {
                    if (empty(Pass) && HostData->NoDisplayUI == NO)
                      InputDialog(passwd_dlg, GetMainHwnd(), 0, Pass, PASSWORD_LEN + 1);
                    if (!empty(Pass)) {
                      auto pass = CheckOneTimePassword(std::wstring{ Pass }, text, Security);

                      /* パスワードがスペース1個の時はパスワードの実体なしとする */
                      if (pass == L" "sv)
                        pass = L""s;
                      Sts = std::get<0>(Command(ContSock, CancelCheckWork, L"PASS {}"sv, pass)) / 100;
                      if(Sts == FTP_ERROR)
                      {
                        if (HostData->NoDisplayUI == NO && InputDialog(re_passwd_dlg, GetMainHwnd(), 0, Pass, PASSWORD_LEN + 1))
                          Continue = YES;
                        else {
                          Pass.clear();
                          Debug(L"No password specified."sv);
                        }
                        ReInPass = YES;
                      }
                      else if(Sts == FTP_CONTINUE)
                      {
                        if (empty(Acct) && HostData->NoDisplayUI == NO)
                          InputDialog(account_dlg, GetMainHwnd(), 0, Acct, ACCOUNT_LEN + 1);
                        if (!empty(Acct))
                          Sts = std::get<0>(Command(ContSock, CancelCheckWork, L"ACCT {}", Acct)) / 100;
                        else
                          Debug(L"No account specified."sv);
                      }
                    }
                    else
                    {
                      Sts = FTP_ERROR;
                      Debug(L"No password specified."sv);
                    }
                  }
                  // FTPES対応
                  if(Continue == YES)
                    Sts = FTP_COMPLETE;
                }
                while(Continue == YES);
              }
              else
              {
                Sts = FTP_ERROR;
                Debug(L"No user name specified."sv);
              }

              if(Sts != FTP_COMPLETE)
              {
                Notice(IDS_MSGJPN008);
                ContSock.reset();
              }
              else if((SavePass == YES) && (ReInPass == YES))
              {
                if (HostData->NoDisplayUI == NO && Dialog(GetFtpInst(), savepass_dlg, GetMainHwnd()))
                  SetHostPassword(AskCurrentHost(), Pass);
              }
            }
          }
        }
        else
        {
        Notice(IDS_MSGJPN009);
          ContSock.reset();
        }
      }
    }
    else
    {

      if(((Fwall >= FWALL_FU_FP_SITE) && (Fwall <= FWALL_OPEN)) ||
         (Fwall == FWALL_FU_FP))
        Notice(IDS_MSGJPN010);
      else
        Notice(IDS_MSGJPN011);
    }

#if 0
//		WSAUnhookBlockingHook();
#endif
    TryConnect = NO;

    // FEAT対応
    // ホストの機能を確認
    if (ContSock) {
      if (auto [code, text] = Command(ContSock, CancelCheckWork, L"FEAT"sv); code == 211) {
        // 改行文字はReadReplyで消去されるため区切り文字に空白を使用
        if (text.find(L" UTF8 "sv) != std::wstring::npos)
          HostData->Feature |= FEATURE_UTF8;
        if (text.find(L" MLST "sv) != std::wstring::npos || text.find(L" MLSD "sv) != std::wstring::npos)
          HostData->Feature |= FEATURE_MLSD;
        if (text.find(L" EPRT "sv) != std::wstring::npos || text.find(L" EPSV "sv) != std::wstring::npos)
          HostData->Feature |= FEATURE_EPRT | FEATURE_EPSV;
        if (text.find(L" MDTM "sv) != std::wstring::npos)
          HostData->Feature |= FEATURE_MDTM;
        if (text.find(L" MFMT "sv) != std::wstring::npos)
          HostData->Feature |= FEATURE_MFMT;
      }
      if (HostData->CurNameKanjiCode == KANJI_AUTO && (HostData->Feature & FEATURE_UTF8))
        Command(ContSock, CancelCheckWork, L"OPTS UTF8 ON"sv);
    }
  }

  return(ContSock);
}
#endif  // LIBFFFTP_INCLUDE_CONNECT_DoConnectCrypt


//--------------------------------------------------------------------------------------------------
#ifdef LIBFFFTP_INCLUDE_CONNECT_getaddrinfo1
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
#endif  // LIBFFFTP_INCLUDE_CONNECT_getaddrinfo1


//--------------------------------------------------------------------------------------------------
#ifdef LIBFFFTP_INCLUDE_CONNECT_getaddrinfo2
static std::unique_ptr<addrinfo> getaddrinfo(std::wstring const& host, std::wstring const& port, int family, int* CancelCheckWork) {
  auto future = std::async(std::launch::async, [host, port, family] { return getaddrinfo(IdnToAscii(host), port, family, AI_NUMERICSERV);	});
  while (*CancelCheckWork == NO && future.wait_for(1ms) == std::future_status::timeout)
    if (BackgrndMessageProc() == YES)
      *CancelCheckWork = YES;
  if (*CancelCheckWork == YES)
    return {};
  return future.get();
}
#endif  // LIBFFFTP_INCLUDE_CONNECT_getaddrinfo2


//--------------------------------------------------------------------------------------------------
#ifdef LIBFFFTP_INCLUDE_CONNECT_connectsock
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
#endif  // LIBFFFTP_INCLUDE_CONNECT_connectsock


//--------------------------------------------------------------------------------------------------
#ifdef LIBFFFTP_INCLUDE_CONNECT_GetFTPListenSocket
// TODO: この関数は未完成です。
std::shared_ptr<SocketContext> GetFTPListenSocket(std::shared_ptr<SocketContext> ctrl_skt, int *CancelCheckWork) {
  sockaddr_storage saListen;
  int salen = sizeof saListen;
  if (getsockname(ctrl_skt->handle, reinterpret_cast<sockaddr*>(&saListen), &salen) == SOCKET_ERROR) {
    WSAError(L"getsockname()"sv);
    return {};
  }
  auto listen_skt = SocketContext::Create(*ctrl_skt);
  if (!listen_skt)
    return {};
  if (CurHost.FireWall == YES && (FwallType == FWALL_SOCKS4 || FwallType == FWALL_SOCKS5_NOAUTH || FwallType == FWALL_SOCKS5_USER)) {
    Debug(L"Use SOCKS BIND."sv);
    // Control接続と同じアドレスに接続する
    salen = sizeof saListen;
    if (getpeername(ctrl_skt->handle, reinterpret_cast<sockaddr*>(&saListen), &salen) == SOCKET_ERROR) {
      WSAError(L"getpeername()"sv);
      return {};
    }
    if (listen_skt->Connect(reinterpret_cast<const sockaddr*>(&saListen), salen, FwallType, CancelCheckWork) == SOCKET_ERROR) {
      return {};
    }
    if (auto result = SocksRequest(*listen_skt, SocksCommand::Bind, ctrl_skt->target, CancelCheckWork)) {
      saListen = *result;
    } else {
      Notice(IDS_MSGJPN023);
      return {};
    }
  } else {
    Debug(L"Use normal BIND."sv);
    // Control接続と同じアドレス（ただしport=0）でlistenする
    if (saListen.ss_family == AF_INET)
      reinterpret_cast<sockaddr_in&>(saListen).sin_port = 0;
    else
      reinterpret_cast<sockaddr_in6&>(saListen).sin6_port = 0;
    if (bind(listen_skt->handle, reinterpret_cast<const sockaddr*>(&saListen), salen) == SOCKET_ERROR) {
      WSAError(L"bind()"sv);
      Notice(IDS_MSGJPN027);
      return {};
    }
    salen = sizeof saListen;
    if (getsockname(listen_skt->handle, reinterpret_cast<sockaddr*>(&saListen), &salen) == SOCKET_ERROR) {
      WSAError(L"getsockname()"sv);
      Notice(IDS_MSGJPN027);
      return {};
    }
    if (listen_skt->Listen(1) != 0) {
      WSAError(L"listen()"sv);
      Notice(IDS_MSGJPN027);
      return {};
    }
    // TODO: IPv6にUPnP NATは無意味なのでは？
    if (IsUPnPLoaded() == YES && UPnPEnabled == YES) {
      auto const port = ntohs(saListen.ss_family == AF_INET ? reinterpret_cast<sockaddr_in const&>(saListen).sin_port : reinterpret_cast<sockaddr_in6 const&>(saListen).sin6_port);
      // TODO: UPnP NATで外部アドレスだけ参照しているが、外部ポートが内部ポートと異なる可能性が十分にあるのでは？
      if (auto const ExtAdrs = AddPortMapping(AddressToString(saListen), port))
        if (auto ai = getaddrinfo(*ExtAdrs, port)) {
          memcpy(&saListen, ai->ai_addr, ai->ai_addrlen);
          listen_skt->mapPort = port;
        }
    }
  }
  int status;
  if (saListen.ss_family == AF_INET) {
    auto const& sin = reinterpret_cast<sockaddr_in const&>(saListen);
    auto a = reinterpret_cast<const uint8_t*>(&sin.sin_addr), p = reinterpret_cast<const uint8_t*>(&sin.sin_port);
    status = std::get<0>(Command(ctrl_skt, CancelCheckWork, L"PORT {},{},{},{},{},{}"sv, a[0], a[1], a[2], a[3], p[0], p[1]));
  } else {
    auto a = AddressToString(saListen);
    auto const p = reinterpret_cast<sockaddr_in6 const&>(saListen).sin6_port;
    status = std::get<0>(Command(ctrl_skt, CancelCheckWork, L"EPRT |2|{}|{}|"sv, a, ntohs(p)));
  }
  if (status / 100 != FTP_COMPLETE) {
    Notice(IDS_MSGJPN031, saListen.ss_family == AF_INET ? L"PORT"sv : L"EPRT"sv);
    if (IsUPnPLoaded() == YES)
      RemovePortMapping(listen_skt->mapPort);
    return {};
  }
  return listen_skt;
}
#endif  // LIBFFFTP_INCLUDE_CONNECT_GetFTPListenSocket
