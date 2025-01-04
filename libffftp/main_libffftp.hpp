//--------------------------------------------------------------------------------------------------
#ifdef LIBFFFTP_INCLUDE_MAIN_version
// リソースIDである"notify"がQCoreApplicationのメソッド名とバッティングしている。悲しい
#undef notify
#include <QCoreApplication>
#define notify 166

namespace {
constexpr const wchar_t* const kVersion{L"5.8"};
}
fs::path const& systemDirectory() {
  static fs::path ret{};
  return ret;
}

static fs::path const& moduleFileName() {
  static fs::path ret{QCoreApplication::applicationFilePath().toStdWString()};
  return ret;
}

fs::path const& tempDirectory() {
  static auto const directory = [] {
    auto const path = fs::temp_directory_path() / std::format(L"ffftp{:08x}"sv, QCoreApplication::applicationPid());
    fs::create_directory(path);
    return path;
  }();
  return directory;
}

static const auto& version() {
  static std::wstring ret{kVersion};
  return ret;
}

const std::wstring& GetWindowTitle() {
  static std::wstring ret{};
  ret = std::vformat(AskConnecting() == YES ? L"{0} ({1}) - FFFTP"sv : L"FFFTP ({1})"sv, std::make_wformat_args(TitleHostName, FilterStr));
  return ret;
}
#endif  // LIBFFFTP_INCLUDE_MAIN_version


//--------------------------------------------------------------------------------------------------
#ifdef LIBFFFTP_INCLUDE_MAIN_Sound_Register
void Sound::Register() {}
#endif //LIBFFFTP_INCLUDE_MAIN_Sound_Register


//--------------------------------------------------------------------------------------------------
#ifdef LIBFFFTP_INCLUDE_MAIN_DeletedTaskbarProgress
// タスクバー進捗表示
// UI関連の機能はlibffftp使用者側に委ねるため、本機能は削除される
int LoadTaskbarList3() noexcept { return FFFTP_SUCCESS; }
void FreeTaskbarList3() {}
int IsTaskbarList3Loaded() noexcept { return YES; }
void UpdateTaskbarProgress() {}
#endif  // LIBFFFTP_INCLUDE_MAIN_DeletedTaskbarProgress


//--------------------------------------------------------------------------------------------------
#ifdef LIBFFFTP_IMPL

#include <QSettings> // TODO: 一時的

#include "libffftp_common.hpp"

namespace libffftp {

#ifndef LIBFFFTP_DECL
namespace{
constexpr const wchar_t* const kModuleName = L"libffftp";
constexpr const wchar_t* const kAppName = L"FFFTP";
}

LRESULT CallFtpWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  return FtpWndProc(hWnd, message, wParam, lParam);
}

