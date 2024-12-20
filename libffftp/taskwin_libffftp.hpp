#ifdef LIBFFFTP_OTHER


#else

#include "libffftp_common.hpp"

namespace libffftp {

LIBFFFTP_FUNCTION(const wchar_t* taskMessage())
#ifndef LIBFFFTP_DECL
{
  std::wstring _r{};
  _r.clear();
  for (std::wstring temp; queue.try_pop(temp);) {
    _r += temp;
    _r += L"\r\n"sv;
  }
  return _r.c_str();
}
#endif

}  // namespace libffftp

#endif
