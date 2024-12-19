#include "libffftp_windows.hpp"

#include "ffftp_common.h"
#include "libffftp_common.hpp"

namespace LIBFFFTP_WINDOWS {

int MessageBoxIndirectW(const MSGBOXPARAMSW* lpmbp) {
  return ffftp_proc(
    SHOW_MESSAGEBOX,
    { const_cast<void*>(reinterpret_cast<const void*>(lpmbp->lpszText)),
      const_cast<void*>(reinterpret_cast<const void*>(lpmbp->lpszCaption)),
      reinterpret_cast<void*>(static_cast<unsigned long long>(lpmbp->dwStyle)),
      nullptr});
}

}  // namespace LIBFFFTP_WINDOWS
