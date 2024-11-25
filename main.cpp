﻿/** @file main.cpp */
 /*=============================================================================
*
*									ＦＦＦＴＰ
*
===============================================================================
/ Copyright (C) 1997-2007 Sota. All rights reserved.
/
/ Redistribution and use in source and binary forms, with or without 
/ modification, are permitted provided that the following conditions 
/ are met:
/
/  1. Redistributions of source code must retain the above copyright 
/     notice, this list of conditions and the following disclaimer.
/  2. Redistributions in binary form must reproduce the above copyright 
/     notice, this list of conditions and the following disclaimer in the 
/     documentation and/or other materials provided with the distribution.
/
/ THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR 
/ IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
/ OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
/ IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, 
/ INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
/ BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF 
/ USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON 
/ ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
/ (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF 
/ THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
/============================================================================*/

#include "common.h"
// #pragma hdrstopとは？
// 共通ヘッダファイルのインクルード直後に記述することで最適なコンパイル結果が得られるらしい
// https://qiita.com/msnaru/items/bb098447292a20d8faf3
#pragma hdrstop
#include <delayimp.h>// 遅延読み込みヘルパー。なくてもビルドは通るが必要なのか？ https://hoshizuki.hateblo.jp/entry/20090531/p1
#include <HtmlHelp.h>
#pragma comment(lib, "HtmlHelp.lib")
#pragma comment(lib, "Version.Lib")

/**
 * @name
 * @brief ウィンドウのサイズ変更の状態を表すマクロ群
 *
 * cpp内で定義されているマクロなので、このソースファイル内でのみ使用されることに留意してください。\n
 * 参照元: @ref CheckResizeFrame()
 */
 ///@{
#define RESIZE_OFF		0		/**< @brief ウインドウの区切り位置変更していない */
#define RESIZE_ON		1		/**< @brief ウインドウの区切り位置変更中 */
#define RESIZE_PREPARE	2		/**< @brief ウインドウの区切り位置変更の準備 */

#define RESIZE_HPOS		0		/**< @brief ローカル－ホスト間の区切り位置変更 */
#define RESIZE_VPOS		1		/**< @brief リスト－タスク間の区切り位置の変更 */
///@}

/*===== コマンドラインオプション =====*/

/**
 * @name コマンドラインオプションマクロ
 * @brief コマンドラインオプションの解析に伴うアプリの動作を定義するマクロ軍
 *
 * cpp内で定義されているマクロなので、このソースファイル内でのみ使用されることに留意してください。\n
 * 参照元: @ref FtpWndProc(), @ref AnalyzeComLine()
 */
///@{
#define OPT_MIRROR		0x00000001	/**< @brief ミラーリングアップロードを行う */
#define OPT_FORCE		0x00000002	/**< @brief ミラーリング開始の確認をしない */
#define OPT_QUIT		0x00000004	/**< @brief 終了後プログラム終了 */
#define OPT_EUC			0x00000008	/**< @brief 漢字コードはEUC */
#define OPT_JIS			0x00000010	/**< @brief 漢字コードはJIS */
#define OPT_ASCII		0x00000020	/**< @brief アスキー転送モード */
#define OPT_BINARY		0x00000040	/**< @brief バイナリ転送モード */
#define OPT_AUTO		0x00000080	/**< @brief 自動判別 */
#define OPT_KANA		0x00000100	/**< @brief 半角かなをそのまま通す */
#define OPT_EUC_NAME	0x00000200	/**< @brief ファイル名はEUC */
#define OPT_JIS_NAME	0x00000400	/**< @brief ファイル名はJIS */
#define OPT_MIRRORDOWN	0x00000800	/**< @brief ミラーリングダウンロードを行う */
#define OPT_SAVEOFF		0x00001000	/**< @brief 設定の保存を中止する */
#define OPT_SAVEON		0x00002000	/**< @brief 設定の保存を再開する */
#define OPT_SJIS		0x00004000	/**< @brief 漢字コードはShift_JIS */
#define OPT_UTF8N		0x00008000	/**< @brief 漢字コードはUTF-8 */
#define OPT_UTF8BOM		0x00010000	/**< @brief 漢字コードはUTF-8 BOM */
#define OPT_SJIS_NAME	0x00020000	/**< @brief ファイル名はShift_JIS */
#define OPT_UTF8N_NAME	0x00040000	/**< @brief ファイル名はUTF-8 */
///@}


/*===== プロトタイプ =====*/

static int InitApp(int cmdShow);
static bool MakeAllWindows(int cmdShow);
static std::wstring GetWindowTitle();
static void DeleteAllObject(void);
static LRESULT CALLBACK FtpWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
static void StartupProc(std::vector<std::wstring_view> const& args);
/**
 * @addtogroup コマンドライン引数関連
 * @{
 */
/**
 * @brief コマンドラインを解析
 *
 * @ref ARGUMENTS.md を参照
 * @ref コマンドラインオプションマクロ
 * @param[in]	args		コマンドライン引数（引数文字列の配列）
 * @param[out]	hostname	オプション'-s'または'\--set'を指定したときの、登録ホスト名
 * @param[out]	unc			オプション（'-'または'\--'から始まる引数）を何も指定しなかった場合の第一引数
 *
 * @return 指定されたオプションに対するOPT_～マクロのOR値を、該当するオプションがなかった場合は無効値を返す
 *
 * Win32 APIの有無: 直接はなし
 */
static std::optional<int> AnalyzeComLine(std::vector<std::wstring_view> const& args, std::wstring& hostname, std::wstring& unc);
/** @} */
static void ExitProc(HWND hWnd);
static void ChangeDir(int Win, std::wstring dir);
static void ResizeWindowProc(void);
static void CalcWinSize(void);
static void CheckResizeFrame(WPARAM Keys, int x, int y);
static void DispDirInfo(void);
static void DeleteAlltempFile();
static void AboutDialog(HWND hWnd) noexcept;
static int EnterMasterPasswordAndSet(bool newpassword, HWND hWnd);

/*===== ローカルなワーク =====*/

static const wchar_t AppName[] = L"FFFTP";
static const wchar_t FtpClass[] = L"FFFTPWin"; /**< @brief ウィンドウ作成周りのWin32APIに渡されるクラス名 */
static const wchar_t WebURL[] = L"https://github.com/ffftp/ffftp"; /**< @brief バージョン情報や公式ホームページ訪問に使用されるURL */

static HINSTANCE hInstFtp;			/**< @brief 本アプリケーションのインスタンスハンドル */
static HWND hWndFtp;				/**< @brief メインウィンドウのウィンドウハンドル */
static HWND hWndCurFocus = NULL;	/**< @brief ローカル側とホスト側、どちら側にカーソルがあるか（どちら側に対する処理か）を判断するために使われる？ */

static HACCEL Accel;				/**< @brief アクセラレータ（ショートカットキー）ハンドル */

static int Resizing = RESIZE_OFF;	/**< @brief ウィンドウサイズ変更の状態を示す */
static int ResizePos;				/**< @brief 縦のみを変更したか、あるいは横のみを変更したか？？ */
static std::vector<fs::path> TempFiles;/**< @brief  */

static int SaveExit = YES;		/**< @brief アプリ終了時、保存処理を行うかどうか */
static int AutoExit = NO;		/**< @brief コマンドラインの状態がOPT_QUITだった場合、これがYESになり、アプリ起動後自動で終了する */

static fs::path IniPath;		/**< @brief  */
static int ForceIni = NO;

TRANSPACKET MainTransPkt;		/* ファイル転送用パケット */
								/* これを使って転送を行うと、ツールバーの転送 */
								/* 中止ボタンで中止できる */
std::wstring TitleHostName;		/**< @brief メインウィンドウのタイトル文字列。ホストに接続されるとホスト名が表示されたりする */
std::wstring FilterStr = L"*"s;	/**< @brief ファイルリストの表示フィルタ */
HANDLE initialized = CreateEventW(nullptr, true, false, nullptr); /**< @brief 転送スレッドの同期待機イベント用？ */

int SuppressRefresh = 0;		/**< @brief  */

static DWORD dwCookie;			/**< @brief HtmlHelpで使用 */

// マルチコアCPUの特定環境下でファイル通信中にクラッシュするバグ対策
static DWORD MainThreadId;		/**< @brief メインスレッドのID */
HANDLE ChangeNotification = INVALID_HANDLE_VALUE;/**< @brief ファイルを監視のWin32APIで使用されるハンドル？ FindFirstChangeNotificationW()など */
static int ToolWinHeight = 28;	/**< @brief ツールウィンドウの高さ */
static HWND hHelpWin = NULL;	/**< @brief 表示されたHTMLHelpのウィンドウハンドル？ */
static int NoopEnable = NO;		/**< @brief  */


/**
 * @brief システムディレクトリのパスを返す
 * @return システムディレクトリのパス (通常は、C:\Windows\System32)
 *
 * @note Win32 APIの有無: あり
 */
fs::path const& systemDirectory() {
	static fs::path const directory = [] {
		std::wstring directory(32768, L'\0');
		auto const length = GetSystemDirectoryW(data(directory), size_as<UINT>(directory));
		assert(0 < length);
		directory.resize(length);
		return directory;
	}();
	return directory;
}


/**
 * @brief 実行しているEXEファイル名を返す
 * @return 実行しているEXEファイル名
 *
 * @note Win32 APIの有無: あり
 */
static auto const& moduleFileName() {
	static fs::path const filename = [] {
		std::wstring filename(32768, L'\0');
		auto const length = GetModuleFileNameW(GetFtpInst(), data(filename), size_as<DWORD>(filename));
		assert(0 < length);
		filename.resize(length);
		return filename;
	}();
	return filename;
}


/**
 * @brief 独自に生成したテンポラリフォルダへのパスを返す
 * @return 独自に生成したテンポラリフォルダへのパス
 *
 * @note Win32 APIの有無: あり
 */
fs::path const& tempDirectory() {
	static auto const directory = [] {
		auto const path = fs::temp_directory_path() / std::format(L"ffftp{:08x}"sv, GetCurrentProcessId());
		fs::create_directory(path);
		return path;
	}();
	return directory;
}


/**
 * @brief バージョン文字列を返す
 * @details EXEに埋め込まれているバージョン情報を用いてバージョン文字列を作成している。
 * @return バージョン文字列
 *
 * @note Win32 APIの有無: あり
 */
static auto version() {
	auto const size = GetFileVersionInfoSizeW(moduleFileName().c_str(), 0);
	assert(0 < size);
	std::vector<char> buffer(size);
	auto result = GetFileVersionInfoW(moduleFileName().c_str(), 0, size, data(buffer));
	assert(result);
	LPVOID block;
	UINT len;
	result = VerQueryValueW(data(buffer), L"\\", &block, &len);
	assert(result && sizeof(VS_FIXEDFILEINFO) <= len);
	auto const ms = static_cast<VS_FIXEDFILEINFO*>(block)->dwProductVersionMS, ls = static_cast<VS_FIXEDFILEINFO*>(block)->dwProductVersionLS;
	auto const major = HIWORD(ms), minor = LOWORD(ms), patch = HIWORD(ls), build = LOWORD(ls);
	auto const format = build != 0 ? L"{}.{}.{}.{}"sv : patch != 0 ? L"{}.{}.{}"sv : L"{}.{}"sv;
	return std::vformat(format, std::make_wformat_args(major, minor, patch, build));
}


