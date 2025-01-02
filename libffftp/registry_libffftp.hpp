#ifdef LIBFFFTP_INCLUDE_REGISTRY
#include <QSettings>

namespace {
constexpr const char* const kOrg{"Sota"};
constexpr const char* const kApp{"FFFTP"};
constexpr const char* const kRoa{"////"};
int version{};
QString prefix{};
// これは設定に応じて以下のパターンのどれかで初期化されます。
// 1. 設定の入出力先はレジストリ
// 2. 設定の入出力先は個人フォルダ（AppData\Roaming）
// 3. 設定の入出力先はEXEがあるフォルダ（ポータブル版用）
std::unique_ptr<QSettings> settings_{};
}  // namespace

void initSettings() {
  if (RegType == REGTYPE_REG) {
    // レジストリから
    settings_ = std::make_unique<QSettings>(kOrg, kApp);
    prefix = "";
  } else if (AskIniFilePath() == kRoa) {
    // 個人フォルダから
    settings_ = std::make_unique<QSettings>(QSettings::IniFormat, QSettings::UserScope, kOrg, kApp);
    prefix = kApp;
  } else {
    // それ以外はファイルパス指定
    settings_ = std::make_unique<QSettings>(AskIniFilePath().native(), QSettings::IniFormat);
    prefix = kApp;
  }
}
#endif  // LIBFFFTP_INCLUDE_REGISTRY


//--------------------------------------------------------------------------------------------------
#ifdef LIBFFFTP_INCLUDE_REGISTRY_Config
 public:
  using DWORD = unsigned long;
  std::unique_ptr<QSettings> settings_;
 private:
#endif  // LIBFFFTP_INCLUDE_REGISTRY_Config


//--------------------------------------------------------------------------------------------------
#ifdef LIBFFFTP_INCLUDE_REGISTRY_SetMasterPassword
// マスタパスワードの設定
void SetMasterPassword(std::wstring_view password) {
  memset(SecretKey, 0, sizeof SecretKey);
  strncpy_s(SecretKey, empty(password) ? DEFAULT_PASSWORD : u8(password).c_str(), MAX_PASSWORD_LEN);
  SecretKeyLength = (int)strlen(SecretKey);

  /* 未検証なので，初期状態はOKにする (強制再設定→保存にを可能にする)*/
  IsMasterPasswordError = PASSWORD_OK;
}
#endif  // LIBFFFTP_INCLUDE_REGISTRY_SetMasterPassword


//--------------------------------------------------------------------------------------------------
#ifdef LIBFFFTP_INCLUDE_REGISTRY_RegConfig
struct RegConfig : Config {
  RegConfig(const std::string& keyName, HKEY hkey) : Config{} {
    settings_ = std::make_unique<QSettings>(kOrg, kApp);
  }
  ~RegConfig() = default;
  std::unique_ptr<Config> OpenSubKey(std::string_view name) override { return {}; }
  std::unique_ptr<Config> CreateSubKey(std::string_view name) override { return {}; }
  bool ReadIntImpl(std::string_view name, int& value) const override {
    const bool ret{settings_->contains(name)};
    if (ret) { value = settings_->value(name); }
    return ret;
  }
  bool ReadStringImpl(std::string_view name, std::string& value) const override {
    const auto wName = u8(name);
    QString v{settings_->value(name)};
    if (DWORD type, count; RegQueryValueExW(hKey, wName.c_str(), nullptr, &type, nullptr, &count) == ERROR_SUCCESS) {
      if (type == REG_BINARY) {
        // TODO: EncryptSettings == YESの時、末尾に\0を含むが削除していない。
        value.resize(count);
        if (RegQueryValueExW(hKey, wName.c_str(), nullptr, nullptr,
                             data_as<BYTE>(value), &count) == ERROR_SUCCESS)
          return true;
      } else {
        // TODO: 末尾に\0が含まれているが削除していない。
        assert(EncryptSettings != YES &&
               (type == REG_SZ || type == REG_MULTI_SZ));
        if (std::wstring wvalue(count / sizeof(wchar_t), L'\0');
            RegQueryValueExW(hKey, wName.c_str(), nullptr, nullptr,
                             data_as<BYTE>(wvalue), &count) == ERROR_SUCCESS) {
          value = u8(wvalue);
          return true;
        }
      }
    }
    return false;
  }
  void WriteIntImpl(std::string_view name, int value) override {
    RegSetValueExW(hKey, u8(name).c_str(), 0, REG_DWORD, reinterpret_cast<CONST BYTE*>(&value), sizeof(int));
  }
  void WriteStringImpl(std::string_view name, std::string_view value,
                       DWORD type) override {
    if (EncryptSettings == YES || type == REG_BINARY)
      RegSetValueExW(hKey, u8(name).c_str(), 0, REG_BINARY, data_as<const BYTE>(value), type == REG_BINARY ? size_as<DWORD>(value) : size_as<DWORD>(value) + 1);
    else {
      const auto wvalue = u8(value);
      RegSetValueExW(hKey, u8(name).c_str(), 0, type, data_as<const BYTE>(wvalue), (size_as<DWORD>(wvalue) + 1) * sizeof(wchar_t));
    }
  }
  bool DeleteSubKey(std::string_view name) override {
    return SHDeleteKeyW(hKey, u8(name).c_str()) == ERROR_SUCCESS;
  }
  void DeleteValue(std::string_view name) override {
    RegDeleteValueW(hKey, u8(name).c_str());
  }
};
#endif  // LIBFFFTP_INCLUDE_REGISTRY_RegConfig


