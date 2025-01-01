#ifndef LIBFFFTP_WINDOWS_58FEC587_5CD0_4046_AEF2_2E9E3A745449_HPP_
#define LIBFFFTP_WINDOWS_58FEC587_5CD0_4046_AEF2_2E9E3A745449_HPP_

#ifdef LIBFFFTP_USE_WIN32API
#define LIBFFFTP_WINDOWS
#else
#define LIBFFFTP_WINDOWS libffftp_windows
#endif

#include <windows.h>// TODO: 要削除
#include <winsock2.h>

namespace LIBFFFTP_WINDOWS {

extern int MessageBoxIndirectW(const MSGBOXPARAMSW* lpmbp);
extern INT_PTR DialogBoxParamW(HINSTANCE hInstance, LPCWSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam);
extern BOOL SetWindowTextW(HWND hWnd, LPCWSTR lpString);
extern void SetOption();
extern INT WSAAddressToStringW(LPSOCKADDR lpsaAddress, DWORD dwAddressLength, LPWSAPROTOCOL_INFOW lpProtocolInfo, LPWSTR lpszAddressString, LPDWORD lpdwAddressStringLength);
extern BOOL PlaySoundW(LPCWSTR pszSound, HMODULE hmod, DWORD fdwSound);
extern HMODULE GetModuleHandleW(LPCWSTR lpModuleName);
extern DWORD GetCurrentThreadId();
extern HRESULT OleInitialize(LPVOID pvReserved);

}  // namespace LIBFFFTP_WINDOWS

#endif  // LIBFFFTP_WINDOWS_58FEC587_5CD0_4046_AEF2_2E9E3A745449_HPP_
