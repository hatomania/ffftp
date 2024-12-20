#if defined(LIBFFFTP_OTHER)

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


#elif defined(LIBFFFTP_DECL) || defined(LIBFFFTP_IMPL)

#include "libffftp_common.hpp"

// libffftpのために用意されたインターフェース
namespace libffftp {

static const wchar_t* const kModuleName = L"libffftp";

LIBFFFTP_FUNCTION(bool initialize())
#ifdef LIBFFFTP_IMPL
{
	hInstFtp = GetModuleHandleW(kModuleName);

	Sound::Register();

	// マルチコアCPUの特定環境下でファイル通信中にクラッシュするバグ対策
//#ifdef DISABLE_MULTI_CPUS
//	SetProcessAffinityMask(GetCurrentProcess(), 1);
//#endif
	MainThreadId = GetCurrentThreadId();

	// S_FALSEはすでに初期化済みの意
	// ffftpguiから呼び出すとS_FALSEが返る。Qtが自身の初期化ですでに内部的に呼び出してるかもしれない
	// なのでS_FALSEは失敗扱いにしない
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
#ifdef LIBFFFTP_IMPL
{
	// TODO: グローバルに保持されているSocketContextの解放。遅延させると各種エラーが発生するため明示的にここで行う。
	MainTransPkt.ctrl_skt.reset();
	DisconnectSet();

	//UnregisterClassW(FtpClass, GetFtpInst());
	FreeSSL();
	FreeZoneID();
	FreeTaskbarList3();
	FreeUPnP();
	OleUninitialize();
}
#endif

LIBFFFTP_FUNCTION(const wchar_t* applicationName())
#ifdef LIBFFFTP_IMPL
{
	return AppName;
}
#endif

LIBFFFTP_FUNCTION(const wchar_t* windowTitle())
#ifdef LIBFFFTP_IMPL
{
  static std::wstring title{};
	title = GetWindowTitle();
  return title.c_str();
}
#endif

}

#endif
