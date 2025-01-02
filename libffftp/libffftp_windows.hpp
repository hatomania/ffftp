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

extern int messageBox(int textId, int captionId);
extern int dialogBox(int dialogid, void* param);
extern BOOL SetWindowTextW(HWND hWnd, LPCWSTR lpString);
extern void SetOption();
extern INT WSAAddressToStringW(LPSOCKADDR lpsaAddress, DWORD dwAddressLength, LPWSAPROTOCOL_INFOW lpProtocolInfo, LPWSTR lpszAddressString, LPDWORD lpdwAddressStringLength);
extern BOOL PlaySoundW(LPCWSTR pszSound, HMODULE hmod, DWORD fdwSound);
extern HMODULE GetModuleHandleW(LPCWSTR lpModuleName);
extern DWORD GetCurrentThreadId();
extern HRESULT OleInitialize(LPVOID pvReserved);
extern int MultiByteToWideChar(UINT CodePage, DWORD dwFlags, LPCCH lpMultiByteStr, int cbMultiByte, LPWSTR lpWideCharStr, int cchWideChar);

WINBASEAPI
_Success_(return != 0)
         _When_((cchWideChar == -1) && (cbMultiByte != 0), _Post_equal_to_(_String_length_(lpMultiByteStr)+1))
int
WINAPI
WideCharToMultiByte(
    _In_ UINT CodePage,
    _In_ DWORD dwFlags,
    _In_NLS_string_(cchWideChar) LPCWCH lpWideCharStr,
    _In_ int cchWideChar,
    _Out_writes_bytes_to_opt_(cbMultiByte,return) LPSTR lpMultiByteStr,
    _In_ int cbMultiByte,
    _In_opt_ LPCCH lpDefaultChar,
    _Out_opt_ LPBOOL lpUsedDefaultChar
    );

}  // namespace LIBFFFTP_WINDOWS

#endif  // LIBFFFTP_WINDOWS_58FEC587_5CD0_4046_AEF2_2E9E3A745449_HPP_