/**
 * @brief プログラムがポータブル版かどうかを返す
 * @details EXEファイル名の拡張子を'portable'にしたファイルが存在しているとポータブル版としてtrueを返す。
 * @return true  ポータブル版である
 * @return false ポータブル版でない
 *
 * Win32 APIの有無: 直接はなし
 */
static auto isPortable() {
	static auto const isPortable = fs::is_regular_file(fs::path{ moduleFileName() }.replace_filename(L"portable"sv));
	return isPortable;
}


/**
 * @brief HTMLヘルプファイルへのパスを返す
 * @details EXEファイル名の拡張子を'chm'にしたパスを返す。
 * @return  HTMLヘルプファイルへのパス
 *
 * Win32 APIの有無: 直接はなし
 */
static auto const& helpPath() {
	static auto const path = fs::path{ moduleFileName() }.replace_extension(L".chm"sv);
	return path;
}

/**
 * @addtogroup サウンド関係
 * @{
 */
Sound Sound::Connected{ L"FFFTP_Connected", L"Connected", IDS_SOUNDCONNECTED };
Sound Sound::Transferred{ L"FFFTP_Transferred", L"Transferred", IDS_SOUNDTRANSFERRED };
Sound Sound::Error{ L"FFFTP_Error", L"Error", IDS_SOUNDERROR };
/**
 * @brief サウンド関連のレジストリを登録
 *
 * [コントロール パネル] > [ハードウェアとサウンド] > [サウンド] で表示されるシステムダイアログで鳴らす音を設定できるようになる。\n
 * ホストとの接続完了、エラー発生時、ファイル転送完了時にそれぞれ鳴る音を、Windowsのシステムダイアログで設定できるようになる。\n
 * アプリをアンインストールしても残り続ける？
 *
 * @note Win32 APIの有無: あり
 */
void Sound::Register() {
	if (HKEY eventlabels; RegCreateKeyExW(HKEY_CURRENT_USER, LR"(AppEvents\EventLabels)", 0, nullptr, 0, KEY_WRITE, nullptr, &eventlabels, nullptr) == ERROR_SUCCESS) {
		if (HKEY apps; RegCreateKeyExW(HKEY_CURRENT_USER, LR"(AppEvents\Schemes\Apps\ffftp)", 0, nullptr, 0, KEY_WRITE, nullptr, &apps, nullptr) == ERROR_SUCCESS) {
			RegSetValueExW(apps, nullptr, 0, REG_SZ, reinterpret_cast<const BYTE*>(L"FFFTP"), 12);
			for (auto [keyName, name, id] : { Connected, Transferred, Error }) {
				if (HKEY key; RegCreateKeyExW(eventlabels, keyName, 0, nullptr, 0, KEY_SET_VALUE, nullptr, &key, nullptr) == ERROR_SUCCESS) {
					RegSetValueExW(key, nullptr, 0, REG_SZ, reinterpret_cast<const BYTE*>(name), ((DWORD)wcslen(name) + 1) * sizeof(wchar_t));
					auto const value = std::format(L"@{},{}"sv, moduleFileName().native(), -id);
					RegSetValueExW(key, L"DispFileName", 0, REG_SZ, reinterpret_cast<const BYTE*>(value.c_str()), (size_as<DWORD>(value) + 1) * sizeof(wchar_t));
				}
				if (HKEY key; RegCreateKeyExW(apps, keyName, 0, nullptr, 0, KEY_WRITE, nullptr, &key, nullptr) == ERROR_SUCCESS) {
					if (HKEY _current; RegCreateKeyExW(key, L".current", 0, nullptr, 0, KEY_WRITE, nullptr, &_current, nullptr) == ERROR_SUCCESS)
						RegCloseKey(_current);
					RegCloseKey(key);
				}
			}
			RegCloseKey(apps);
		}
		RegCloseKey(eventlabels);
	}
}
/** @} */

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

/**
 * @brief プログラムのエントリポイント
 * @details 処理はこの関数から始まります。
 * @note Win32 APIの有無: どっさり
 */
 // メインルーチン
int WINAPI wWinMain(__in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPWSTR lpCmdLine, __in int nShowCmd) {
	//--------------------------------------------------
	// 初期化
	//--------------------------------------------------
	hInstFtp = hInstance;

	Sound::Register();

	// マルチコアCPUの特定環境下でファイル通信中にクラッシュするバグ対策
#ifdef DISABLE_MULTI_CPUS
	SetProcessAffinityMask(GetCurrentProcess(), 1);
#endif
	MainThreadId = GetCurrentThreadId();

	if (OleInitialize(nullptr) != S_OK) {
		Message(IDS_FAIL_TO_INIT_OLE, MB_OK | MB_ICONERROR);
		return 0;
	}

	LoadUPnP();
	LoadTaskbarList3();
	LoadZoneID();

	if (!LoadSSL()) {
		Message(IDS_ERR_SSL, MB_OK | MB_ICONERROR);
		return 0;
	}

	//--------------------------------------------------
	// ウィンドウのメインループ
	//--------------------------------------------------
	int exitCode = FALSE;
	if (InitApp(nShowCmd) == FFFTP_SUCCESS) {
		MSG msg;
		while (GetMessageW(&msg, NULL, 0, 0)) {
			if (__pragma(warning(suppress:6387)) HtmlHelpW(NULL, NULL, HH_PRETRANSLATEMESSAGE, (DWORD_PTR)&msg))
				continue;
			/* ディレクトリ名の表示コンボボックスでBSやRETが効くように */
			/* コンボボックス内ではアクセラレータを無効にする */
			if (msg.hwnd == GetLocalHistEditHwnd() || msg.hwnd == GetRemoteHistEditHwnd() || hHelpWin && GetAncestor(msg.hwnd, GA_ROOT) == hHelpWin || AskUserOpeDisabled() || TranslateAcceleratorW(GetMainHwnd(), Accel, &msg) == 0) {
				TranslateMessage(&msg);
				DispatchMessageW(&msg);
			}
		}
		exitCode = (int)msg.wParam;
	}

	//--------------------------------------------------
	// 後処理
	//--------------------------------------------------
	// TODO: グローバルに保持されているSocketContextの解放。遅延させると各種エラーが発生するため明示的にここで行う。
	MainTransPkt.ctrl_skt.reset();
	DisconnectSet();

	UnregisterClassW(FtpClass, GetFtpInst());
	FreeSSL();
	FreeZoneID();
	FreeTaskbarList3();
	FreeUPnP();
	OleUninitialize();
	return exitCode;
}


// アプリケーションの初期設定
static int InitApp(int cmdShow)
{
	int sts;
	int Err;
	WSADATA WSAData;
	int useDefautPassword = 0; /* 警告文表示用 */
	int masterpass;
	// ポータブル版判定
	int ImportPortable;

	sts = FFFTP_FAIL;
	
	__pragma(warning(suppress:6387)) HtmlHelpW(NULL, NULL, HH_INITIALIZE, (DWORD_PTR)&dwCookie);

	if((Err = WSAStartup((WORD)0x0202, &WSAData)) != 0)
		MessageBoxW(GetMainHwnd(), GetErrorMessage(Err).c_str(), GetString(IDS_APP).c_str(), MB_OK);
	else
	{
		Accel = LoadAcceleratorsW(GetFtpInst(), MAKEINTRESOURCEW(ffftp_accel));

		std::copy(std::begin(LocalTabWidthDefault), std::end(LocalTabWidthDefault), std::begin(LocalTabWidth));
		std::copy(std::begin(RemoteTabWidthDefault), std::end(RemoteTabWidthDefault), std::begin(RemoteTabWidth));

		//--------------------------------------------------
		// 設定ファイル関連の処理
		//--------------------------------------------------
		std::vector<std::wstring_view> args{ __wargv + 1, __wargv + __argc };
		// コマンドラインオプションを解析して -n か --ini が含まれていたら設定をINIファイルから読み込むようにする(以下、INIモード)
		if (auto it = std::find_if(begin(args), end(args), [](auto const& arg) { return ieq(arg, L"-n"sv) || ieq(arg, L"--ini"sv); }); it != end(args) && ++it != end(args)) {
			ForceIni = YES;
			RegType = REGTYPE_INI;
			IniPath = *it; // コマンドラインに指定されたINIファイルへのパス？
		} else
			IniPath = fs::path{ moduleFileName() }.replace_extension(L".ini"sv);// デフォルトのINIファイルのパス？
		// ポータブル版かどうかの判定（EXEのファイル名で判断してる？）
		ImportPortable = NO;
		if (isPortable()) {
			// ポータブル版だったら強制的にINIモード
			ForceIni = YES;
			RegType = REGTYPE_INI;
			if(IsRegAvailable() == YES && IsIniAvailable() == NO)
			{
				// INIモードで動作しようとしているが、REGも見つかった。REGをINIにインポートする？
				if (Dialog(GetFtpInst(), ini_from_reg_dlg, GetMainHwnd()))
					ImportPortable = YES;
			}
		} else {
			if(ReadSettingsVersion() > VER_NUM)
			{
				// 新しいバージョンの設定が見つかった
				if(IsRegAvailable() == YES && IsIniAvailable() == NO)
				{
					switch(Message(IDS_FOUND_NEW_VERSION_INI, MB_YESNOCANCEL | MB_DEFBUTTON2))
					{
						case IDCANCEL:// 読み取り専用モードにする
							ReadOnlySettings = YES;
							break;
						case IDYES:// そのままREGに新設定を上書き
							break;
						case IDNO:// 新設定がREGに上書きされるのを阻止(INIモードにしてINIファイルに保存されるようにする)
							ImportPortable = YES;
							break;
					}
				}
			}
		}
		// ポータブル版判定
		if(ImportPortable == YES)
		{
			ForceIni = NO;
			RegType = REGTYPE_REG;
		}

		//--------------------------------------------------
		// マスターパスワード関連の処理
		//--------------------------------------------------
			/* 2010.02.01 genta マスターパスワードを入力させる
		  -z オプションがあるときは最初だけスキップ
		  -z オプションがないときは，デフォルトパスワードをまず試す
		  LoadRegistry()する
		  パスワードが不一致なら再入力するか尋ねる．
		  (破損していた場合はさせない)
		*/
		if(auto it = std::find_if(begin(args), end(args), [](auto const& arg) { return ieq(arg, L"-z"sv) || ieq(arg, L"--mpasswd"sv); }); it != end(args) && ++it != end(args))
		{
			SetMasterPassword(*it);
			useDefautPassword = 0;
		}
		else {
			/* パスワード指定無し */
			SetMasterPassword();
			/* この場では表示できないのでフラグだけ立てておく*/
			useDefautPassword = 2;
		}

		/* パスワードチェックのみ実施 */
		masterpass = 1;// 0/ユーザキャンセル, 1/設定した, 2/デフォルト設定
		while( ValidateMasterPassword() == YES &&
				GetMasterPasswordStatus() == PASSWORD_UNMATCH ){
			
			if( useDefautPassword != 2 ){
				/* 再トライするか確認 */
				if( !AskRetryMasterPassword_func() ){
					useDefautPassword = 0; /* 不一致なので，もはやデフォルトかどうかは分からない */
					break;
				}
			}
			
			/* 再入力させる*/
			masterpass = EnterMasterPasswordAndSet(false, NULL);
			if( masterpass == 2 ){
				useDefautPassword = 1;
			}
			else if( masterpass == 0 ){
				SaveExit = NO;
				break;
			}
			else {
				useDefautPassword = 0;
			}
		}
		
		if(masterpass != 0)// デフォルトマスターパスワードが使われたか、マスターパスワードの確認でキャンセルされなかったら
		{
			// ホスト共通設定機能
			ResetDefaultHost();

			LoadRegistry();

			// ポータブル版判定
			if(ImportPortable == YES)
			{
				ForceIni = YES;
				RegType = REGTYPE_INI;
			}

			//タイマの精度を改善
			timeBeginPeriod(1);

			if(MakeAllWindows(cmdShow))
			{
				hWndCurFocus = GetLocalHwnd();

				if (std::error_code ec; !empty(DefaultLocalPath))
					fs::current_path(DefaultLocalPath, ec);

				SetSortTypeImm(Sort);
				SetTransferTypeImm(TransMode);
				DispTransferType();
				SetHostKanaCnvImm(YES);
				SetHostKanjiCodeImm(KANJI_NOCNV);
				// UTF-8対応
				SetLocalKanjiCodeImm(LocalKanjiCode);
				DispListType();
				DispDotFileMode();
				DispSyncMoveMode();

				if(MakeTransferThread() == FFFTP_SUCCESS)
				{
					Debug(L"DEBUG MESSAGE ON ! ##"sv);

					DispWindowTitle();
					UpdateStatusBar();
					Notice(IDS_COPYRIGHT, version(), sizeof(void*) == 4 ? L"32bit"sv : L"64bit"sv);

					if(ForceIni)
						Notice(IDS_MSGJPN283, IniPath.native());

					Debug(L"Help={}", helpPath().native());

					DragAcceptFiles(GetRemoteHwnd(), TRUE);
					DragAcceptFiles(GetLocalHwnd(), TRUE);

					SetAllHistoryToMenu();
					GetLocalDirForWnd();
					MakeButtonsFocus();
					DispTransferFiles();

					StartupProc(args);
					sts = FFFTP_SUCCESS;

					/* セキュリティ警告文の表示 */
					if( useDefautPassword ){
						Notice(IDS_MSGJPN300);
					}
					
					/* パスワード不一致警告文の表示 */
					switch( GetMasterPasswordStatus() ){
					case PASSWORD_UNMATCH:
						Notice(IDS_MSGJPN301);
						break;
					case BAD_PASSWORD_HASH:
						Notice(IDS_MSGJPN302);
						break;
					default:
						break;
					}
				}
			}
		}
	}

	if(sts == FFFTP_FAIL)
		DeleteAllObject();

	return(sts);
}


