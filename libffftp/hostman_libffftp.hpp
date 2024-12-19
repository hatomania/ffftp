#if defined(LIBFFFTP_OTHER)


#elif defined(LIBFFFTP_DECL) || defined(LIBFFFTP_IMPL)

#include "libffftp_common.hpp"
#include "ffftp_common.h"
#include "ffftp_hostdata.h"

namespace libffftp {

#ifdef LIBFFFTP_IMPL

namespace {

HOSTLISTDATA* castContext2Host(ffftp_hostcontext_t hc) {
  return const_cast<HOSTLISTDATA*>(static_cast<const HOSTLISTDATA*>(hc));
}

int hostIndex(ffftp_hostcontext_t hc) {
  auto data = castContext2Host(hc);
  int _n = 0;
  for (auto p = HostListTop.get(); p != data; p = p->GetNext().get()) ++_n;
  return _n;
}

inline constexpr int timezone2Index(int timezone) { return timezone + 12; }
inline constexpr int index2Timezone(int timezone) { return timezone - 12; }

inline constexpr int convertKanjiCode2libffftp(int kanjicode) {
  return
    kanjicode == KANJI_NOCNV   ? ffftp_kanjicodes::KC_NOP     :
    kanjicode == KANJI_SJIS    ? ffftp_kanjicodes::KC_SJIS    :
    kanjicode == KANJI_JIS     ? ffftp_kanjicodes::KC_JIS     :
    kanjicode == KANJI_EUC     ? ffftp_kanjicodes::KC_EUC     :
    kanjicode == KANJI_UTF8N   ? ffftp_kanjicodes::KC_UTF8N   :
    kanjicode == KANJI_UTF8BOM ? ffftp_kanjicodes::KC_UTF8BOM : -1;
}

inline constexpr int convertNameKanjiCode2libffftp(int kanjicode) {
  return
    kanjicode == KANJI_AUTO     ? ffftp_kanjicodes::KC_AUTO     :
    kanjicode == KANJI_SJIS     ? ffftp_kanjicodes::KC_SJIS     :
    kanjicode == KANJI_JIS      ? ffftp_kanjicodes::KC_JIS      :
    kanjicode == KANJI_EUC      ? ffftp_kanjicodes::KC_EUC      :
    kanjicode == KANJI_SMB_HEX  ? ffftp_kanjicodes::KC_SMH      :
    kanjicode == KANJI_SMB_CAP  ? ffftp_kanjicodes::KC_SMC      :
    kanjicode == KANJI_UTF8N    ? ffftp_kanjicodes::KC_UTF8N    :
    kanjicode == KANJI_UTF8HFSX ? ffftp_kanjicodes::KC_UTF8HFSX : -1;
}

inline constexpr int convertKanjiCode2ffftp(int kanjicode) {
  return
    kanjicode == ffftp_kanjicodes::KC_NOP     ? KANJI_NOCNV   :
    kanjicode == ffftp_kanjicodes::KC_SJIS    ? KANJI_SJIS    :
    kanjicode == ffftp_kanjicodes::KC_JIS     ? KANJI_JIS     :
    kanjicode == ffftp_kanjicodes::KC_EUC     ? KANJI_EUC     :
    kanjicode == ffftp_kanjicodes::KC_UTF8N   ? KANJI_UTF8N   :
    kanjicode == ffftp_kanjicodes::KC_UTF8BOM ? KANJI_UTF8BOM : -1;
}

inline constexpr int convertNameKanjiCode2ffftp(int kanjicode) {
  return
    kanjicode == ffftp_kanjicodes::KC_AUTO     ? KANJI_AUTO     :
    kanjicode == ffftp_kanjicodes::KC_SJIS     ? KANJI_SJIS     :
    kanjicode == ffftp_kanjicodes::KC_JIS      ? KANJI_JIS      :
    kanjicode == ffftp_kanjicodes::KC_EUC      ? KANJI_EUC      :
    kanjicode == ffftp_kanjicodes::KC_SMH      ? KANJI_SMB_HEX  :
    kanjicode == ffftp_kanjicodes::KC_SMC      ? KANJI_SMB_CAP  :
    kanjicode == ffftp_kanjicodes::KC_UTF8N    ? KANJI_UTF8N    :
    kanjicode == ffftp_kanjicodes::KC_UTF8HFSX ? KANJI_UTF8HFSX : -1;
}

void convertHostData(ffftp_hostdata& dst, const HOSTDATA& src) {
  // [基本]タブ
  dst.general = {
    .host_name = src.HostName.c_str(),
    .host_adrs = src.HostAdrs.c_str(),
    .username = src.UserName.c_str(),
    .password = src.PassWord.c_str(),
    .anonymous_password = UserMailAdrs.c_str(),
    .anonymous = src.Anonymous == YES,
    .initdir_local = src.LocalInitDir.c_str(),
    .initdir_remote = src.RemoteInitDir.c_str(),
    .initdir_remote_now = AskRemoteCurDir().c_str(),
    .enabled_curdir = AskConnecting() == YES,
    .last_dir = src.LastDir == YES,
  };
  // [拡張]タブ
  dst.advanced = {
    .firewall = src.FireWall == YES,
    .pasv = src.Pasv == YES,
    .syncmove = src.SyncMove == YES,
    .port = src.Port,
    .account = src.Account.c_str(),
    .timezone = timezone2Index(src.TimeZone),
    .security = src.Security,
    .initcmd = src.InitCmd.c_str(),
  };
  // [文字コード]タブ
  dst.kanjicode = {
    .kanjicode = convertKanjiCode2libffftp(src.KanjiCode),
    .kanacnv = src.KanaCnv == YES,
    .kanjicode_name = convertNameKanjiCode2libffftp(src.NameKanjiCode),
    .kanacnv_name = src.NameKanaCnv == YES,
  };
  // [ダイアルアップ]タブ
  dst.dialup.dialup = src.Dialup == YES;
  dst.dialup.dial_entry = src.DialEntry.c_str();
  dst.dialup.dialup_always = src.DialupAlways == YES;
  dst.dialup.dialup_notify = src.DialupNotify == YES;
  delete[] dst.dialup.dial_entries;
  dst.dialup.dial_entries = nullptr;
  dst.dialup.dial_entries_cnt = 0;
  const std::vector<std::wstring>& dialup_entries = dialupEntries();
  if (!dialup_entries.empty()) {
    dst.dialup.dial_entries = new const wchar_t* [dialup_entries.size()];
    for (int i = 0; const auto & entry : dialup_entries) {
      dst.dialup.dial_entries[i++] = entry.c_str();
    }
    dst.dialup.dial_entries_cnt = dialup_entries.size();
  }
  // [高度]タブ
  dst.special = {
    .list_cmd_only = src.ListCmdOnly == YES,
    .use_mlsd = src.UseMLSD == YES,
    .use_nlst_r = src.UseNLST_R == YES,
    .no_fullpath = src.NoFullPath == YES,
    .chmod_cmd = src.ChmodCmd.c_str(),
    .host_type = src.HostType,
    .ls_name = src.LsName.c_str(),
  };
  // [暗号化]タブ
  dst.encryption = {
    .use_no_encryption = src.UseNoEncryption == YES,
    .use_ftp_es = src.UseFTPES == YES,
    .use_ftp_is = src.UseFTPIS == YES,
  };
  // [特殊機能]タブ
  dst.feature = {
    .max_thread_cnt = src.MaxThreadCount,
    .reuse_cmdsocket = src.ReuseCmdSkt == YES,
    .no_pasv_adrs = src.NoPasvAdrs == YES,
    .noop_interval = src.NoopInterval,
    .error_mode =
      src.TransferErrorNotify == YES ? 0 :
      src.TransferErrorMode == EXIST_OVW ? 1 :
      src.TransferErrorMode == EXIST_RESUME ? 2 :
      src.TransferErrorMode == EXIST_IGNORE ? 3 : -1,
    .reconnect = src.TransferErrorReconnect == YES,
  };
}

void convertHostData(HOSTDATA& dst, const ffftp_hostdata& src) {
  // [基本]タブ
  dst.HostName = src.general.host_name;
  dst.HostAdrs = src.general.host_adrs;
  dst.UserName = src.general.username;
  dst.PassWord = src.general.password;
  dst.Anonymous = src.general.anonymous ? YES : NO;
  dst.LocalInitDir = src.general.initdir_local;
  dst.RemoteInitDir = src.general.initdir_remote;
  dst.LastDir = src.general.last_dir;
  // [拡張]タブ
  dst.FireWall = src.advanced.firewall ? YES : NO;
  dst.Pasv = src.advanced.pasv ? YES : NO;
  dst.SyncMove = src.advanced.syncmove ? YES : NO;
  dst.Port = src.advanced.port;
  dst.Account = src.advanced.account;
  dst.TimeZone = index2Timezone(src.advanced.timezone);
  dst.Security = src.advanced.security;
  dst.InitCmd = src.advanced.initcmd;
  // [文字コード]タブ
  dst.KanjiCode = convertKanjiCode2ffftp(src.kanjicode.kanjicode);
  dst.KanaCnv = src.kanjicode.kanacnv ? YES : NO;
  dst.NameKanjiCode = convertNameKanjiCode2ffftp(src.kanjicode.kanjicode_name);
  dst.NameKanaCnv = src.kanjicode.kanacnv_name ? YES : NO;
  // [ダイアルアップ]タブ
  dst.Dialup = src.dialup.dialup ? YES : NO;
  dst.DialEntry = src.dialup.dial_entry;
  dst.DialupAlways = src.dialup.dialup_always ? YES : NO;
  dst.DialupNotify = src.dialup.dialup_notify ? YES : NO;
  // [高度]タブ
  dst.ListCmdOnly = src.special.list_cmd_only ? YES : NO;
  dst.UseMLSD = src.special.use_mlsd ? YES : NO;
  dst.UseNLST_R = src.special.use_nlst_r ? YES : NO;
  dst.NoFullPath = src.special.no_fullpath ? YES : NO;
  dst.ChmodCmd = src.special.chmod_cmd;
  dst.HostType = src.special.host_type;
  dst.LsName = src.special.ls_name;
  // [暗号化]タブ
  dst.UseNoEncryption = src.encryption.use_no_encryption ? YES : NO;
  dst.UseFTPES = src.encryption.use_ftp_es ? YES : NO;
  dst.UseFTPIS = src.encryption.use_ftp_is ? YES : NO;
  // [特殊機能]タブ
  dst.MaxThreadCount = src.feature.max_thread_cnt;
  dst.ReuseCmdSkt = src.feature.reuse_cmdsocket ? YES : NO;
  dst.NoPasvAdrs = src.feature.no_pasv_adrs ? YES : NO;
  dst.NoopInterval = src.feature.noop_interval;
  dst.TransferErrorMode = -1;
  switch (src.feature.error_mode)
  {
  case 0:
    dst.TransferErrorMode = EXIST_OVW;
    dst.TransferErrorNotify = YES;
    break;
  case 1:
    dst.TransferErrorMode = EXIST_OVW;
    dst.TransferErrorNotify = NO;
    break;
  case 2:
    dst.TransferErrorMode = EXIST_RESUME;
    dst.TransferErrorNotify = NO;
    break;
  case 3:
    dst.TransferErrorMode = EXIST_IGNORE;
    dst.TransferErrorNotify = NO;
    break;
  }
  dst.TransferErrorReconnect = src.feature.reconnect;
}

inline ffftp_hostdata convertHostData(const HOSTDATA& src) {
  ffftp_hostdata ret;
  convertHostData(ret, src);
  return ret;
}

} // namespace

#endif // LIBFFFTP_IMPL

LIBFFFTP_FUNCTION(ffftp_hostcontext_t hostContextFirst())
#ifdef LIBFFFTP_IMPL
{
  return HostListTop.get();
}
#endif

LIBFFFTP_FUNCTION(ffftp_hostcontext_t hostContextNext(ffftp_hostcontext_t hc))
#ifdef LIBFFFTP_IMPL
{
  return castContext2Host(hc)->GetNext().get();
}
#endif

LIBFFFTP_FUNCTION(ffftp_hostcontext_t hostContextNew(ffftp_hostcontext_t hc, const ffftp_hostdata* hdata))
#ifdef LIBFFFTP_IMPL
{
  int pos = -1;
  int index = -1;
  if (!hc) {
    // 先頭に追加したい
    TmpHost.Level = 0;
    CurrentHost = pos = 0;
  } else if (Hosts == 0) {
    // ホストが一つも登録されていなかったら
    TmpHost.Level = 0;
    CurrentHost = Hosts;
  } else {
    index = hostIndex(hc);
    TmpHost.Level = GetLevel(index);
    CurrentHost = pos = index + 1;
  }
  convertHostData(TmpHost, *hdata);
  AddHostToList(&TmpHost, pos, SET_LEVEL_SAME);
  return GetNode(CurrentHost).get();
}
#endif

LIBFFFTP_FUNCTION(ffftp_hostcontext_t hostContextNewGroup(ffftp_hostcontext_t hc, const wchar_t* group_name))
#ifdef LIBFFFTP_IMPL
{
  int pos = -1;
  int index = -1;
  if (!hc) {
    // 先頭に追加したい
    TmpHost.Level = 0;
    CurrentHost = pos = 0;
  }
  else if (Hosts == 0) {
    // ホストが一つも登録されていなかったら
    TmpHost.Level = 0;
    CurrentHost = Hosts;
  }
  else {
    index = hostIndex(hc);
    TmpHost.Level = GetLevel(index);
    CurrentHost = pos = index + 1;
  }
  TmpHost.Level |= SET_LEVEL_GROUP;
  TmpHost.HostName = group_name;
  AddHostToList(&TmpHost, pos, SET_LEVEL_SAME);
  return GetNode(CurrentHost).get();
}
#endif

LIBFFFTP_FUNCTION(ffftp_hostcontext_t hostContextModify(ffftp_hostcontext_t hc, const ffftp_hostdata* hdata))
#ifdef LIBFFFTP_IMPL
{
  CurrentHost = hostIndex(hc);
  CopyHostFromList(CurrentHost, &TmpHost);
  convertHostData(TmpHost, *hdata);
  UpdateHostToList(CurrentHost, &TmpHost);
  return GetNode(CurrentHost).get();
}
#endif

LIBFFFTP_FUNCTION(ffftp_hostcontext_t hostContextModifyGroup(ffftp_hostcontext_t hc, const wchar_t* group_name))
#ifdef LIBFFFTP_IMPL
{
  CurrentHost = hostIndex(hc);
  CopyHostFromList(CurrentHost, &TmpHost);
  TmpHost.HostName = group_name;
  UpdateHostToList(CurrentHost, &TmpHost);
  return GetNode(CurrentHost).get();
}
#endif

LIBFFFTP_FUNCTION(ffftp_hostcontext_t hostContextCopy(ffftp_hostcontext_t hc))
#ifdef LIBFFFTP_IMPL
{
  CurrentHost = hostIndex(hc);
  CopyHostFromList(CurrentHost, &TmpHost);
  TmpHost.BookMark = {};
  CurrentHost++;
  AddHostToList(&TmpHost, CurrentHost, SET_LEVEL_SAME);
  return GetNode(CurrentHost).get();
}
#endif

LIBFFFTP_FUNCTION(ffftp_hostcontext_t hostContextDelete(ffftp_hostcontext_t hc))
#ifdef LIBFFFTP_IMPL
{
  CurrentHost = hostIndex(hc);
  DelHostFromList(CurrentHost);
  if (CurrentHost >= Hosts)
    CurrentHost = std::max(0, Hosts - 1);
  return GetNode(CurrentHost).get();
}
#endif

LIBFFFTP_FUNCTION(void hostContextUp(ffftp_hostcontext_t hc))
#ifdef LIBFFFTP_IMPL
{
  CurrentHost = hostIndex(hc);

  if (CurrentHost > 0) {
    auto Data1 = GetNode(CurrentHost);
    const int Level1 = Data1->GetLevel();
    auto Data2 = GetNode(CurrentHost - 1);
    const int Level2 = Data2->GetLevel();
    if (Level1 == Level2 && (Data2->Level & SET_LEVEL_GROUP)) {
      // Data2のchildへ
      if (Data1->Next != NULL) Data1->Next->Prev = Data1->Prev;
      if (Data1->Prev != NULL) Data1->Prev->Next = Data1->Next;
      if (Data1->Parent != NULL && Data1->Parent->Child == Data1)
        Data1->Parent->Child = Data1->Next;
      if (Data1->Parent == NULL && HostListTop == Data1)
        HostListTop = Data1->Next;

      Data1->Next = Data2->Child;
      Data1->Prev = NULL;
      Data1->Parent = Data2;
      Data2->Child = Data1;
    } else if (Level1 < Level2) {
      // Data1のPrevのChildのNextの末尾へ
      Data2 = Data1->Prev->Child;
      while (Data2->Next != NULL) Data2 = Data2->Next;

      if (Data1->Next != NULL) Data1->Next->Prev = Data1->Prev;
      if (Data1->Prev != NULL) Data1->Prev->Next = Data1->Next;
      if (Data1->Parent != NULL && Data1->Parent->Child == Data1)
        Data1->Parent->Child = Data1->Next;
      if (Data1->Parent == NULL && HostListTop == Data1)
        HostListTop = Data1->Next;

      Data2->Next = Data1;
      Data1->Prev = Data2;
      Data1->Next = NULL;
      Data1->Parent = Data2->Parent;
    } else {
      // Data2のprevへ
      if (Data1->Next != NULL) Data1->Next->Prev = Data1->Prev;
      if (Data1->Prev != NULL) Data1->Prev->Next = Data1->Next;
      if (Data1->Parent != NULL && Data1->Parent->Child == Data1)
        Data1->Parent->Child = Data1->Next;
      if (Data1->Parent == NULL && HostListTop == Data1)
        HostListTop = Data1->Next;

      if (Data2->Prev != NULL) Data2->Prev->Next = Data1;
      Data1->Prev = Data2->Prev;
      Data2->Prev = Data1;
      Data1->Next = Data2;
      Data1->Parent = Data2->Parent;

      if (Data1->Parent != NULL && Data1->Parent->Child == Data2)
        Data1->Parent->Child = Data1;
      if (Data1->Parent == NULL && HostListTop == Data2) HostListTop = Data1;
    }

    CurrentHost = GetNum(Data1);
  }
}
#endif

LIBFFFTP_FUNCTION(void hostContextDown(ffftp_hostcontext_t hc))
#ifdef LIBFFFTP_IMPL
{
  CurrentHost = hostIndex(hc);

  auto Data1 = GetNode(CurrentHost);
  const int Level1 = Data1->GetLevel();
  std::shared_ptr<HOSTLISTDATA> Data2;
  int Level2 = SET_LEVEL_SAME;
  if (CurrentHost < Hosts - 1) {
    Data2 = GetNode(CurrentHost + 1);
    Level2 = Data2->GetLevel();

    if (Level1 < Level2) {
      if (Data1->Next != NULL) {
        // Data2 = Data1のNext
        Data2 = Data1->Next;
        Level2 = Data2->GetLevel();
      } else if (Data1->Parent != NULL) {
        Data2 = NULL;
        Level2 = SET_LEVEL_SAME;
      }
    }
  }

  __assume(Data1);
  if (Data2 == NULL && Level1 > 0 || Level1 > Level2) {
    __assume(Data1->Parent);
    // Data1のParentのNextへ
    Data2 = Data1->Parent;

    if (Data1->Next != NULL) Data1->Next->Prev = Data1->Prev;
    if (Data1->Prev != NULL) Data1->Prev->Next = Data1->Next;
    if (Data1->Parent != NULL && Data1->Parent->Child == Data1)
      Data1->Parent->Child = Data1->Next;
    if (Data1->Parent == NULL && HostListTop == Data1)
      HostListTop = Data1->Next;

    if (Data2->Next != NULL) Data2->Next->Prev = Data1;
    Data1->Next = Data2->Next;
    Data2->Next = Data1;
    Data1->Prev = Data2;
    Data1->Parent = Data2->Parent;

    if (Data1->Parent != NULL && Data1->Parent->Child == Data1)
      Data1->Parent->Child = Data2;
    if (Data1->Parent == NULL && HostListTop == Data1) HostListTop = Data2;
  } else if (Level1 == Level2) {
    __assume(Data2);
    if (Data2->Level & SET_LEVEL_GROUP) {
      // Data2のChildへ
      if (Data1->Next != NULL) Data1->Next->Prev = Data1->Prev;
      if (Data1->Prev != NULL) Data1->Prev->Next = Data1->Next;
      if (Data1->Parent != NULL && Data1->Parent->Child == Data1)
        Data1->Parent->Child = Data1->Next;
      if (Data1->Parent == NULL && HostListTop == Data1)
        HostListTop = Data1->Next;

      if (Data2->Child != NULL) Data2->Child->Prev = Data1;
      Data1->Next = Data2->Child;
      Data1->Prev = NULL;
      Data1->Parent = Data2;
      Data2->Child = Data1;
    } else {
      // Data2のNextへ
      if (Data1->Next != NULL) Data1->Next->Prev = Data1->Prev;
      if (Data1->Prev != NULL) Data1->Prev->Next = Data1->Next;
      if (Data1->Parent != NULL && Data1->Parent->Child == Data1)
        Data1->Parent->Child = Data1->Next;
      if (Data1->Parent == NULL && HostListTop == Data1)
        HostListTop = Data1->Next;

      if (Data2->Next != NULL) Data2->Next->Prev = Data1;
      Data1->Next = Data2->Next;
      Data2->Next = Data1;
      Data1->Prev = Data2;
      Data1->Parent = Data2->Parent;

      if (Data1->Parent != NULL && Data1->Parent->Child == Data1)
        Data1->Parent->Child = Data2;
      if (Data1->Parent == NULL && HostListTop == Data1) HostListTop = Data2;
    }
  }

  CurrentHost = GetNum(Data1);
}
#endif

LIBFFFTP_FUNCTION(void hostContextSetDataDefault(const ffftp_hostdata* hdata))
#ifdef LIBFFFTP_IMPL
{
  CopyDefaultHost(&TmpHost);
  convertHostData(TmpHost, *hdata);
  SetDefaultHost(&TmpHost);
}
#endif

LIBFFFTP_FUNCTION(void hostContextDataDefault(ffftp_hostdata* hdata))
#ifdef LIBFFFTP_IMPL
{
  convertHostData(*hdata, DefaultHost);
}
#endif

LIBFFFTP_FUNCTION(void hostContextData(ffftp_hostcontext_t hc, ffftp_hostdata* hdata))
#ifdef LIBFFFTP_IMPL
{
  static HOSTDATA hd; // 文字列へのポインタはライブラリ使用側に返るのでstaticとする
  CopyHostFromList(hostIndex(hc), &hd);
  convertHostData(*hdata, hd);
}
#endif

LIBFFFTP_FUNCTION(const wchar_t* hostContextName(ffftp_hostcontext_t hc))
#ifdef LIBFFFTP_IMPL
{
  static std::wstring host_name{};
  host_name = castContext2Host(hc)->HostName.c_str();
  return host_name.c_str();
}
#endif

LIBFFFTP_FUNCTION(int hostContextLevel(ffftp_hostcontext_t hc))
#ifdef LIBFFFTP_IMPL
{
  return castContext2Host(hc)->GetLevel();
}
#endif

LIBFFFTP_FUNCTION(bool hostContextIsGroup(ffftp_hostcontext_t hc))
#ifdef LIBFFFTP_IMPL
{
  return castContext2Host(hc)->GetLevel() & SET_LEVEL_GROUP;
}
#endif

LIBFFFTP_FUNCTION(bool connect(ffftp_hostcontext_t hc))
#ifdef LIBFFFTP_IMPL
{
  ConnectProc(DLG_TYPE_CON, hostIndex(hc));
  return AskConnecting() == YES;
}
#endif

LIBFFFTP_FUNCTION(void showHelp(int id))
#ifdef LIBFFFTP_IMPL
{
  ShowHelp(id);
}
#endif

}  // namespace libffftp

#endif
