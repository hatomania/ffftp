#ifdef LIBFFFTP_INCLUDE_COMMON
#include <QString>
#include <QTimeZone>
#include "ffftp_common.h"

extern void initSettings();
#endif


//--------------------------------------------------------------------------------------------------
#ifdef LIBFFFTP_INCLUDE_COMMON_DefaultTimeZone
    static inline int DefaultTimeZone{static_cast<int>(-(QTimeZone::systemTimeZone().offsetFromUtc(QDateTime()) / 60))};
#endif


//--------------------------------------------------------------------------------------------------
#ifdef LIBFFFTP_INCLUDE_COMMON_Message
static inline auto Message(int textId, int captionId = IDS_APP) noexcept {
  return LIBFFFTP_WINDOWS::messageBox(textId, captionId);
}
#endif


//--------------------------------------------------------------------------------------------------
#ifdef LIBFFFTP_INCLUDE_COMMON_u8
static inline std::wstring u8(std::string_view utf8) {
  return QString(utf8).toStdWString();
}
static inline std::string u8(std::wstring_view wide) {
  return QString(wide).toStdString();
  return convert<char>([](auto src, auto srclen, auto dst, auto dstlen) noexcept { return WideCharToMultiByte(CP_UTF8, 0, src, srclen, dst, dstlen, nullptr, nullptr); }, wide);
}
#endif

#ifdef LIBFFFTP_OTHER

#ifndef LIBFFFTP_USE_WIN32API

#include "eventproc.hpp"

inline std::unique_ptr<EventProc> eventproc{};

#define SOCKET_PROXY_ERROR (SOCKET_ERROR - 1)

namespace std {
  template<>
  struct default_delete<addrinfo> {
    void operator()(addrinfo* ai) const noexcept {
      freeaddrinfo(ai);
    }
  };
}

inline const std::tuple<std::string, uint16_t> sockaddr2AddressPort(const sockaddr_storage* addr) {
  std::tuple<std::string, uint16_t> ret{};
  if (addr->ss_family == AF_INET6) {
    auto sin6{reinterpret_cast<const sockaddr_in6*>(addr)};
    char tmp[INET6_ADDRSTRLEN];
    std::get<0>(ret) = inet_ntop(AF_INET6, reinterpret_cast<const void*>(&sin6->sin6_addr), tmp, sizeof tmp);
    std::get<1>(ret) = ntohs(sin6->sin6_port);
  } else {
    auto sin{reinterpret_cast<const sockaddr_in*>(addr)};
    char tmp[INET_ADDRSTRLEN];
    std::get<0>(ret) = inet_ntop(AF_INET, reinterpret_cast<const void*>(&sin->sin_addr), tmp, sizeof tmp);
    std::get<1>(ret) = ntohs(sin->sin_port);
  }
  return ret;
}

#endif  // LIBFFFTP_USE_WIN32API


#else  // LIBFFFTP_OTHER

#endif  // LIBFFFTP_OTHER
