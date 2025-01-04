#ifndef LIBFFFTP_WINDOWS_58FEC587_5CD0_4046_AEF2_2E9E3A745449_HPP_
#define LIBFFFTP_WINDOWS_58FEC587_5CD0_4046_AEF2_2E9E3A745449_HPP_

#include "ffftp_common.h"

extern int messageBox(int textId, int captionId = 0);
extern int dialogBox(int dialogid, void* param);
extern void setOption();

#ifndef _WIN32
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <cstdint>

using VOID      = void;
using LPVOID    = void*;
using LPCVOID   = const void*;
using BOOL      = int;
using INT       = int;
using UINT      = unsigned int;
using LONG      = long;
using ULONG     = unsigned long;
using LONGLONG  = long long;
using WORD      = unsigned short;
using DWORD     = unsigned long;
using LPDWORD   = unsigned long*;
using CHAR      = char;
using LPSTR     = char*;
using LPCSTR    = const char*;
using WCHAR     = wchar_t;
using LPWSTR    = wchar_t*;
using LPCWSTR   = const wchar_t*;

#if SIZE_MAX > 0xffffffff
using INT_PTR   = int64_t;
using UINT_PTR  = uint64_t;
using LONG_PTR  = int64_t;
using ULONG_PTR = uint64_t;
#else
using INT_PTR   = int;
using UINT_PTR  = unsigned int;
using LONG_PTR  = long;
using ULONG_PTR = unsigned long;
#endif
using DWORD_PTR = ULONG_PTR;

using WPARAM    = UINT_PTR;
using LPARAM    = LONG_PTR;
using LRESULT   = LONG_PTR;
using HRESULT   = long;
using HANDLE    = void*;
using HINSTANCE = void*;
using HMODULE   = void*;
using HWND      = void*;
using HFONT     = void*;

struct LOGFONTW {};
struct SIZE { LONG cx; LONG cy; };
using LPSIZE = SIZE*;
struct RECT { LONG left; LONG top; LONG right; LONG bottom; };
using LPRECT = RECT*;
struct POINT { LONG x; LONG y; };
using LPPOINT = POINT*;
struct FILETIME { DWORD dwLowDateTime; DWORD dwHighDateTime; };
using LPSOCKADDR = sockaddr*;
struct _WSAPROTOCOL_INFOW {};
using LPWSAPROTOCOL_INFOW = _WSAPROTOCOL_INFOW*;
using LPCCH = const char*;
struct NMHDR {};

#define CALLBACK
#define CONST const
#define FALSE (0)
#define TRUE  (1)

#define CW_USEDEFAULT      (static_cast<int>(0x80000000))
#define LVS_REPORT         (0x0001)
#define IPPORT_FTP         (21)
#define SW_RESTORE         (9)
#define SWP_NOSIZE         (0x0001)
#define SWP_NOMOVE         (0x0002)
#define SWP_NOZORDER       (0x0004)
#define SWP_NOREDRAW       (0x0008)
#define SWP_NOACTIVATE     (0x0010)
#define SWP_FRAMECHANGED   (0x0020)
#define SWP_SHOWWINDOW     (0x0040)
#define SWP_HIDEWINDOW     (0x0080)
#define SWP_NOCOPYBITS     (0x0100)
#define SWP_NOOWNERZORDER  (0x0200)
#define SWP_NOSENDCHANGING (0x0400)
#define SWP_DEFERERASE     (0x2000)
#define SWP_ASYNCWINDOWPOS (0x4000)
#define WMSZ_LEFT          (1)
#define WMSZ_RIGHT         (2)
#define WMSZ_TOP           (3)
#define WMSZ_TOPLEFT       (4)
#define WMSZ_TOPRIGHT      (5)
#define WMSZ_BOTTOM        (6)
#define WMSZ_BOTTOMLEFT    (7)
#define WMSZ_BOTTOMRIGHT   (8)
#define BM_SETCHECK        (0x00F1)
#define BM_GETCHECK        (0x00F0)
#define BST_CHECKED        (0x0001)
#define WM_INITDIALOG      (0x0110)
#define GWLP_USERDATA      (-21)
#define WM_COMMAND         (0x0111)
#define WM_SIZING          (0x0214)
#define WM_NULL            (0x0000)
#define WM_CREATE          (0x0001)
#define WM_DESTROY         (0x0002)
#define WM_MOVE            (0x0003)
#define WM_SIZE            (0x0005)
#define WM_NOTIFY          (0x004E)
#define PSH_PROPSHEETPAGE  (0x00000008)
#define MAKEWPARAM(l, h)           (0)
#define MAKELPARAM(l, h)           (0)
#define GET_WM_COMMAND_ID(wp, lp)  (0)
#define GET_WM_COMMAND_CMD(wp, lp) (0)
#define MAKEINTRESOURCEW(i)        (0)

using DLGPROC = INT_PTR (CALLBACK*)(HWND, UINT, WPARAM, LPARAM);

struct PROPSHEETPAGEW {
  DWORD     dwSize;
  DWORD     dwFlags;
  HINSTANCE hInstance;
  LPCWSTR   pszTitle;
  DLGPROC   pfnDlgProc;
  LPARAM    lParam;
  void*     pfnCallback;
};

struct PROPSHEETHEADERW {
  DWORD     dwSize;
  DWORD     dwFlags;
  HWND      hwndParent;
  HINSTANCE hInstance;
  LPCWSTR   pszIcon;
  LPCWSTR   pszCaption;
  UINT      nPages;
  void*     v1;
  void*     v2;
};
using LPCPROPSHEETHEADERW = const PROPSHEETHEADERW*;

extern BOOL SetWindowTextW(HWND hWnd, LPCWSTR lpString);
extern INT WSAAddressToStringW(LPSOCKADDR lpsaAddress, DWORD dwAddressLength, LPWSAPROTOCOL_INFOW lpProtocolInfo, LPWSTR lpszAddressString, LPDWORD lpdwAddressStringLength);
extern BOOL PlaySoundW(LPCWSTR pszSound, HMODULE hmod, DWORD fdwSound);
extern HMODULE GetModuleHandleW(LPCWSTR lpModuleName);
extern DWORD GetCurrentThreadId();
extern HRESULT OleInitialize(LPVOID pvReserved);
extern int MultiByteToWideChar(UINT CodePage, DWORD dwFlags, LPCCH lpMultiByteStr, int cbMultiByte, LPWSTR lpWideCharStr, int cchWideChar);
extern HWND GetDlgItem(HWND hDlg, int nIDDlgItem);
extern BOOL ScreenToClient(HWND hWnd, LPPOINT lpPoint);
extern BOOL SetWindowPos(HWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags);
extern BOOL GetWindowRect(HWND hWnd, LPRECT lpRect);
extern BOOL InvalidateRect(HWND hWnd, CONST RECT *lpRect, BOOL bErase);
extern LONG_PTR SetWindowLongPtrW(HWND hWnd, int nIndex, LONG_PTR dwNewLong);
extern LONG_PTR GetWindowLongPtrW(HWND hWnd, int nIndex);
extern LRESULT SendDlgItemMessageW(HWND hDlg, int nIDDlgItem, UINT Msg, WPARAM wParam, LPARAM lParam);
extern LRESULT SendMessageW(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
extern INT_PTR PropertySheetW(LPCPROPSHEETHEADERW pcp);
extern BOOL PostMessageW(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
extern BOOL SetEvent(HANDLE hEvent);

#endif  // _WIN32

#endif  // LIBFFFTP_WINDOWS_58FEC587_5CD0_4046_AEF2_2E9E3A745449_HPP_