// ウインドウを作成する
static bool MakeAllWindows(int cmdShow) {
	WNDCLASSEXW classEx{ sizeof(WNDCLASSEXW), 0, FtpWndProc, 0, 0, GetFtpInst(), LoadIconW(GetFtpInst(), MAKEINTRESOURCEW(ffftp)), 0, GetSysColorBrush(COLOR_3DFACE), MAKEINTRESOURCEW(main_menu), FtpClass };
	RegisterClassExW(&classEx);

	if (SaveWinPos == NO) {
		WinPosX = CW_USEDEFAULT;
		WinPosY = 0;
	}
	hWndFtp = CreateWindowExW(0, FtpClass, L"FFFTP", WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, WinPosX, WinPosY, WinWidth, WinHeight, HWND_DESKTOP, 0, GetFtpInst(), nullptr);
	if (!hWndFtp)
		return false;

	// ウィンドウがのっけから画面外にはみ出ないようにする？
	RECT workArea;
	SystemParametersInfoW(SPI_GETWORKAREA, 0, &workArea, 0);
	RECT windowRect;
	GetWindowRect(GetMainHwnd(), &windowRect);
	if (workArea.bottom < windowRect.bottom)
		MoveWindow(GetMainHwnd(), windowRect.left, std::max(0L, windowRect.top - windowRect.bottom + workArea.bottom), WinWidth, WinHeight, FALSE);

	if (MakeStatusBarWindow() == FFFTP_FAIL)
		return false;

	CalcWinSize();

	if (!MakeToolBarWindow())
		return false;

	if (MakeListWin() == FFFTP_FAIL)
		return false;

	if (MakeTaskWindow() == FFFTP_FAIL)
		return false;

	ShowWindow(GetMainHwnd(), cmdShow != SW_MINIMIZE && cmdShow != SW_SHOWMINIMIZED && cmdShow != SW_SHOWMINNOACTIVE && Sizing == SW_MAXIMIZE ? SW_MAXIMIZE : cmdShow);

	SetListViewType();

	return true;
}


// ウインドウのタイトルを取得する
static std::wstring GetWindowTitle() {
	return std::vformat(AskConnecting() == YES ? L"{0} ({1}) - FFFTP"sv : L"FFFTP ({1})"sv, std::make_wformat_args(TitleHostName, FilterStr));
}


// ウインドウのタイトルを表示する
void DispWindowTitle() {
	SetWindowTextW(GetMainHwnd(), GetWindowTitle().c_str());
}


// 全てのオブジェクトを削除
static void DeleteAllObject() {
	WSACleanup();
	if (hWndFtp != NULL)
		DestroyWindow(hWndFtp);
}


// メインウインドウのウインドウハンドルを返す
HWND GetMainHwnd() noexcept {
	return hWndFtp;
}


// 現在フォーカスがあるウインドウのをセットする
void SetFocusHwnd(HWND hWnd) noexcept {
	hWndCurFocus = hWnd;
}


// プログラムのインスタンスを返す
HINSTANCE GetFtpInst() noexcept {
	return hInstFtp;
}


static void OtpCalcTool() noexcept {
	struct Data {
		using result_t = int;
		using AlgoButton = RadioButton<OTPCALC_MD4, OTPCALC_MD5, OTPCALC_SHA1>;
		INT_PTR OnInit(HWND hDlg) noexcept {
			SendDlgItemMessageW(hDlg, OTPCALC_KEY, EM_LIMITTEXT, 40, 0);
			SendDlgItemMessageW(hDlg, OTPCALC_PASS, EM_LIMITTEXT, PASSWORD_LEN, 0);
			AlgoButton::Set(hDlg, MD4);
			return(TRUE);
		}
		void OnCommand(HWND hDlg, WORD id) {
			switch (id) {
			case IDOK:
			{
				static boost::wregex re{ LR"(^ *(\d+)(?=[^ ]* +([^ ]+)))" };
				auto const key = GetText(hDlg, OTPCALC_KEY);
				if (boost::wsmatch m; boost::regex_search(key, m, re)) {
					if (m[2].matched) {
						auto seq = std::stoi(m[1]);
						auto seed = u8(m[2].str());
						auto pass = u8(GetText(hDlg, OTPCALC_PASS));
						auto result = Make6WordPass(seq, seed, pass, AlgoButton::Get(hDlg));
						SetText(hDlg, OTPCALC_RES, u8(result));
					} else
						SetText(hDlg, OTPCALC_RES, GetString(IDS_MSGJPN251));
				} else
					SetText(hDlg, OTPCALC_RES, GetString(IDS_MSGJPN253));
				break;
			}
			case IDCANCEL:
				EndDialog(hDlg, NO);
				break;
			case IDHELP:
				ShowHelp(IDH_HELP_TOPIC_0000037);
				break;
			}
		}
	};
	Dialog(GetFtpInst(), otp_calc_dlg, GetMainHwnd(), Data{});
}

static void TurnStatefulFTPFilter() {
	if (auto const ID = Message(IDS_MANAGE_STATEFUL_FTP, MB_YESNOCANCEL); ID == IDYES || ID == IDNO)
		if (PtrToInt(ShellExecuteW(NULL, L"runas", L"netsh", ID == IDYES ? L"advfirewall set global statefulftp enable" : L"advfirewall set global statefulftp disable", systemDirectory().c_str(), SW_SHOW)) <= 32)
			Message(IDS_FAIL_TO_MANAGE_STATEFUL_FTP, MB_OK | MB_ICONERROR);
}


/*----- メインウインドウのメッセージ処理 --------------------------------------
*
*	Parameter
*		HWND hWnd : ウインドウハンドル
*		UINT message  : メッセージ番号
*		WPARAM wParam : メッセージの WPARAM 引数
*		LPARAM lParam : メッセージの LPARAM 引数
*
*	Return Value
*		メッセージに対応する戻り値
*----------------------------------------------------------------------------*/

