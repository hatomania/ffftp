#ifndef LIBFFFTP_WINDOWS_58FEC587_5CD0_4046_AEF2_2E9E3A745449_HPP_
#define LIBFFFTP_WINDOWS_58FEC587_5CD0_4046_AEF2_2E9E3A745449_HPP_

#define LIBFFFTP_WINDOWS libffftp_windows

#include <windows.h>// TODO: 要削除

namespace LIBFFFTP_WINDOWS {

extern int MessageBoxIndirectW(const MSGBOXPARAMSW* lpmbp);
extern INT_PTR DialogBoxParamW(HINSTANCE hInstance, LPCWSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam);

}  // namespace LIBFFFTP_WINDOWS

#endif  // LIBFFFTP_WINDOWS_58FEC587_5CD0_4046_AEF2_2E9E3A745449_HPP_