long long doNotifyEvent(int eventid, long long param1, long long param2) {
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
    ret = FtpWndProc(GetMainHwnd(), WM_COMMAND, MAKEWPARAM(MENU_CONNECT_NUM, param1), param2);
    break;
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
  case EID_MENU_EXPORT_FILEZILLA_XML:
    (void)param1;
    (void)param2;
    ret = FtpWndProc(GetMainHwnd(), WM_COMMAND, MAKEWPARAM(MENU_EXPORT_FILEZILLA_XML, 0), 0);
    break;
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

// libffftpの中のInitApp関数
static int InitApp(int cmdShow) {
  int sts;
#ifdef LIBFFFTP_USE_WIN32API
  WSADATA WSAData;
#endif
  int useDefautPassword = 0; /* 警告文表示用 */
  int masterpass;
  // ポータブル版判定
  int ImportPortable;

  sts = FFFTP_FAIL;

#ifdef LIBFFFTP_USE_WIN32API
  if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0) { return FFFTP_FAIL; }
#endif

  // コマンドライン引数を先頭のEXEを除いて、std::vector<std::wstring_view>という型に格納する
  QStringList qargs{QCoreApplication::arguments()}; // 別スレッドからなのか、__wargvが機能しないのでQtを使う
  qargs.pop_front(); // 先頭のEXEを消去
  // うまくやればパイプライン演算子という手法を使って一行で実現できるらしい。以下はGemini2.0が提案してくれたコード。しかしコンパイルエラー
  //std::vector<std::wstring> args_ = qargs | std::views::transform([](const QString& s){ return s.toStdWString(); }) | std::ranges::to<std::vector>();
  //const std::vector<std::wstring_view> args = args_ | std::views::transform([](const std::wstring& s){ return std::wstring_view(s); }) | std::ranges::to<std::vector>();
  const std::vector<std::wstring>&& args_{[&qargs](){
    std::vector<std::wstring> t{};
    t.reserve(qargs.size());
    for (const auto& s : qargs) { t.push_back(s.toStdWString()); }
    return t;
  }()};
  const std::vector<std::wstring_view>&& args{[&args_](){
    std::vector<std::wstring_view> t{};
    t.reserve(args_.size());
    for (const auto& s : args_) { t.push_back(s); }
    return t;
  }()};
  for (const auto& s: args) {
    qDebug() << s;
  }

  // INIファイルモードかどうか
  // オプション＋引数省略: INIファイルの入出力先は個人フォルダ（ファイル名は"モジュール名(=ffftp)"+".ini"）
  // オプション＋引数指定: INIファイルの入出力先は指定したファイルパス
  // ポータブル版であっても、ユーザによって指定されたこの値は優先される
  if (auto it = std::find_if(begin(args), end(args), [](auto const& arg) { return ieq(arg, L"-n"sv) || ieq(arg, L"--ini"sv); }); it != end(args) && ++it != end(args)) {
    ForceIni = YES;
    RegType  = REGTYPE_INI;
    IniPath  = *it;
  } else {
    IniPath  = "////"; // これはINIファイルの入出力先は個人フォルダであることを意味するものとする
  }
  // IniPath == ""     : 設定の入出力先はレジストリ
  // IniPath == "////" : 設定の入出力先は個人フォルダ（AppData\Roaming）
  // IniPath それ以外  : 設定の入出力先はIniPath

  // ポータブル版かつレジストリに設定が存在した場合、設定をレジストリからインポートするかどうか
  // ここで言うインポートとは、読み込みはレジストリから、書き込みはINIファイルに、ということ
  ImportPortable = NO;
  if (isPortable()) {
    ForceIni = YES;
    RegType = REGTYPE_INI;
    IniPath = fs::path{moduleFileName()}.replace_extension(L".ini"sv);  // ポータブル版のINIファイルはEXEがあるフォルダにある
    if (IsRegAvailable() == YES && IsIniAvailable() == NO) {
      if (Dialog(nullptr, ffftp_dialogid::INI_FROM_REG_DLG, nullptr)) {
        ImportPortable = YES;
      }
    }
  } else {
    // レジストリから新しいバージョンがないか確認する
    if (ReadSettingsVersion() > VER_NUM) {
      if (IsRegAvailable() == YES && IsIniAvailable() == NO) {
        switch (Message(ffftp_messageid::SID_FOUND_NEW_VERSION_INI, 0)) { // インポートするかどうか
          case ffftp_procresponse::CANCEL:
            ReadOnlySettings = YES;
            break;
          case ffftp_procresponse::YES_:
            break;
          case ffftp_procresponse::NO_:
            ImportPortable = YES;
            break;
        }
      }
    }
  }

  // ポータブル版判定
  if (ImportPortable == YES) {
    ForceIni = NO;
    RegType = REGTYPE_REG;
  }

  // TODO: いったんここで個人フォルダのパスに書き換える
  if (IniPath == "////") {
    QSettings s{QSettings::IniFormat, QSettings::UserScope,"Sota", "FFFTP"};
    IniPath = s.fileName().toStdWString();
  }

  /* 2010.02.01 genta マスターパスワードを入力させる
    -z オプションがあるときは最初だけスキップ
    -z オプションがないときは，デフォルトパスワードをまず試す
    LoadRegistry()する
    パスワードが不一致なら再入力するか尋ねる．
    (破損していた場合はさせない)
  */
  if (auto it = std::find_if(begin(args), end(args), [](const auto& arg) { return ieq(arg, L"-z"sv) || ieq(arg, L"--mpasswd"sv); }); it != end(args) && ++it != end(args)) {
    SetMasterPassword(*it);
    useDefautPassword = 0;
  } else {
    /* パスワード指定無し */
    SetMasterPassword();
    /* この場では表示できないのでフラグだけ立てておく*/
    useDefautPassword = 2;
  }

  /* パスワードチェックのみ実施 */
  masterpass = 1;
  while (ValidateMasterPassword() == YES && GetMasterPasswordStatus() == PASSWORD_UNMATCH) {
    if (useDefautPassword != 2) {
      /* 再トライするか確認 */
      if (Message(ffftp_messageid::SID_MASTER_PASSWORD_INCORRECT, 0) != ffftp_procresponse::YES_) {
        useDefautPassword = 0; /* 不一致なので，もはやデフォルトかどうかは分からない */
        break;
      }
    }

    /* 再入力させる*/
    masterpass = EnterMasterPasswordAndSet(false, NULL);
    if (masterpass == 2) {
      useDefautPassword = 1;
    } else if (masterpass == 0) {
      SaveExit = NO;
      break;
    } else {
      useDefautPassword = 0;
    }
  }

  if (masterpass != 0) {
    // ホスト共通設定機能
    ResetDefaultHost();

    LoadRegistry();

    // ポータブル版判定
    if (ImportPortable == YES) {
      ForceIni = YES;
      RegType = REGTYPE_INI;
    }

    if (std::error_code ec; !empty(DefaultLocalPath))
      fs::current_path(DefaultLocalPath, ec);

    /* ウィンドウは作らない */

    if (MakeTransferThread() == FFFTP_SUCCESS) {
      Debug(L"DEBUG MESSAGE ON ! ##"sv);
      Notice(IDS_COPYRIGHT, version(), sizeof(void*) == 4 ? L"32bit"sv : L"64bit"sv);

      if (ForceIni) Notice(IDS_MSGJPN283, IniPath.native());

      Debug(L"Help={}", helpPath().native());

      StartupProc(args);
      sts = FFFTP_SUCCESS;

      /* セキュリティ警告文の表示 */
      if (useDefautPassword) {
        Notice(IDS_MSGJPN300);
      }

      /* パスワード不一致警告文の表示 */
      switch (GetMasterPasswordStatus()) {
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

  if (sts == FFFTP_FAIL) DeleteAllObject();

  return sts;
}

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
      if (ConnectOnStart == YES)
        doNotifyEvent(EID_MENU_CONNECT, 0, 0);
    } else if (empty(hostname) && !empty(unc)) {
      DirectConnectProc(std::move(unc), Kanji, Kana, FnameKanji, TrMode);
    } else if (!empty(hostname) && empty(unc)) {
      if (int const AutoConnect = SearchHostName(hostname); AutoConnect == -1)
        Notice(IDS_MSGJPN177, hostname);
      else {
        initializeDeferred = true;
        doNotifyEvent(EID_MENU_CONNECT_NUM, opt, AutoConnect);
      }
    } else {
      Notice(IDS_MSGJPN179);
    }
  }
  if (!initializeDeferred)
    SetEvent(initialized);
}

static void ExitProc() {
  CancelFlg = YES;

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

  return;
}
#endif  // LIBFFFTP_DECL


//--------------------------------------------------------------------------------------------------
LIBFFFTP_FUNCTION(bool initialize())
#ifndef LIBFFFTP_DECL
{
  hInstFtp = GetModuleHandleW(kModuleName);
  Sound::Register();
  MainThreadId = GetCurrentThreadId();

  // 戻り値S_FALSEはすでにOleInitialize関数呼び出し済みの意味
  // 他のプラットフォームがすでに呼び出してるだけかもしれないのでS_FALSEは失敗扱いにしない
  if (HRESULT hres = OleInitialize(nullptr); hres != S_OK && hres != S_FALSE) {
    Message(SID_FAIL_TO_INIT_OLE, 0);
    return false;
  }

  LoadUPnP();
  LoadTaskbarList3();
  LoadZoneID();

  if (!LoadSSL()) {
    Message(SID_ERR_SSL, 0);
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
  ExitProc();
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
  return doNotifyEvent(eventid, param1, param2);
}
#endif

}  // namespace libffftp

#endif  // LIBFFFTP_IMPL
