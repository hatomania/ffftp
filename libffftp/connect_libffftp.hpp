#ifndef LIBFFFTP_USE_WIN32API

#ifdef LIBFFFTP_OTHER
namespace std {
  template<>
  struct default_delete<addrinfo> {
    void operator()(addrinfo* ai) const noexcept {
      freeaddrinfo(ai);
    }
  };
}
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
#endif  // LIBFFFTP_DECL

#endif  // LIBFFFTP_OTHER

#endif  // LIBFFFTP_USE_WIN32API
