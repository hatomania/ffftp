#ifdef LIBFFFTP_OTHER

#include "callback.h"

// 途中でダイアログを表示してユーザに問い合わせる部分の実装はコールバック関数に委ねる
// libffftpを使う側が責任をもって自前のGUIフレームワークに合わせた実装をする

// 起動時にマスターパスワードを求めるダイアログを表示する
LIBFFFTP_IMPLEMENT_CALLBACK(bool, AskMasterPassword, (const wchar_t** passwd), {
	static std::wstring passwd_;
	*passwd = passwd_.c_str();
	return InputDialog(188, GetMainHwnd(), 0, passwd_, 128 + 1, nullptr, 64);
})
// 2回目のマスターパスワード入力を求めるダイアログを表示する
LIBFFFTP_IMPLEMENT_CALLBACK(bool, AskMasterPassword2nd, (const wchar_t** passwd), {
	static std::wstring passwd_;
	*passwd = passwd_.c_str();
	return InputDialog(newmasterpasswd_dlg, GetMainHwnd(), 0, passwd_, MAX_PASSWORD_LEN + 1, nullptr, IDH_HELP_TOPIC_0000064);
})
// 入力したマスターパスワードが間違えていた場合に再度入力するか問い合わせるダイアログを表示する
// true: はい、false: いいえ
LIBFFFTP_IMPLEMENT_CALLBACK(bool, AskRetryMasterPassword, (), {
	return Message(IDS_MASTER_PASSWORD_INCORRECT, MB_YESNO | MB_ICONEXCLAMATION) == IDYES;
})

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
	// 他のプラットフォームがすでに呼び出してるかもしれないのでS_FALSEは失敗扱いにしない
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

}

#endif