static LRESULT CALLBACK FtpWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	RECT Rect;

	int TmpTransType;

	switch (message)
	{
		// ローカル側自動更新
		// タスクバー進捗表示
		case WM_CREATE :
			SetTimer(hWnd, 1, 1000, NULL);
			SetTimer(hWnd, 2, 100, NULL);
			break;

		// ローカル側自動更新
		// 自動切断対策
		// タスクバー進捗表示
		case WM_TIMER :
			switch(wParam)
			{
			case 1:
				if(WaitForSingleObject(ChangeNotification, 0) == WAIT_OBJECT_0)
				{
					if (!AskUserOpeDisabled())
					{
						FindNextChangeNotification(ChangeNotification);
						if (AutoRefreshFileList == YES)
							RefreshLocal();
					}
				}
				if(CancelFlg == YES)
					AbortRecoveryProc();
				if (auto const& curHost = GetCurHost(); NoopEnable == YES && curHost.NoopInterval > 0 && time(NULL) - LastDataConnectionTime >= curHost.NoopInterval) {
					NoopProc(NO);
					LastDataConnectionTime = time(NULL);
				}
				break;
			case 2:
				if(IsTaskbarList3Loaded() == YES)
					UpdateTaskbarProgress();
				break;
			}
			break;

		case WM_COMMAND :
			// 同時接続対応
			// 中断後に受信バッファに応答が残っていると次のコマンドの応答が正しく処理できない
			if(CancelFlg == YES)
				AbortRecoveryProc();
			switch(LOWORD(wParam))
			{
				// メニュー[接続]->[接続]をクリックしたときの処理
				case MENU_CONNECT :
					// 自動切断対策
					NoopEnable = NO;
					ConnectProc(DLG_TYPE_CON, -1);
					// 自動切断対策
					NoopEnable = YES;
					break;

				// 起動時に引数で自動するホストを指定したときの処理？
				case MENU_CONNECT_NUM :
					// 自動切断対策
					NoopEnable = NO;
					ConnectProc(DLG_TYPE_CON, (int)lParam);
					// 自動切断対策
					NoopEnable = YES;
					if(AskConnecting() == YES)
					{
						if(HIWORD(wParam) & OPT_MIRROR)
						{
							if(HIWORD(wParam) & OPT_FORCE)
								MirrorUploadProc(NO);
							else
								MirrorUploadProc(YES);
						}
						else if(HIWORD(wParam) & OPT_MIRRORDOWN)
						{
							if(HIWORD(wParam) & OPT_FORCE)
								MirrorDownloadProc(NO);
							else
								MirrorDownloadProc(YES);
						}
					}
					SetEvent(initialized);
					break;

				case MENU_SET_CONNECT :
					// 自動切断対策
					NoopEnable = NO;
					ConnectProc(DLG_TYPE_SET, -1);
					// 自動切断対策
					NoopEnable = YES;
					break;

				case MENU_QUICK :
					// 自動切断対策
					NoopEnable = NO;
					QuickConnectProc();
					// 自動切断対策
					NoopEnable = YES;
					break;

				case MENU_DISCONNECT :
					if(AskTryingConnect() == YES)
						CancelFlg = YES;
					else if(AskConnecting() == YES)
					{
						SaveBookMark();
						SaveCurrentSetToHost();
						DisconnectProc();
					}
					break;

				case MENU_HIST_1 :
				case MENU_HIST_2 :
				case MENU_HIST_3 :
				case MENU_HIST_4 :
				case MENU_HIST_5 :
				case MENU_HIST_6 :
				case MENU_HIST_7 :
				case MENU_HIST_8 :
				case MENU_HIST_9 :
				case MENU_HIST_10 :
				case MENU_HIST_11 :
				case MENU_HIST_12 :
				case MENU_HIST_13 :
				case MENU_HIST_14 :
				case MENU_HIST_15 :
				case MENU_HIST_16 :
				case MENU_HIST_17 :
				case MENU_HIST_18 :
				case MENU_HIST_19 :
				case MENU_HIST_20 :
					// 自動切断対策
					NoopEnable = NO;
					HistoryConnectProc(LOWORD(wParam));
					// 自動切断対策
					NoopEnable = YES;
					break;

				case MENU_UPDIR :
					if(hWndCurFocus == GetLocalHwnd())
						PostMessageW(hWnd, WM_COMMAND, MAKEWPARAM(MENU_LOCAL_UPDIR, 0), 0);
					else
						PostMessageW(hWnd, WM_COMMAND, MAKEWPARAM(MENU_REMOTE_UPDIR, 0), 0);
					break;

				case MENU_DCLICK :
					if(hWndCurFocus == GetLocalHwnd())
						// ローカルフォルダを開く
//						DoubleClickProc(WIN_LOCAL, YES, -1);
						DoubleClickProc(WIN_LOCAL, NO, -1);
					else
					{
						SuppressRefresh = 1;
						// ローカルフォルダを開く
//						DoubleClickProc(WIN_REMOTE, YES, -1);
						DoubleClickProc(WIN_REMOTE, NO, -1);
						SuppressRefresh = 0;
					}
					break;

				// ローカルフォルダを開く
				case MENU_OPEN :
					if(hWndCurFocus == GetLocalHwnd())
						DoubleClickProc(WIN_LOCAL, YES, -1);
					else
					{
						SuppressRefresh = 1;
						DoubleClickProc(WIN_REMOTE, YES, -1);
						SuppressRefresh = 0;
					}
					break;

				case MENU_OPEN1 :
					if(hWndCurFocus == GetLocalHwnd())
						DoubleClickProc(WIN_LOCAL, YES, 0);
					else
					{
						SuppressRefresh = 1;
						DoubleClickProc(WIN_REMOTE, YES, 0);
						SuppressRefresh = 0;
					}
					break;

				case MENU_OPEN2 :
					if(hWndCurFocus == GetLocalHwnd())
						DoubleClickProc(WIN_LOCAL, YES, 1);
					else
					{
						SuppressRefresh = 1;
						DoubleClickProc(WIN_REMOTE, YES, 1);
						SuppressRefresh = 0;
					}
					break;

				case MENU_OPEN3 :
					if(hWndCurFocus == GetLocalHwnd())
						DoubleClickProc(WIN_LOCAL, YES, 2);
					else
					{
						SuppressRefresh = 1;
						DoubleClickProc(WIN_REMOTE, YES, 2);
						SuppressRefresh = 0;
					}
					break;

				case MENU_REMOTE_UPDIR :
					if (AskUserOpeDisabled())
						break;
					SuppressRefresh = 1;
					SetCurrentDirAsDirHist();
					ChangeDir(WIN_REMOTE, L".."s);
					SuppressRefresh = 0;
					break;

				case MENU_LOCAL_UPDIR :
					if (AskUserOpeDisabled())
						break;
					SetCurrentDirAsDirHist();
					ChangeDir(WIN_LOCAL, L".."s);
					break;

				case MENU_REMOTE_CHDIR :
					SuppressRefresh = 1;
					SetCurrentDirAsDirHist();
					ChangeDirDirectProc(WIN_REMOTE);
					SuppressRefresh = 0;
					break;

				case MENU_LOCAL_CHDIR :
					SetCurrentDirAsDirHist();
					ChangeDirDirectProc(WIN_LOCAL);
					break;

				case MENU_DOWNLOAD :
					SetCurrentDirAsDirHist();
					DownloadProc(NO, NO, NO);
					break;

				case MENU_DOWNLOAD_AS :
					SetCurrentDirAsDirHist();
					DownloadProc(YES, NO, NO);
					break;

				case MENU_DOWNLOAD_AS_FILE :
					SetCurrentDirAsDirHist();
					DownloadProc(NO, YES, NO);
					break;

				case MENU_DOWNLOAD_ALL :
					SetCurrentDirAsDirHist();
					DownloadProc(NO, NO, YES);
					break;

				case MENU_DOWNLOAD_NAME :
					SetCurrentDirAsDirHist();
					if (std::wstring path; InputDialog(downname_dlg, GetMainHwnd(), 0, path, FMAX_PATH))
						DirectDownloadProc(path);
					break;

				case MENU_UPLOAD :
					SetCurrentDirAsDirHist();
					UploadListProc(NO, NO);
					break;

				case MENU_UPLOAD_AS :
					SetCurrentDirAsDirHist();
					UploadListProc(YES, NO);
					break;

				case MENU_UPLOAD_ALL :
					SetCurrentDirAsDirHist();
					UploadListProc(NO, YES);
					break;

				case MENU_MIRROR_UPLOAD :
					SetCurrentDirAsDirHist();
					MirrorUploadProc(YES);
					break;

				case MENU_MIRROR_DOWNLOAD :
					SetCurrentDirAsDirHist();
					MirrorDownloadProc(YES);
					break;

				case MENU_FILESIZE :
					SetCurrentDirAsDirHist();
					CalcFileSizeProc();
					break;

				case MENU_DELETE :
					SuppressRefresh = 1;
					SetCurrentDirAsDirHist();
					DeleteProc();
					SuppressRefresh = 0;
					break;

				case MENU_RENAME :
					SuppressRefresh = 1;
					SetCurrentDirAsDirHist();
					RenameProc();
					SuppressRefresh = 0;
					break;

				case MENU_MKDIR :
					SuppressRefresh = 1;
					SetCurrentDirAsDirHist();
					MkdirProc();
					SuppressRefresh = 0;
					break;

				case MENU_CHMOD :
					SuppressRefresh = 1;
					ChmodProc();
					SuppressRefresh = 0;
					break;

				case MENU_SOMECMD :
					SuppressRefresh = 1;
					SomeCmdProc();
					SuppressRefresh = 0;
					break;

				case MENU_OPTION :
					SetOption();
					if(ListFont != NULL)
					{
						SendMessageW(GetLocalHwnd(), WM_SETFONT, (WPARAM)ListFont, MAKELPARAM(TRUE, 0));
						SendMessageW(GetRemoteHwnd(), WM_SETFONT, (WPARAM)ListFont, MAKELPARAM(TRUE, 0));
						SendMessageW(GetTaskWnd(), WM_SETFONT, (WPARAM)ListFont, MAKELPARAM(TRUE, 0));
					}
					GetLocalDirForWnd();
					DispTransferType();
					SetAllHistoryToMenu();
					break;

				case MENU_FILTER :
					// 同時接続対応
					CancelFlg = NO;
					SetFilter(&CancelFlg);
					break;

				case MENU_SORT :
					if(SortSetting() == YES)
					{
						// 同時接続対応
						CancelFlg = NO;
						Sort = AskSortType();
						ReSortDispList(WIN_LOCAL, &CancelFlg);
						ReSortDispList(WIN_REMOTE, &CancelFlg);
					}
					break;

				case MENU_EXIT :
					PostMessageW(hWnd, WM_CLOSE, 0, 0L);
					break;

				case MENU_AUTO_EXIT :
					if(AutoExit == YES)
						PostMessageW(hWnd, WM_CLOSE, 0, 0L);
					break;

				case MENU_ABOUT :
					AboutDialog(hWnd);
					break;

				case MENU_TEXT :
				case MENU_BINARY :
				case MENU_AUTO :
					SetTransferType(LOWORD(wParam));
					DispTransferType();
					break;

				case MENU_XFRMODE :
					switch(AskTransferType())
					{
						case TYPE_A :
							TmpTransType = MENU_BINARY;
							break;

						case TYPE_I :
							TmpTransType = MENU_AUTO;
							break;

						default :
							TmpTransType = MENU_TEXT;
							break;
					}
					SetTransferType(TmpTransType);
					DispTransferType();
					break;

				// UTF-8対応
				case MENU_KNJ_SJIS :
				case MENU_KNJ_EUC :
				case MENU_KNJ_JIS :
				case MENU_KNJ_UTF8N :
				case MENU_KNJ_UTF8BOM :
				case MENU_KNJ_NONE :
					SetHostKanjiCode(LOWORD(wParam));
					break;

				case MENU_L_KNJ_SJIS :
				case MENU_L_KNJ_EUC :
				case MENU_L_KNJ_JIS :
				case MENU_L_KNJ_UTF8N :
				case MENU_L_KNJ_UTF8BOM :
					SetLocalKanjiCode(LOWORD(wParam));
					break;

				case MENU_KANACNV :
					SetHostKanaCnv();
					break;

				case MENU_REFRESH :
					if (AskUserOpeDisabled())
						break;
					// 同時接続対応
					CancelFlg = NO;
					SuppressRefresh = 1;
					GetLocalDirForWnd();
					if(CheckClosedAndReconnect() == FFFTP_SUCCESS)
						GetRemoteDirForWnd(CACHE_REFRESH, &CancelFlg);
					SuppressRefresh = 0;
					break;

				case MENU_LIST :
					ListType = LVS_LIST;
					DispListType();
					SetListViewType();
					break;

				case MENU_REPORT :
					ListType = LVS_REPORT;
					DispListType();
					SetListViewType();
					break;

				case REFRESH_LOCAL :
					if (AskUserOpeDisabled())
						break;
					GetLocalDirForWnd();
					break;

				case REFRESH_REMOTE :
					if (AskUserOpeDisabled())
						break;
					// 同時接続対応
					CancelFlg = NO;
					SuppressRefresh = 1;
					if(CheckClosedAndReconnect() == FFFTP_SUCCESS)
						GetRemoteDirForWnd(CACHE_REFRESH, &CancelFlg);
					SuppressRefresh = 0;
					break;

				case COMBO_LOCAL :
				case COMBO_REMOTE :
					SuppressRefresh = 1;
					if(HIWORD(wParam) == CBN_SELCHANGE)
					{
						SetCurrentDirAsDirHist();
						ChangeDirComboProc((HWND)lParam);
					}
					else if(HIWORD(wParam) != CBN_CLOSEUP)
					{
						MakeButtonsFocus();
						SuppressRefresh = 0;
						return(0);
					}
					SuppressRefresh = 0;
					break;

				case MENU_HELP :
					ShowHelp(IDH_HELP_TOPIC_0000001);
					break;

				case MENU_HELP_TROUBLE :
					ShellExecuteW(0, L"open", WebURL, nullptr, nullptr, SW_SHOW);
					break;

				case MENU_BMARK_ADD :
					AddCurDirToBookMark(WIN_REMOTE);
					break;

				case MENU_BMARK_ADD_LOCAL :
					AddCurDirToBookMark(WIN_LOCAL);
					break;

				case MENU_BMARK_ADD_BOTH :
					AddCurDirToBookMark(WIN_BOTH);
					break;

				case MENU_BMARK_EDIT :
					EditBookMark();
					break;

				case MENU_SELECT_ALL :
					SelectFileInList(hWndCurFocus, SELECT_ALL, {});
					break;

				case MENU_SELECT :
					SelectFileInList(hWndCurFocus, SELECT_REGEXP, {});
					break;

				case MENU_FIND :
					FindFileInList(hWndCurFocus, FIND_FIRST);
					break;

				case MENU_FINDNEXT :
					FindFileInList(hWndCurFocus, FIND_NEXT);
					break;

				case MENU_DOTFILE :
					if (AskUserOpeDisabled())
						break;
					// 同時接続対応
					CancelFlg = NO;
					DotFile ^= 1;
					DispDotFileMode();
					GetLocalDirForWnd();
					GetRemoteDirForWnd(CACHE_LASTREAD, &CancelFlg);
					break;

				case MENU_SYNC :
					ToggleSyncMoveMode();
					break;

				case MENU_IMPORT_WS :
					ImportFromWSFTP();
					break;

				case MENU_REGSAVE :
					SaveRegistry();
					SaveSettingsToFile();
					break;

				case MENU_REGLOAD :
					if(LoadSettingsFromFile() == YES)
					{
						Message(IDS_NEED_RESTART, MB_OK);
						SaveExit = NO;
						PostMessageW(hWnd, WM_CLOSE, 0, 0L);
					}
					break;

				case MENU_REGINIT :
					if(Dialog(GetFtpInst(), reginit_dlg, hWnd))
					{
						ClearRegistry();
						// ポータブル版判定
						ClearIni();
						SaveExit = NO;
						PostMessageW(hWnd, WM_CLOSE, 0, 0L);
					}
					break;
				case MENU_CHANGEPASSWD:	/* 2010.01.31 genta */
					if( GetMasterPasswordStatus() != PASSWORD_OK )
					{
						/* 強制的に設定するか確認 */
						if (!Dialog(GetFtpInst(), forcepasschange_dlg, hWnd))
							break;
						if(EnterMasterPasswordAndSet(true, hWnd) != 0)
							Notice(IDS_MSGJPN303);
					}
					else if(GetMasterPasswordStatus() == PASSWORD_OK)
					{
						auto const password = GetMasterPassword();
						SetMasterPassword();
						while(ValidateMasterPassword() == YES && GetMasterPasswordStatus() == PASSWORD_UNMATCH)
						{
							if(EnterMasterPasswordAndSet(false, hWnd) == 0)
								break;
						}
						if(GetMasterPasswordStatus() == PASSWORD_OK && EnterMasterPasswordAndSet(true, hWnd) != 0)
						{
							Notice(IDS_MSGJPN303);
							SaveRegistry();
						}
						else
						{
							SetMasterPassword(password);
							ValidateMasterPassword();
						}
					}
					break;

				case MENU_DIRINFO :
					DispDirInfo();
					break;

				case MENU_TASKINFO :
					DispTaskMsg();
					break;

				case MENU_ABORT :
					CancelFlg = YES;
					if(AskTryingConnect() == NO)
						MainTransPkt.Abort = ABORT_USER;
					break;

				case MENU_OTPCALC :
					OtpCalcTool();
					break;

				// FTPS対応
				case MENU_FW_FTP_FILTER :
					TurnStatefulFTPFilter();
					break;

				case MENU_URL_COPY :
					CopyURLtoClipBoard();
					break;

				case MENU_APPKEY :
					if(hWndCurFocus == GetRemoteHwnd())
						ShowPopupMenu(WIN_REMOTE, 1);
					else if(hWndCurFocus == GetLocalHwnd())
						ShowPopupMenu(WIN_LOCAL, 1);
					break;

#if defined(HAVE_TANDEM)
				case MENU_SWITCH_OSS :
					SwitchOSSProc();
					break;
#endif

				// 上位のディレクトリへ移動対応
				case MENU_REMOTE_MOVE_UPDIR :
					MoveRemoteFileProc(-1);
					break;

				// FileZilla XML形式エクスポート対応
				case MENU_EXPORT_FILEZILLA_XML :
					// 平文で出力するためマスターパスワードを再確認
					if(GetMasterPasswordStatus() == PASSWORD_OK)
					{
						auto const password = GetMasterPassword();
						SetMasterPassword();
						while(ValidateMasterPassword() == YES && GetMasterPasswordStatus() == PASSWORD_UNMATCH)
						{
							if(EnterMasterPasswordAndSet(false, hWnd) == 0)
								break;
						}
						if(GetMasterPasswordStatus() == PASSWORD_OK)
							SaveSettingsToFileZillaXml();
						else
						{
							SetMasterPassword(password);
							ValidateMasterPassword();
						}
					}
					break;

				// WinSCP INI形式エクスポート対応
				case MENU_EXPORT_WINSCP_INI :
					// 平文で出力するためマスターパスワードを再確認
					if(GetMasterPasswordStatus() == PASSWORD_OK)
					{
						auto const password = GetMasterPassword();
						SetMasterPassword();
						while(ValidateMasterPassword() == YES && GetMasterPasswordStatus() == PASSWORD_UNMATCH)
						{
							if(EnterMasterPasswordAndSet(false, hWnd) == 0)
								break;
						}
						if(GetMasterPasswordStatus() == PASSWORD_OK)
							SaveSettingsToWinSCPIni();
						else
						{
							SetMasterPassword(password);
							ValidateMasterPassword();
						}
					}
					break;

				default :
					if((LOWORD(wParam) >= MENU_BMARK_TOP) &&
					   (LOWORD(wParam) < MENU_BMARK_TOP+100))
					{
						ChangeDirBmarkProc(LOWORD(wParam));
					}
					break;
			}
// 常にホストかローカルへフォーカスを移動
//			SetFocus(hWndCurFocus);
			MakeButtonsFocus();
			break;

		case WM_NOTIFY :
			if (NotifyStatusBar(reinterpret_cast<const NMHDR*>(lParam)))
				break;
			switch(((LPNMHDR)lParam)->code)
			{
				/* ツールチップコントロールメッセージの処理 */
				case TTN_GETDISPINFOW:
				{
					static constexpr std::tuple<int, int> map[] = {
						{ MENU_CONNECT, IDS_MSGJPN154 },
						{ MENU_QUICK, IDS_MSGJPN155 },
						{ MENU_DISCONNECT, IDS_MSGJPN156 },
						{ MENU_DOWNLOAD, IDS_MSGJPN157 },
#if defined(HAVE_TANDEM)
						{ MENU_DOWNLOAD_AS, IDS_MSGJPN065 },
						{ MENU_UPLOAD_AS, IDS_MSGJPN064 },
#endif
						{ MENU_UPLOAD, IDS_MSGJPN158 },
						{ MENU_MIRROR_UPLOAD, IDS_MSGJPN159 },
						{ MENU_DELETE, IDS_MSGJPN160 },
						{ MENU_RENAME, IDS_MSGJPN161 },
						{ MENU_MKDIR, IDS_MSGJPN162 },
						{ MENU_LOCAL_UPDIR, IDS_MSGJPN163 },
						{ MENU_REMOTE_UPDIR, IDS_MSGJPN163 },
						{ MENU_LOCAL_CHDIR, IDS_MSGJPN164 },
						{ MENU_REMOTE_CHDIR, IDS_MSGJPN164 },
						{ MENU_TEXT, IDS_MSGJPN165 },
						{ MENU_BINARY, IDS_MSGJPN166 },
						{ MENU_AUTO, IDS_MSGJPN167 },
						{ MENU_REFRESH, IDS_MSGJPN168 },
						{ MENU_LIST, IDS_MSGJPN169 },
						{ MENU_REPORT, IDS_MSGJPN170 },
						{ MENU_KNJ_SJIS, IDS_MSGJPN307 },
						{ MENU_KNJ_EUC, IDS_MSGJPN171 },
						{ MENU_KNJ_JIS, IDS_MSGJPN172 },
						{ MENU_KNJ_UTF8N, IDS_MSGJPN308 },
						{ MENU_KNJ_UTF8BOM, IDS_MSGJPN330 },
						{ MENU_KNJ_NONE, IDS_MSGJPN173 },
						{ MENU_L_KNJ_SJIS, IDS_MSGJPN309 },
						{ MENU_L_KNJ_EUC, IDS_MSGJPN310 },
						{ MENU_L_KNJ_JIS, IDS_MSGJPN311 },
						{ MENU_L_KNJ_UTF8N, IDS_MSGJPN312 },
						{ MENU_L_KNJ_UTF8BOM, IDS_MSGJPN331 },
						{ MENU_KANACNV, IDS_MSGJPN174 },
						{ MENU_SYNC, IDS_MSGJPN175 },
						{ MENU_ABORT, IDS_MSGJPN176 },
					};
					auto di = reinterpret_cast<NMTTDISPINFOW*>(lParam);
					for (auto [menuId, resourceId] : map) {
						if (di->hdr.idFrom == menuId) {
							di->lpszText = MAKEINTRESOURCEW(resourceId);
							di->hinst = GetFtpInst();
							break;
						}
					}
					break;
				}
				case LVN_COLUMNCLICK :
					if(((NMHDR *)lParam)->hwndFrom == GetLocalHwnd())
					{
						// 同時接続対応
						CancelFlg = NO;
						SetSortTypeByColumn(WIN_LOCAL, ((NM_LISTVIEW *)lParam)->iSubItem);
						ReSortDispList(WIN_LOCAL, &CancelFlg);
					}
					else if(((NMHDR *)lParam)->hwndFrom == GetRemoteHwnd())
					{
						if(((NM_LISTVIEW *)lParam)->iSubItem != 4)
						{
							// 同時接続対応
							CancelFlg = NO;
							SetSortTypeByColumn(WIN_REMOTE, ((NM_LISTVIEW *)lParam)->iSubItem);
							ReSortDispList(WIN_REMOTE, &CancelFlg);
						}
					}
					SetFocus(hWndCurFocus);
					break;

				case LVN_ITEMCHANGED :
					{
						// SetTimerによるとnIDEventが一致する既存のタイマーを置き換えるとのこと <https://msdn.microsoft.com/en-us/library/ms644906(v=vs.85).aspx>
						// この通りであれば問題ない。ただしCWnd::SetTimerによると新たなタイマーが作成される（＝既存のタイマーを置き換えない）とのこと
						// <https://docs.microsoft.com/ja-jp/cpp/mfc/reference/cwnd-class#settimer>
						auto const id = SetTimer(hWnd, 3, USER_TIMER_MINIMUM, [](auto hWnd, auto, auto, auto) {
							DispSelectedSpace();
							MakeButtonsFocus();
							auto const result = KillTimer(hWnd, 3);
							assert(result);
						});
						assert(id == 3);
					}
					break;
			}
			break;

		case WM_SIZE :
			Sizing = SW_RESTORE;
			if(wParam == SIZE_RESTORED)
			{
				ResizeWindowProc();
				GetWindowRect(hWnd, &Rect);
				WinPosX = Rect.left;
				WinPosY = Rect.top;
			}
			else if(wParam == SIZE_MAXIMIZED)
			{
				Sizing = SW_MAXIMIZE;
				ResizeWindowProc();
			}
			else
				return DefWindowProcW(hWnd, message, wParam, lParam);
			break;

		case WM_MOVING :
			WinPosX = ((RECT *)lParam)->left;
			WinPosY = ((RECT *)lParam)->top;
			return DefWindowProcW(hWnd, message, wParam, lParam);

		case WM_SETFOCUS :
			SetFocus(hWndCurFocus);
			break;

		case WM_LBUTTONDOWN :
		case WM_LBUTTONUP :
		case WM_MOUSEMOVE :
			CheckResizeFrame(wParam, LOWORD(lParam), HIWORD(lParam));
			break;

		case WM_CHANGE_COND :
			DispTransferFiles();
			break;

		case WM_REFRESH_LOCAL_FLG :
			// 外部アプリケーションへドロップ後にローカル側のファイル一覧に作業フォルダが表示されるバグ対策
			if(SuppressRefresh == 0)
				PostMessageW(hWnd,  WM_COMMAND, MAKEWPARAM(REFRESH_LOCAL, 0), 0);
			break;

		case WM_REFRESH_REMOTE_FLG :
			if(SuppressRefresh == 0)
				PostMessageW(hWnd,  WM_COMMAND, MAKEWPARAM(REFRESH_REMOTE, 0), 0);
			break;

		// 同時接続対応
		case WM_RECONNECTSOCKET :
			ReconnectProc();
			break;

		case WM_MAINTHREADRUNNER:
			return reinterpret_cast<MainThreadRunner*>(lParam)->Run();

		case WM_PAINT :
			BeginPaint(hWnd, (LPPAINTSTRUCT) &ps);
			EndPaint(hWnd, (LPPAINTSTRUCT) &ps);
			break;

		case WM_DESTROY :
			// ローカル側自動更新
			KillTimer(hWnd, 1);
			if(ChangeNotification != INVALID_HANDLE_VALUE)
				FindCloseChangeNotification(ChangeNotification);
			// タスクバー進捗表示
			KillTimer(hWnd, 2);
			PostQuitMessage(0);
			break;

		case WM_QUERYENDSESSION :
			ExitProc(hWnd);
			return(TRUE);

		case WM_CLOSE :
			if (AskTransferNow() == NO || Dialog(GetFtpInst(), exit_dlg, hWnd)) {
				ExitProc(hWnd);
				return DefWindowProcW(hWnd, message, wParam, lParam);
			}
			break;

		default :
			return DefWindowProcW(hWnd, message, wParam, lParam);
	}
	return(0L);
}


