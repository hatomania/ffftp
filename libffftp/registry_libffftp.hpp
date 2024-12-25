#ifndef LIBFFFTP_REALLY_NOTUSE_QT
// Qt XMLを使用してFileZilla用の設定形式(XML)にエクスポートを行う
#include <QFile>
#include <QTimeZone>
#include <QXmlStreamWriter>
void SaveSettingsToFileZillaXml() {
  static boost::wregex unix{ LR"([^/]+)" }, dos{ LR"([^/\\]+)" };
  if (auto const path = SelectFile(false, GetMainHwnd(), IDS_SAVE_SETTING, L"FileZilla.xml", L"xml", { FileType::Xml,FileType::All }); !std::empty(path)) {
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
          writer.writeEndElement();	// </Server>
        }
      }
      writer.writeEndDocument();	// Closes any open elements or attributes, then closes the current document.
      return;
    } else {
      Message(IDS_FAIL_TO_EXPORT, MB_OK | MB_ICONERROR);
    }
  }
}
#endif
