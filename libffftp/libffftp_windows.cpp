#include "libffftp_windows.hpp"

#include <string>

#include "../Resource/resource.ja-JP.h"
#include "ffftp_common.h"
#include "libffftp_common.hpp"

namespace LIBFFFTP_WINDOWS {

int MessageBoxIndirectW(const MSGBOXPARAMSW *lpmbp) {
  return ffftp_proc(
    SHOW_MESSAGEBOX,
    { const_cast<void*>(reinterpret_cast<const void*>(lpmbp->lpszText)),
      const_cast<void*>(reinterpret_cast<const void*>(lpmbp->lpszCaption)),
      reinterpret_cast<void*>(static_cast<unsigned long long>(lpmbp->dwStyle)),
      nullptr});
}

template <unsigned long long DID>
INT_PTR InputDialogBox(unsigned long long dialogid, LPARAM dwInitParam) {
  return -1;
}

template <>
INT_PTR InputDialogBox<masterpasswd_dlg>(unsigned long long dialogid, LPARAM dwInitParam) {
	struct Data {
		UINT _;
		std::wstring& text;
  };
  Data* p = reinterpret_cast<Data*>(dwInitParam);
  return static_cast<INT_PTR>(ffftp_proc(
    SHOW_DIALOGBOX,
    { reinterpret_cast<void*>(dialogid),
      reinterpret_cast<void*>(&p->text),
      nullptr,
      nullptr}));
}

INT_PTR DialogBoxParamW(HINSTANCE hInstance, LPCWSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam) {
  INT_PTR ret{-1};
  const unsigned long long dialogid = reinterpret_cast<const unsigned long long>(lpTemplateName);
  switch (dialogid) {
  case savecrypt_dlg: break;
  case masterpasswd_dlg:
    ret = InputDialogBox<masterpasswd_dlg>(dialogid, dwInitParam);
    break;
  }
  return ret;
}

}  // namespace LIBFFFTP_WINDOWS