// プログラム開始時の処理
static void StartupProc(std::vector<std::wstring_view> const& args) {
	std::wstring hostname;
	std::wstring unc;
	bool initializeDeferred = false;
	if (auto result = AnalyzeComLine(args, hostname, unc)) {
		int const opt = *result;
		int const Kanji = opt & OPT_UTF8BOM ? KANJI_UTF8BOM : opt & OPT_UTF8N ? KANJI_UTF8N : opt & OPT_SJIS ? KANJI_SJIS : opt & OPT_JIS ? KANJI_JIS : opt & OPT_EUC ? KANJI_EUC : KANJI_NOCNV;
		int const Kana = opt & OPT_KANA ? NO : YES;
		int const FnameKanji = opt & OPT_UTF8N_NAME ? KANJI_UTF8N : opt & OPT_SJIS_NAME ? KANJI_SJIS : opt & OPT_JIS_NAME ? KANJI_JIS : opt & OPT_EUC_NAME ? KANJI_EUC : KANJI_NOCNV;
		int const TrMode = opt & OPT_BINARY ? TYPE_I : opt & OPT_ASCII ? TYPE_A : TYPE_DEFAULT;
		if (opt & OPT_QUIT)
			AutoExit = YES;
		if (opt & OPT_SAVEOFF)
			SuppressSave = YES;
		if (opt & OPT_SAVEON)
			SuppressSave = NO;
		if (empty(hostname) && empty(unc)) {
			if (ConnectOnStart == YES && IsWindowVisible(GetMainHwnd()))
				PostMessageW(GetMainHwnd(), WM_COMMAND, MAKEWPARAM(MENU_CONNECT, 0), 0);// 起動時（引数で接続ホスト名を指定しなかった場合）、ホスト一覧ダイアログを表示するためのメッセージを飛ばす
		} else if (empty(hostname) && !empty(unc)) {
			DirectConnectProc(std::move(unc), Kanji, Kana, FnameKanji, TrMode);
		} else if (!empty(hostname) && empty(unc)) {
			if (int const AutoConnect = SearchHostName(hostname); AutoConnect == -1)
				Notice(IDS_MSGJPN177, hostname);
			else {
				initializeDeferred = true;
				PostMessageW(GetMainHwnd(), WM_COMMAND, MAKEWPARAM(MENU_CONNECT_NUM, opt), (LPARAM)AutoConnect);
			}
		} else {
			Notice(IDS_MSGJPN179);
		}
	}
	if (!initializeDeferred)
		SetEvent(initialized);
}