//--------------------------------------------------------------------------------------------------
#ifdef LIBFFFTP_INCLUDE_REGISTRY_OpenReg
// レジストリ/INIファイルをオープンする（読み込み）
//static std::unique_ptr<Config> OpenReg(int type) {
//  auto name = "FFFTP"s;
//  if (type == REGTYPE_REG) {
//    if (HKEY key; RegOpenKeyExW(HKEY_CURRENT_USER, LR"(Software\Sota\FFFTP)", 0, KEY_READ, &key) == ERROR_SUCCESS)
//      return std::make_unique<RegConfig>(name, key);
//  } else {
//    if (std::ifstream is{AskIniFilePath()}) {
//      auto root = std::make_unique<IniConfig>(name, false);
//      for (std::string line; getline(is, line);) {
//        if (empty(line) || line[0] == '#') continue;
//        if (line[0] == '[') {
//          if (const auto pos = line.find(']'); pos != std::string::npos)
//            line.resize(pos);
//          name = line.substr(1);
//        } else
//          (*root->map)[name].push_back(line);
//      }
//      return root;
//    }
//  }
//  return {};
//}

// レジストリ/INIファイルをオープンする（読み込み）
// type == REGTYPE_REG: レジストリパス"HKEY_CURRENT_USER\Software\Sota\FFFTP"が存在しない場合はエラー（空std::unique_ptr）が返る
// type == REGTYPE_INI: 変数IniPathが示すファイルが開けなかった場合はエラー（空std::unique_ptr）が返る
static std::unique_ptr<Config> OpenReg(int type) {
  std::unique_ptr<Config> ret{};
  // トップレベルフォルダ"FFFTP"の有無は確認できないので、キー"FFFTP\Version"の有無で判断する
  switch (type) {
  case REGTYPE_REG:
    QSettings::setDefaultFormat(QSettings::NativeFormat);
    if (settings.contains("Version")) {
    }
    break;
  case REGTYPE_INI:
    QSettings::setDefaultFormat(QSettings::IniFormat);
    if (settings.contains("Version")) {
    }
    break;
  }
  return ret;
}
#endif  // LIBFFFTP_INCLUDE_REGISTRY_OpenReg


//--------------------------------------------------------------------------------------------------
#ifdef LIBFFFTP_INCLUDE_REGISTRY_IsAvailable
// レジストリが有効性の確認
int IsRegAvailable() {
  QSettings s{kOrg, kApp};
  // トップレベルフォルダ"FFFTP"の有無は確認できないので、キー"FFFTP\Version"の有無で判断する
  return s.contains("Version") ? YES : NO;
}

// INIファイルの有効性の確認
int IsIniAvailable() {
  QSettings s{QString{AskIniFilePath().native()}, QSettings::IniFormat};
  // キー"FFFTP\Version"が読めたら有効とする
  return s.contains(kApp + "/Version") ? YES : NO;
}

// バージョン確認
int ReadSettingsVersion() {
  if (version > 0) { return version; } // 既に読み込む済みなのでそれを返す
  std::unique_ptr<QSettings> s{};
  QString prefix{};
  if (AskIniFilePath().empty()) {
    s = std::make_unique<QSettings>(kOrg, kApp); // レジストリから
    prefix = "";
  } else if (AskIniFilePath() == kRoa) {
    s = std::make_unique<QSettings>(QSettings::IniFormat, QSettings::UserScope, kOrg, kApp); // 個人フォルダから
    prefix = kApp;
  } else {
    QSettings s{QString{AskIniFilePath().native()}, QSettings::IniFormat}; // それ以外はファイルパス指定
    prefix = kApp;
  }
  s->beginGroup(prefix);
  version = s->value("Version");
  s->endGroup()
  return version;
}
#endif  // LIBFFFTP_INCLUDE_REGISTRY_IsAvailable


