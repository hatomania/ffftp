#ifdef LIBFFFTP_OTHER

static Concurrency::concurrent_queue<std::wstring> libffftp_queue{};


#else

#ifndef LIBFFFTP_DECL
void detail::Notice(UINT id, std::wformat_args args) {
  const auto format = GetString(id);
  auto message = std::vformat(format, args);
  _RPTWN(_CRT_WARN, L"N: %s\n", message.c_str());
  libffftp_queue.push(message);
  queue.push(std::move(message));
}

void detail::Debug(std::wstring_view format, std::wformat_args args) {
  if (DebugConsole != YES) return;
  auto message = std::vformat(format, args);
  _RPTWN(_CRT_WARN, L"D: %s\n", message.c_str());
  message.insert(0, L"## "sv);
  libffftp_queue.push(message);
  queue.push(std::move(message));
}
#endif  // LIBFFFTP_DECL

#include "libffftp_common.hpp"

namespace libffftp {

LIBFFFTP_FUNCTION(const wchar_t* taskMessage())
#ifndef LIBFFFTP_DECL
{
  static std::wstring _r{};
  _r.clear();
  for (std::wstring temp; libffftp_queue.try_pop(temp);) {
    _r += temp;
    _r += L"\r\n"sv;
  }
  return _r.c_str();
}
#endif

}  // namespace libffftp

#endif