// コマンドラインを解析
static std::optional<int> AnalyzeComLine(std::vector<std::wstring_view> const& args, std::wstring& hostname, std::wstring& unc) {
	const std::map<std::wstring_view, int> map{
		{ L"-m"sv, OPT_MIRROR }, { L"--mirror"sv, OPT_MIRROR },
		{ L"-d"sv, OPT_MIRRORDOWN }, { L"--mirrordown"sv, OPT_MIRRORDOWN },
		{ L"-eu"sv, OPT_EUC }, { L"-e"sv, OPT_EUC }, { L"--euc"sv, OPT_EUC },
		{ L"-ji"sv, OPT_JIS }, { L"-j"sv, OPT_JIS }, { L"--jis"sv, OPT_JIS },
		{ L"-a"sv, OPT_ASCII }, { L"--ascii"sv, OPT_ASCII },
		{ L"-b"sv, OPT_BINARY }, { L"--binary"sv, OPT_BINARY },
		{ L"-x"sv, OPT_AUTO }, { L"--auto"sv, OPT_AUTO },
		{ L"-f"sv, OPT_FORCE }, { L"--force"sv, OPT_FORCE },
		{ L"-q"sv, OPT_QUIT }, { L"--quit"sv, OPT_QUIT },
		{ L"-k"sv, OPT_KANA }, { L"--kana"sv, OPT_KANA },
		{ L"-eun"sv, OPT_EUC_NAME }, { L"-u"sv, OPT_EUC_NAME }, { L"--eucname"sv, OPT_EUC_NAME },
		{ L"-jin"sv, OPT_JIS_NAME }, { L"-i"sv, OPT_JIS_NAME }, { L"--jisname"sv, OPT_JIS_NAME },
		{ L"--saveoff"sv, OPT_SAVEOFF },
		{ L"--saveon"sv, OPT_SAVEON },
		{ L"-sj"sv, OPT_SJIS }, { L"--sjis"sv, OPT_SJIS },
		{ L"-u8"sv, OPT_UTF8N }, { L"--utf8"sv, OPT_UTF8N },
		{ L"-8b"sv, OPT_UTF8BOM }, { L"--utf8bom"sv, OPT_UTF8BOM },
		{ L"-sjn"sv, OPT_SJIS_NAME }, { L"--sjisname"sv, OPT_SJIS_NAME },
		{ L"-u8n"sv, OPT_UTF8N_NAME }, { L"--utf8name"sv, OPT_UTF8N_NAME },
	};
	int option = 0;
	for (auto it = begin(args); it != end(args); ++it) {
		if ((*it)[0] == L'-') {
			auto key = lc(std::wstring{ *it });
			if (auto const mapit = map.find(key); mapit != end(map)) {
				option |= mapit->second;
			} else if (key == L"-n"sv || key == L"--ini"sv) {
				if (++it == end(args)) {
					// '-n'や'--ini'を指定しているにもかかわらず、INIファイル名を指定していない
					Notice(IDS_MSGJPN282);
					return {};
				}
			} else if (key == L"-z"sv || key == L"--mpasswd"sv) {
				if (++it == end(args)) {
					// '-z'や'--mpasswd'を指定しているにもかかわらず、マスターパスワードを指定していない
					Notice(IDS_MSGJPN299);
					return {};
				}
			} else if (key == L"-s"sv || key == L"--set"sv) {
				if (++it == end(args)) {
					// '-s'や'--set'を指定しているにもかかわらず、登録ホスト名を指定していない
					Notice(IDS_MSGJPN178);
					return {};
				}
				hostname = *it;
			} else if (key == L"-h"sv || key == L"--help"sv) {
				// HTMLヘルプファイルを開く
				ShowHelp(IDH_HELP_TOPIC_0000024);
			} else {
				Notice(IDS_MSGJPN180, *it);
				return {};
			}
		} else
			unc = *it;
	}
	return option;
}


/*----- プログラム終了時の処理 ------------------------------------------------
*
*	Parameter
*		HWND hWnd : ウインドウハンドル
*
*	Return Value
*		なし
*----------------------------------------------------------------------------*/

static void ExitProc(HWND hWnd)
{
	CancelFlg = YES;

	// バグ対策
	DisableUserOpe();

	CloseTransferThread();

	if(SaveExit == YES)
	{
		SaveBookMark();
		SaveCurrentSetToHost();
	}
	DeleteAlltempFile();

//	WSACancelBlockingCall();
	DisconnectProc();
//	CloseTransferThread();

	if(SaveExit == YES)
	{
		SaveRegistry();
		// ポータブル版判定
		if(RegType == REGTYPE_REG)
			ClearIni();
	}

	fs::remove_all(tempDirectory());

	if(RasClose == YES)
	{
		DisconnectRas(RasCloseNotify != NO);
	}
	DeleteAllObject();
	__pragma(warning(suppress:6387)) HtmlHelpW(NULL, NULL, HH_UNINITIALIZE, dwCookie);
	return;
}


