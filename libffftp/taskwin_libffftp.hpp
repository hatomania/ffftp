#if defined(LIBFFFTP_OTHER)


#elif defined(LIBFFFTP_DECL) || defined(LIBFFFTP_IMPL)

#include "libffftp_common.hpp"

namespace libffftp {

LIBFFFTP_FUNCTION(const wchar_t* taskMessage())
#ifdef LIBFFFTP_IMPL
{
  std::wstring _r{};
  _r.clear();
  for (std::wstring temp; queue_libffftp.try_pop(temp);) {
    _r += temp;
    _r += L"\r\n"sv;
  }
  return _r.c_str();
}
#endif

}  // namespace libffftp

#endif
