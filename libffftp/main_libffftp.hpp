#ifdef LIBFFFTP_OTHER

std::wstring GetWindowTitle() {
	return std::vformat(AskConnecting() == YES ? L"{0} ({1}) - FFFTP"sv : L"FFFTP ({1})"sv, std::make_wformat_args(TitleHostName, FilterStr));
}


#else

#include "libffftp_common.hpp"

namespace libffftp {

#ifndef LIBFFFTP_DECL 
namespace{
constexpr const wchar_t* const kModuleName = L"libffftp";
constexpr const wchar_t* const kAppName = L"FFFTP";
}
#endif

LIBFFFTP_FUNCTION(bool initialize())
#ifndef LIBFFFTP_DECL
{
	hInstFtp = GetModuleHandleW(kModuleName);
	Sound::Register();
	MainThreadId = GetCurrentThreadId();

	// 戻り値S_FALSEはすでにOleInitialize関数呼び出し済みの意味
	// 他のプラットフォームがすでに呼び出してるだけかもしれないのでS_FALSEは失敗扱いにしない
	if (HRESULT hres = OleInitialize(nullptr); hres != S_OK && hres != S_FALSE) {
		Message(IDS_FAIL_TO_INIT_OLE, MB_OK | MB_ICONERROR);
		return false;
	}

	LoadUPnP();
	LoadTaskbarList3();
	LoadZoneID();

	if (!LoadSSL()) {
		Message(IDS_ERR_SSL, MB_OK | MB_ICONERROR);
		return false;
	}

	if (InitApp(SW_HIDE) != FFFTP_SUCCESS) {
		return false;
	}

	return true;
}
#endif

LIBFFFTP_FUNCTION(void finalize())
#ifndef LIBFFFTP_DECL
{
	MainTransPkt.ctrl_skt.reset();
	DisconnectSet();

	UnregisterClassW(FtpClass, GetFtpInst());
	FreeSSL();
	FreeZoneID();
	FreeTaskbarList3();
	FreeUPnP();
	OleUninitialize();
}
#endif

LIBFFFTP_FUNCTION(const wchar_t* applicationName())
#ifndef LIBFFFTP_DECL
{
	return kAppName;
}
#endif

LIBFFFTP_FUNCTION(const wchar_t* windowTitle())
#ifndef LIBFFFTP_DECL
{
  static std::wstring title{};
	title = GetWindowTitle();
  return title.c_str();
}
#endif

LIBFFFTP_FUNCTION(long long notifyEvent(int eventid, long long param1, long long param2))
#ifndef LIBFFFTP_DECL
{
  long long ret{-1};
  switch (eventid) {
  case EID_CREATE: break;
  case EID_TIMER: break;
  case EID_MENU_CONNECT:
    (void)param1;
    (void)param2;
    ret = FtpWndProc(GetMainHwnd(), WM_COMMAND, MAKEWPARAM(MENU_CONNECT, 0), 0);
    break;
  case EID_MENU_CONNECT_NUM:
  case EID_MENU_SET_CONNECT:
    (void)param1;
    (void)param2;
    ret = FtpWndProc(GetMainHwnd(), WM_COMMAND, MAKEWPARAM(MENU_SET_CONNECT, 0), 0);
    break;
  case EID_MENU_QUICK:
    (void)param1;
    (void)param2;
    ret = FtpWndProc(GetMainHwnd(), WM_COMMAND, MAKEWPARAM(MENU_QUICK, 0), 0);
    break;
  case EID_MENU_DISCONNECT:
    (void)param1;
    (void)param2;
    ret = FtpWndProc(GetMainHwnd(), WM_COMMAND, MAKEWPARAM(MENU_DISCONNECT, 0), 0);
    break;
  case EID_MENU_HIST_01: break;
  case EID_MENU_HIST_02: break;
  case EID_MENU_HIST_03: break;
  case EID_MENU_HIST_04: break;
  case EID_MENU_HIST_05: break;
  case EID_MENU_HIST_06: break;
  case EID_MENU_HIST_07: break;
  case EID_MENU_HIST_08: break;
  case EID_MENU_HIST_09: break;
  case EID_MENU_HIST_10: break;
  case EID_MENU_HIST_11: break;
  case EID_MENU_HIST_12: break;
  case EID_MENU_HIST_13: break;
  case EID_MENU_HIST_14: break;
  case EID_MENU_HIST_15: break;
  case EID_MENU_HIST_16: break;
  case EID_MENU_HIST_17: break;
  case EID_MENU_HIST_18: break;
  case EID_MENU_HIST_19: break;
  case EID_MENU_HIST_20: break;
  case EID_MENU_UPDIR: break;
  case EID_MENU_DCLICK: break;
  case EID_MENU_OPEN: break;
  case EID_MENU_OPEN1: break;
  case EID_MENU_OPEN2: break;
  case EID_MENU_OPEN3: break;
  case EID_MENU_REMOTE_UPDIR: break;
  case EID_MENU_LOCAL_UPDIR: break;
  case EID_MENU_REMOTE_CHDIR: break;
  case EID_MENU_LOCAL_CHDIR: break;
  case EID_MENU_DOWNLOAD: break;
  case EID_MENU_DOWNLOAD_AS: break;
  case EID_MENU_DOWNLOAD_AS_FILE: break;
  case EID_MENU_DOWNLOAD_ALL: break;
  case EID_MENU_DOWNLOAD_NAME: break;
  case EID_MENU_UPLOAD: break;
  case EID_MENU_UPLOAD_AS: break;
  case EID_MENU_UPLOAD_ALL: break;
  case EID_MENU_MIRROR_UPLOAD: break;
  case EID_MENU_MIRROR_DOWNLOAD: break;
  case EID_MENU_FILESIZE: break;
  case EID_MENU_DELETE: break;
  case EID_MENU_RENAME: break;
  case EID_MENU_MKDIR: break;
  case EID_MENU_CHMOD: break;
  case EID_MENU_SOMECMD: break;
  case EID_MENU_OPTION:
    (void)param1;
    (void)param2;
    ret = FtpWndProc(GetMainHwnd(), WM_COMMAND, MAKEWPARAM(MENU_OPTION, 0), 0);
    break;
  case EID_MENU_FILTER: break;
  case EID_MENU_SORT: break;
  case EID_MENU_EXIT:
    (void)param1;
    (void)param2;
    ret = FtpWndProc(GetMainHwnd(), WM_COMMAND, MAKEWPARAM(MENU_EXIT, 0), 0);
    break;
  case EID_MENU_AUTO_EXIT: break;
  case EID_MENU_ABOUT: break;
  case EID_MENU_TEXT: break;
  case EID_MENU_BINARY: break;
  case EID_MENU_AUTO: break;
  case EID_MENU_XFRMODE: break;
  case EID_MENU_KNJ_SJIS: break;
  case EID_MENU_KNJ_EUC: break;
  case EID_MENU_KNJ_JIS: break;
  case EID_MENU_KNJ_UTF8N: break;
  case EID_MENU_KNJ_UTF8BOM: break;
  case EID_MENU_KNJ_NONE: break;
  case EID_MENU_L_KNJ_SJIS: break;
  case EID_MENU_L_KNJ_EUC: break;
  case EID_MENU_L_KNJ_JIS: break;
  case EID_MENU_L_KNJ_UTF8N: break;
  case EID_MENU_L_KNJ_UTF8BOM: break;
  case EID_MENU_KANACNV: break;
  case EID_MENU_REFRESH: break;
  case EID_MENU_LIST: break;
  case EID_MENU_REPORT: break;
  case EID_REFRESH_LOCAL: break;
  case EID_REFRESH_REMOTE: break;
  case EID_COMBO_LOCAL: break;
  case EID_COMBO_REMOTE: break;
  case EID_MENU_HELP: break;
  case EID_MENU_HELP_TROUBLE: break;
  case EID_MENU_BMARK_ADD: break;
  case EID_MENU_BMARK_ADD_LOCAL: break;
  case EID_MENU_BMARK_ADD_BOTH: break;
  case EID_MENU_BMARK_EDIT: break;
  case EID_MENU_SELECT_ALL: break;
  case EID_MENU_SELECT: break;
  case EID_MENU_FIND: break;
  case EID_MENU_FINDNEXT: break;
  case EID_MENU_DOTFILE: break;
  case EID_MENU_SYNC: break;
  case EID_MENU_IMPORT_WS: break;
  case EID_MENU_REGSAVE: break;
  case EID_MENU_REGLOAD: break;
  case EID_MENU_REGINIT: break;
  case EID_MENU_CHANGEPASSWD: break;
  case EID_MENU_DIRINFO: break;
  case EID_MENU_TASKINFO: break;
  case EID_MENU_ABORT: break;
  case EID_MENU_OTPCALC: break;
  case EID_MENU_FW_FTP_FILTER: break;
  case EID_MENU_URL_COPY: break;
  case EID_MENU_APPKEY: break;
  case EID_MENU_SWITCH_OSS: break;
  case EID_MENU_REMOTE_MOVE_UPDIR: break;
  case EID_MENU_EXPORT_FILEZILLA_XML: break;
  case EID_MENU_EXPORT_WINSCP_INI: break;
  case EID_TTN_GETDISPINFOW: break;
  case EID_LVN_COLUMNCLICK: break;
  case EID_LVN_ITEMCHANGED: break;
  case EID_SIZE: break;
  case EID_MOVING: break;
  case EID_SETFOCUS: break;
  case EID_LBUTTONDOWN: break;
  case EID_LBUTTONUP: break;
  case EID_MOUSEMOVE: break;
  case EID_CHANGE_COND: break;
  case EID_REFRESH_LOCAL_FLG: break;
  case EID_REFRESH_REMOTE_FLG: break;
  case EID_RECONNECTSOCKET: break;
  case EID_MAINTHREADRUNNER: break;
  case EID_PAINT: break;
  case EID_DESTROY: break;
  case EID_QUERYENDSESSION: break;
  case EID_CLOSE: break;
  }
  return ret;
}
#endif

}  // namespace libffftp

#endif