// ファイル名をダブルクリックしたときの処理
//   Win : ウインドウ番号 (WIN_xxx)
//   Mode : 常に「開く」動作をするかどうか (YES/NO)
//   App : アプリケーション番号（-1=関連づけ優先）
void DoubleClickProc(int Win, int Mode, int App) {
	if (!AskUserOpeDisabled()) {
		SetCurrentDirAsDirHist();
		if (int Pos; GetSelectedCount(Win) == 1 && (Pos = GetFirstSelected(Win, NO)) != -1) {
			auto const& item = GetItem(Win, Pos);
			if (Win == WIN_LOCAL) {
				if (App != -1 || item.Node == NODE_FILE || Mode == YES) {
					if (DclickOpen == YES || Mode == YES)
						ExecViewer(AskLocalCurDir() / item.Name, App);
					else
						PostMessageW(GetMainHwnd(), WM_COMMAND, MAKEWPARAM(MENU_UPLOAD, 0), 0);
				} else
					ChangeDir(WIN_LOCAL, item.Name);
			} else if (CheckClosedAndReconnect() == FFFTP_SUCCESS) {
				if (App != -1 || item.Node == NODE_FILE) {
					if (DclickOpen == YES || Mode == YES) {
						// ビューワ２、３のパスが "d " で始まっていたら差分ビューア使用
						auto const UseDiffViewer = (App == 1 || App == 2) && ViewerName[App].starts_with(L"d "sv);

						auto remoteDir = tempDirectory() / L"file";
						fs::create_directory(remoteDir);
						auto remotePath = remoteDir / (UseDiffViewer ? L"remote." + item.Name : item.Name);

						if (AskTransferNow() == YES)
							SktShareProh();

						MainTransPkt.Command = L"RETR "s;
						MainTransPkt.Remote = AskHostType() == HTYPE_ACOS ? std::format(L"'{}({})'"sv, GetConnectingHost().LsName, item.Name) : item.Name;
						MainTransPkt.Local = remotePath;
						MainTransPkt.Type = AskTransferTypeAssoc(MainTransPkt.Remote, AskTransferType());
						MainTransPkt.Size = 1;
						MainTransPkt.KanjiCode = AskHostKanjiCode();
						MainTransPkt.KanjiCodeDesired = AskLocalKanjiCode();
						MainTransPkt.KanaCnv = AskHostKanaCnv();
						MainTransPkt.Mode = EXIST_OVW;
						// ミラーリング設定追加
						MainTransPkt.NoTransfer = NO;
						MainTransPkt.ExistSize = 0;
						MainTransPkt.hWndTrans = NULL;

						/* 不正なパスを検出 */
						int Sts = 0;
						DisableUserOpe();
						if (CheckPathViolation(MainTransPkt) == NO) {
							CancelFlg = NO;
							Sts = DoDownload(AskCmdCtrlSkt(), MainTransPkt, NO, &CancelFlg);
							if (MarkAsInternet == YES && IsZoneIDLoaded() == YES)
								MarkFileAsDownloadedFromInternet(remotePath);
						}
						EnableUserOpe();

						AddTempFileList(remotePath);
						if (Sts / 100 == FTP_COMPLETE) {
							if (UseDiffViewer)
								ExecViewer2(AskLocalCurDir() / item.Name, remotePath, App);
							else
								ExecViewer(remotePath, App);
						}
					} else
						PostMessageW(GetMainHwnd(), WM_COMMAND, MAKEWPARAM(MENU_DOWNLOAD, 0), 0);
				} else
					ChangeDir(WIN_REMOTE, item.Name);
			}
		}
		MakeButtonsFocus();
	}
}


// フォルダの移動
static void ChangeDir(int Win, std::wstring dir) {
	CancelFlg = NO;
	DisableUserOpe();
	int Sync = AskSyncMoveMode();
	if (Sync == YES && dir == L".."sv && AskLocalCurDir().filename() != GetFileName(AskRemoteCurDir()))
		Sync = NO;
	if (Win == WIN_LOCAL || Sync == YES) {
		if (DoLocalCWD(dir) == FFFTP_SUCCESS)
			GetLocalDirForWnd();
	}
	if (Win == WIN_REMOTE || Sync == YES) {
		if (CheckClosedAndReconnect() == FFFTP_SUCCESS) {
#if defined(HAVE_OPENVMS)
			/* OpenVMSの場合、".DIR;?"を取る */
			if (AskHostType() == HTYPE_VMS)
				dir = ReformVMSDirName(std::move(dir));
#endif
			if (DoCWD(dir, YES, NO, YES) < FTP_RETRY)
				GetRemoteDirForWnd(CACHE_NORMAL, &CancelFlg);
		}
	}
	EnableUserOpe();
}


/*----- ウインドウのサイズ変更の処理 ------------------------------------------
*
*	Parameter
*		なし
*
*	Return Value
*		なし
*----------------------------------------------------------------------------*/

static void ResizeWindowProc(void)
{
	RECT Rect;

	GetClientRect(GetMainHwnd(), &Rect);
	SendMessageW(GetSbarWnd(), WM_SIZE, SIZE_RESTORED, MAKELPARAM(Rect.right, Rect.bottom));

	CalcWinSize();
	SetWindowPos(GetMainTbarWnd(), 0, 0, 0, Rect.right, AskToolWinHeight(), SWP_NOACTIVATE | SWP_NOZORDER);
	SetWindowPos(GetLocalTbarWnd(), 0, 0, AskToolWinHeight(), LocalWidth, AskToolWinHeight(), SWP_NOACTIVATE | SWP_NOZORDER);
	SetWindowPos(GetRemoteTbarWnd(), 0, LocalWidth + SepaWidth, AskToolWinHeight(), RemoteWidth, AskToolWinHeight(), SWP_NOACTIVATE | SWP_NOZORDER);
	SendMessageW(GetLocalTbarWnd(), TB_GETITEMRECT, 3, (LPARAM)&Rect);
	SetWindowPos(GetLocalHistHwnd(), 0, Rect.right, Rect.top, LocalWidth - Rect.right, 200, SWP_NOACTIVATE | SWP_NOZORDER);
	SendMessageW(GetRemoteTbarWnd(), TB_GETITEMRECT, 3, (LPARAM)&Rect);
	SetWindowPos(GetRemoteHistHwnd(), 0, Rect.right, Rect.top, RemoteWidth - Rect.right, 200, SWP_NOACTIVATE | SWP_NOZORDER);
	SetWindowPos(GetLocalHwnd(), 0, 0, AskToolWinHeight()*2, LocalWidth, ListHeight, SWP_NOACTIVATE | SWP_NOZORDER);
	SetWindowPos(GetRemoteHwnd(), 0, LocalWidth + SepaWidth, AskToolWinHeight()*2, RemoteWidth, ListHeight, SWP_NOACTIVATE | SWP_NOZORDER);
	SetWindowPos(GetTaskWnd(), 0, 0, AskToolWinHeight()*2+ListHeight+SepaWidth, ClientWidth, TaskHeight, SWP_NOACTIVATE | SWP_NOZORDER);
}


/*----- ウインドウの各部分のサイズを計算する ----------------------------------
*
*	Parameter
*		なし
*
*	Return Value
*		なし
*----------------------------------------------------------------------------*/

static void CalcWinSize(void)
{
	RECT Rect;

	GetWindowRect(GetMainHwnd(), &Rect);
	// メインウィンドウの非クライアント領域を含めた全体の幅と高さを計算
	if(Sizing != SW_MAXIMIZE)
	{
		WinWidth = Rect.right - Rect.left;
		WinHeight = Rect.bottom - Rect.top;
	}

	// クライアント領域の幅と高さを計算
	GetClientRect(GetMainHwnd(), &Rect);

	ClientWidth = Rect.right;
	int const ClientHeight = Rect.bottom;

	SepaWidth = 4; // ローカル側とリモート側のファイルリストを隔てるセパレータの幅
	LocalWidth = std::clamp(LocalWidth, 0, ClientWidth - SepaWidth); // ローカル側のファイルストの幅を計算？
	RemoteWidth = std::max(0, ClientWidth - LocalWidth - SepaWidth); // リモート側のファイルストの幅を計算？

	GetClientRect(GetSbarWnd(), &Rect);

	ListHeight = std::max(0L, ClientHeight - AskToolWinHeight() * 2 - TaskHeight - SepaWidth - Rect.bottom); // ファイルリスト全体の高さを計算？
}


/*----- ディレクトリリストとファイルリストの境界変更処理 ----------------------
*
*	Parameter
*		WPARAM Keys : WM_MOUSEMOVEなどのWPARAMの値
*		int x : マウスカーソルのＸ座標
*		int y : マウスカーソルのＹ座標
*
*	Return Value
*		なし
*----------------------------------------------------------------------------*/

static void CheckResizeFrame(WPARAM Keys, int x, int y)
{
	static auto sizewe = LoadCursorW(0, IDC_SIZEWE);
	static auto sizens = LoadCursorW(0, IDC_SIZENS);
	static auto arrow = LoadCursorW(0, IDC_ARROW);
	RECT Rect;
	RECT Rect1;

	if((Resizing == RESIZE_OFF) && (Keys == 0))
	{
		if((x >= LocalWidth) && (x <= LocalWidth + SepaWidth) &&
		   (y > AskToolWinHeight()) && (y < (AskToolWinHeight() * 2 + ListHeight)))
		{
			/* 境界位置変更用カーソルに変更 */
			SetCapture(GetMainHwnd());
			SetCursor(sizewe);
			Resizing = RESIZE_PREPARE;
			ResizePos = RESIZE_HPOS;
		}
		else if((y >= AskToolWinHeight()*2+ListHeight) && (y <= AskToolWinHeight()*2+ListHeight+SepaWidth))
		{
			/* 境界位置変更用カーソルに変更 */
			SetCapture(GetMainHwnd());
			SetCursor(sizens);
			Resizing = RESIZE_PREPARE;
			ResizePos = RESIZE_VPOS;
		}
	}
	else if(Resizing == RESIZE_PREPARE)
	{
		if(Keys & MK_LBUTTON)
		{
			/* 境界位置変更開始 */
			Resizing = RESIZE_ON;
			GetWindowRect(GetMainHwnd(), &Rect);
			GetClientRect(GetSbarWnd(), &Rect1);
			Rect.left += GetSystemMetrics(SM_CXFRAME);
			Rect.right -= GetSystemMetrics(SM_CXFRAME);
			Rect.top += AskToolWinHeight()*2 + GetSystemMetrics(SM_CYMENU) + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYFRAME);
			Rect.bottom -= GetSystemMetrics(SM_CYFRAME) + Rect1.bottom;
			ClipCursor(&Rect);
		}
		else
		{
			if(((ResizePos == RESIZE_HPOS) &&
				((x < LocalWidth) || (x > LocalWidth + SepaWidth) ||
				 (y <= AskToolWinHeight()) || (y >= (AskToolWinHeight() * 2 + ListHeight)))) ||
			   ((ResizePos == RESIZE_VPOS) &&
				((y < AskToolWinHeight()*2+ListHeight) || (y > AskToolWinHeight()*2+ListHeight+SepaWidth))))
			{
				/* 元のカーソルに戻す */
				ReleaseCapture();
				SetCursor(arrow);
				Resizing = RESIZE_OFF;
			}
		}
	}
	else if(Resizing == RESIZE_ON)
	{
		if(ResizePos == RESIZE_HPOS)
			LocalWidth = x;
		else
		{
			GetClientRect(GetMainHwnd(), &Rect);
			GetClientRect(GetSbarWnd(), &Rect1);
			TaskHeight = std::max(0L, Rect.bottom - y - Rect1.bottom);
		}
		ResizeWindowProc();

		if((Keys & MK_LBUTTON) == 0)
		{
			/* 境界位置変更終了 */
			ReleaseCapture();
			ClipCursor(NULL);
			SetCursor(arrow);
			Resizing = RESIZE_OFF;
		}
	}
	return;
}