//--------------------------------------------------------------------------------------------------
#ifdef LIBFFFTP_INCLUDE_REGISTRY_SaveSettingsToFileZillaXml
// Qt XMLを使用してFileZilla用の設定形式(XML)にエクスポートを行う
#include <QFile>
#include <QTimeZone>
#include <QXmlStreamWriter>
void SaveSettingsToFileZillaXml() {
  static boost::wregex unix{ LR"([^/]+)" }, dos{ LR"([^/\\]+)" };
  if (auto const path = SelectFile(false, nullptr, IDS_SAVE_SETTING, L"FileZilla.xml", nullptr, { FileType::Xml,FileType::All }); !std::empty(path)) {
    if (QFile file{path}; file.open(QFile::WriteOnly | QFile::Text)) {
      int tz_bias = -(QTimeZone::systemTimeZone().offsetFromUtc(QDateTime()) / 60);
      QXmlStreamWriter writer{&file};
      writer.setAutoFormatting(true);
      writer.writeStartDocument();
      writer.writeEndDocument();
      writer.writeStartElement(L"FileZilla3");
      writer.writeStartElement(L"Servers");
      int level = 0;
      HOSTDATA host;
      for (int i = 0; CopyHostFromList(i, &host) == FFFTP_SUCCESS; i++) {
        while ((host.Level & SET_LEVEL_MASK) < level--)
          writer.writeEndElement();
        if (host.Level & SET_LEVEL_GROUP) {
          writer.writeStartElement(L"Folder");
          writer.writeAttribute(L"expanded", L"1");
          writer.writeCharacters(host.HostName.c_str());
          level++;
        } else {
          writer.writeStartElement(L"Server");
          writer.writeTextElement(L"Host", host.HostAdrs.c_str());
          writer.writeTextElement(L"Port", std::to_wstring(host.Port).c_str());
          writer.writeTextElement(L"Protocol", host.UseNoEncryption == YES ? L"0" : host.UseFTPES == YES ? L"4" : host.UseFTPIS == YES ? L"3" : L"0");
          writer.writeTextElement(L"Type", L"0");
          writer.writeTextElement(L"User", host.UserName.c_str());
          writer.writeTextElement(L"Pass", host.PassWord.c_str());
          writer.writeTextElement(L"Account", host.Account.c_str());
          writer.writeTextElement(L"Logontype", host.Anonymous == YES || empty(host.UserName) ? L"0" : L"1");
          writer.writeTextElement(L"TimezoneOffset", std::to_wstring(tz_bias + host.TimeZone * 60).c_str());
          writer.writeTextElement(L"PasvMode", host.Pasv == YES ? L"MODE_PASSIVE" : L"MODE_ACTIVE");
          writer.writeTextElement(L"MaximumMultipleConnections", nullptr, std::to_wstring(host.MaxThreadCount).c_str());
          switch (host.NameKanjiCode) {
          case KANJI_SJIS:
            writer.writeTextElement(L"EncodingType",L"Custom");
            writer.writeTextElement(L"CustomEncoding", L"Shift_JIS");
            break;
          case KANJI_EUC:
            writer.writeTextElement(L"EncodingType", L"Custom");
            writer.writeTextElement(L"CustomEncoding", L"EUC-JP");
            break;
          case KANJI_UTF8N:
            writer.writeTextElement(L"EncodingType", L"UTF-8");
            break;
          case KANJI_JIS:
          case KANJI_SMB_HEX:
          case KANJI_SMB_CAP:
          case KANJI_UTF8HFSX:
          default:
            writer.writeTextElement(L"EncodingType", L"Auto");
            break;
          }
          writer.writeTextElement(L"BypassProxy", host.FireWall == YES ? L"0" : L"1");
          writer.writeTextElement(L"Name", host.HostName.c_str());
          writer.writeTextElement(L"LocalDir", host.LocalInitDir.c_str());
          auto remoteDir = host.RemoteInitDir;
          for (auto& [ch, prefix, re] : std::initializer_list<std::tuple<wchar_t, std::wstring_view, boost::wregex>>{ { L'/', L"1 0"sv, unix }, { L'\\', L"8 0"sv, dos } })
            if (remoteDir.find(ch) != std::wstring::npos) {
              std::wstring encoded{ prefix };
              for (boost::wcregex_iterator it{ data(remoteDir), data(remoteDir) + size(remoteDir), re }, end; it != end; ++it) {
                encoded += L' ';
                encoded += std::to_wstring(it->length(0));
                encoded += L' ';
                encoded += { (*it)[0].first, (size_t)it->length(0) };
              }
              remoteDir = encoded;
              break;
            }
          writer.writeTextElement(L"RemoteDir", remoteDir.c_str());
          writer.writeTextElement(L"SyncBrowsing", host.SyncMove == YES ? L"1" : L"0");
          writer.writeEndElement(); // </Server>
        }
      }
      writer.writeEndDocument(); // Closes any open elements or attributes, then closes the current document.
      return;
    } else {
      Message(SID_FAIL_TO_EXPORT, 0);
    }
  }
}
#endif  // LIBFFFTP_INCLUDE_REGISTRY_SaveSettingsToFileZillaXml