// ファイル一覧情報をビューワで表示
static void DispDirInfo() {
	ExecViewer(MakeCacheFileName(0), 0);
}


// ビューワを起動
void ExecViewer(fs::path const& path, int App) {
	/* FindExecutable()は関連付けられたプログラムのパス名にスペースが	*/
	/* 含まれている時、間違ったパス名を返す事がある。					*/
	/* そこで、関連付けられたプログラムの起動はShellExecute()を使う。	*/
	if (wchar_t result[MAX_PATH]; App == -1 && path.has_extension() && FindExecutableW(path.c_str(), nullptr, result) > (HINSTANCE)32) {
		// 拡張子があるので関連付けを実行する
		Debug(L"ShellExecute - {}"sv, path.native());
		ShellExecuteW(0, L"open", path.c_str(), nullptr, AskLocalCurDir().c_str(), SW_SHOW);
	} else if (App == -1 && (GetFileAttributesW(path.c_str()) & FILE_ATTRIBUTE_DIRECTORY)) {
		// ディレクトリなのでフォルダを開く
		auto wComLine = MakeDistinguishableFileName(fs::path{ path });
		Debug(L"ShellExecute - {}"sv, path.native());
		ShellExecuteW(0, L"open", wComLine.c_str(), nullptr, path.c_str(), SW_SHOW);
	} else {
		auto commandLine = std::format(LR"({} "{}")"sv, ViewerName[App == -1 ? 0 : App], path.native());
		Debug(L"CreateProcess - {}"sv, commandLine);
		STARTUPINFOW si{ sizeof(STARTUPINFOW), nullptr, nullptr, nullptr, 0, 0, 0, 0, 0, 0, 0, 0, SW_SHOWNORMAL };
		if (ProcessInformation pi; __pragma(warning(suppress:6335)) !CreateProcessW(nullptr, data(commandLine), nullptr, nullptr, false, 0, nullptr, systemDirectory().c_str(), &si, &pi)) {
			Notice(IDS_MSGJPN182, GetLastError());
			Notice(IDS_LOCALCMD, commandLine);
		}
	}
}


// 差分表示ビューワを起動
void ExecViewer2(fs::path const& path1, fs::path const& path2, int App) {
	/* FindExecutable()は関連付けられたプログラムのパス名にスペースが	*/
	/* 含まれている時、間違ったパス名を返す事がある。					*/
	/* そこで、関連付けられたプログラムの起動はShellExecute()を使う。	*/
	auto const format = path1.native().find(L' ') == std::wstring::npos && path2.native().find(L' ') == std::wstring::npos ? LR"({} {} {})"sv : LR"({} "{}" "{}")"sv;
	auto const executable = std::wstring_view{ ViewerName[App] }.substr(2);		/* 先頭の "d " は読み飛ばす */
	auto commandLine = std::vformat(format, std::make_wformat_args(executable, path1.native(), path2.native()));
	Debug(L"FindExecutable - {}"sv, commandLine);
	STARTUPINFOW si{ sizeof(STARTUPINFOW), nullptr, nullptr, nullptr, 0, 0, 0, 0, 0, 0, 0, 0, SW_SHOWNORMAL };
	if (ProcessInformation pi; __pragma(warning(suppress:6335)) !CreateProcessW(nullptr, data(commandLine), nullptr, nullptr, false, 0, nullptr, systemDirectory().c_str(), &si, &pi)) {
		Notice(IDS_MSGJPN182, GetLastError());
		Notice(IDS_LOCALCMD, commandLine);
	}
}


// テンポラリファイル名をテンポラリファイルリストに追加
void AddTempFileList(fs::path const& file) {
	TempFiles.push_back(file);
}


// テンポラリファイルリストに登録されているファイルを全て削除
static void DeleteAlltempFile() {
	for (auto const& file : TempFiles)
		fs::remove(file);
	doDeleteRemoteFile();
}


// Ａｂｏｕｔダイアログボックス
static void AboutDialog(HWND hWnd) noexcept {
	struct About {
		using result_t = int;
		static INT_PTR OnInit(HWND hDlg) noexcept {
			SendDlgItemMessageW(hDlg, ABOUT_URL, EM_LIMITTEXT, 256, 0);
			SetText(hDlg, ABOUT_URL, WebURL);
			return TRUE;
		}
		static void OnCommand(HWND hDlg, WORD id) noexcept {
			switch (id) {
			case IDOK:
			case IDCANCEL:
				EndDialog(hDlg, 0);
				break;
			}
		}
	};
	Dialog(GetFtpInst(), about_dlg, hWnd, About{});
}


void ShowHelp(DWORD_PTR helpTopicId) {
	hHelpWin = HtmlHelpW(NULL, helpPath().c_str(), HH_HELP_CONTEXT, helpTopicId);
}


// INIファイルのパス名を返す
fs::path const& AskIniFilePath() noexcept {
	return IniPath;
}


// INIファイルのみを使うかどうかを返す
int AskForceIni() noexcept {
	return ForceIni;
}


// メッセージ処理
int BackgrndMessageProc() noexcept {
	MSG Msg;
	int Ret;

	Ret = NO;
	while(PeekMessageW(&Msg, NULL, 0, 0, PM_REMOVE))
	{
		if(!IsMainThread() || __pragma(warning(suppress:6387)) !HtmlHelpW(NULL, NULL, HH_PRETRANSLATEMESSAGE, (DWORD_PTR)&Msg))
		{
			/* ディレクトリ名の表示コンボボックスでBSやRETが効くように */
			/* コンボボックス内ではアクセラレータを無効にする */
			if((Msg.hwnd == GetLocalHistEditHwnd()) ||
			   (Msg.hwnd == GetRemoteHistEditHwnd()) ||
			   ((hHelpWin != NULL) && (Msg.hwnd == hHelpWin)) ||
				AskUserOpeDisabled() ||
			   (TranslateAcceleratorW(GetMainHwnd(), Accel, &Msg) == 0))
			{
				if(Msg.message == WM_QUIT)
				{
					Ret = YES;
					PostQuitMessage(0);
					break;
				}
				TranslateMessage(&Msg);
				DispatchMessageW(&Msg);
			}
		}
	}
	return(Ret);
}


// 自動終了フラグをクリアする
void ResetAutoExitFlg() noexcept {
	AutoExit = NO;
}


// 自動終了フラグを返す
int AskAutoExit() noexcept {
	return AutoExit;
}

static bool MasterPasswordInputDialog(int dialogId, HWND parent, UINT titleId, std::wstring& text, size_t maxlength = 0, int* flag = nullptr, int helpTopicId = IDH_HELP_TOPIC_0000001) noexcept {
	bool ret = false;
	const wchar_t* outpasswd = nullptr;
	switch (dialogId)
	{
	case masterpasswd_dlg:
		ret = AskMasterPassword_func(&outpasswd);
		break;
	case newmasterpasswd_dlg:
		ret = AskMasterPassword2nd_func(&outpasswd);
		break;
	default:
		break;
	}
	if (ret)
		text = outpasswd;
	return ret;
}

// ユーザにパスワードを入力させ，それを設定する
//   0/ユーザキャンセル, 1/設定した, 2/デフォルト設定
int EnterMasterPasswordAndSet(bool newpassword, HWND hWnd) {
	std::wstring pass1;
	if (!MasterPasswordInputDialog(newpassword ? newmasterpasswd_dlg : masterpasswd_dlg, hWnd, 0, pass1, MAX_PASSWORD_LEN + 1, nullptr, IDH_HELP_TOPIC_0000064))
		return 0;
	if (newpassword) {
		// 新しいパスワードを2回入力させる
		if (std::wstring pass2; !InputDialog(newmasterpasswd_dlg, hWnd, 0, pass2, MAX_PASSWORD_LEN + 1, nullptr, IDH_HELP_TOPIC_0000064))
			return 0;
		else if (pass1 != pass2) {
			Message(hWnd, IDS_PASSWORD_ISNOT_IDENTICAL, MB_OK | MB_ICONERROR);
			return 0;
		}
	}

	/* 末尾の空白を削除 */
	if (auto const pos = pass1.find_last_not_of(L' '); pos != std::wstring::npos && pos + 1 != size(pass1))
		pass1.erase(pos + 1);
	/* 先頭の空白を削除 */
	if (auto const pos = pass1.find_first_not_of(L' '); pos != std::wstring::npos && pos != 0)
		pass1.erase(0, pos);

	if (empty(pass1)) {
		/* 空の場合はデフォルト値を設定 */
		SetMasterPassword();
		return 2;
	}
	SetMasterPassword(pass1);
	return 1;
}

// マルチコアCPUの特定環境下でファイル通信中にクラッシュするバグ対策
BOOL IsMainThread() noexcept {
	if(GetCurrentThreadId() != MainThreadId)
		return FALSE;
	return TRUE;
}

void Restart() noexcept {
	STARTUPINFOW si;
	GetStartupInfoW(&si);
	ProcessInformation pi;
	__pragma(warning(suppress:6335)) CreateProcessW(nullptr, GetCommandLineW(), nullptr, nullptr, false, 0, nullptr, nullptr, &si, &pi);
}

void Terminate() noexcept {
	exit(1);
}

// タスクバー進捗表示
static ComPtr<ITaskbarList3> taskbarList;

int LoadTaskbarList3() noexcept {
	if (CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_ALL, IID_PPV_ARGS(&taskbarList)) == S_OK)
		return FFFTP_SUCCESS;
	return FFFTP_FAIL;
}

void FreeTaskbarList3() {
	taskbarList.Reset();
}

int IsTaskbarList3Loaded() noexcept {
	return taskbarList ? YES : NO;
}

void UpdateTaskbarProgress() {
	if (AskTransferSizeTotal() > 0) {
		taskbarList->SetProgressState(GetMainHwnd(), 0 < AskTransferErrorDisplay() ? TBPF_ERROR : TBPF_NORMAL);
		taskbarList->SetProgressValue(GetMainHwnd(), (ULONGLONG)(AskTransferSizeTotal() - AskTransferSizeLeft()), (ULONGLONG)AskTransferSizeTotal());
	} else
		taskbarList->SetProgressState(GetMainHwnd(), TBPF_NOPROGRESS);
}

// 高DPI対応
int AskToolWinHeight() noexcept {
	return(ToolWinHeight);
}

int MainThreadRunner::Run() {
	return IsMainThread() ? DoWork() : (int)SendMessageW(GetMainHwnd(), WM_MAINTHREADRUNNER, 0, (LPARAM)this);
}

// libffftpのために用意されたインターフェース
namespace libffftp {

static const wchar_t* const kModuleName = L"libffftp";

bool initialize() {
	hInstFtp = GetModuleHandleW(kModuleName);

	Sound::Register();

	// マルチコアCPUの特定環境下でファイル通信中にクラッシュするバグ対策
#ifdef DISABLE_MULTI_CPUS
	SetProcessAffinityMask(GetCurrentProcess(), 1);
#endif
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

void finalize() {
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

const wchar_t* getApplicationName() {
	return AppName;
}

void getWindowTitle(std::wstring& title) {
	title = GetWindowTitle();
}

}
