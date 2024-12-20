#ifdef LIBFFFTP_OTHER


#else

#include "ffftp_option.h"
#include "libffftp_common.hpp"

namespace libffftp {

// オプションを設定する
LIBFFFTP_FUNCTION(void setOption(const ffftp_option& opt))
#ifndef LIBFFFTP_DECL
{
  // wchar_tの配列からvector<wstring>に変換する関数オブジェクト
  auto wchar2VectorWstr = [](std::vector<std::wstring>& out_str, const wchar_t** in_str, size_t in_cnt) {
    out_str.clear();
    out_str.reserve(in_cnt);
    for (int i = 0; i < in_cnt; ++i) {
      out_str.push_back(in_str[i]);
    }
  };
  // [ユーザー]タブ
  UserMailAdrs = opt.user.user_mail_adrs;
  // [転送1]タブ
  SetTransferTypeImm(
    opt.transfer1.trans_mode == modes::ASCII  ? TYPE_A :
    opt.transfer1.trans_mode == modes::BINARY ? TYPE_I :
    opt.transfer1.trans_mode == modes::AUTO   ? TYPE_X : -1);
  RmEOF = opt.transfer1.rm_eof ? YES : NO;
  SaveTimeStamp = opt.transfer1.save_timestamp ? YES : NO;
  VaxSemicolon = opt.transfer1.vax_semicolon ? YES : NO;
  MakeAllDir = opt.transfer1.make_all_dir ? YES : NO;
  AbortOnListError = opt.transfer1.abort_on_list_error ? YES : NO;
  wchar2VectorWstr(AsciiExt, opt.transfer1.ascii_ext, opt.transfer1.ascii_ext_cnt);
  // [転送2]タブ
  FnameCnv =
    opt.transfer2.fname_cnv == modes::LOWER ? FNAME_LOWER :
    opt.transfer2.fname_cnv == modes::UPPER ? FNAME_UPPER :
    opt.transfer2.fname_cnv == modes::NOCNV ? FNAME_NOCNV : -1;
  TimeOut = opt.transfer2.timeout;
  DefaultLocalPath = opt.transfer2.default_local_path;
  // [転送3]タブ
  DefAttrList.clear();
  DefAttrList.reserve(opt.transfer3.attrlist_cnt * 2);
  for (int i = 0; i < opt.transfer3.attrlist_cnt; ++i) {
    DefAttrList.push_back(opt.transfer3.attrlist_fname[i]);
    DefAttrList.push_back(std::to_wstring(opt.transfer3.attrlist_attr[i]));
  }
  FolderAttr = opt.transfer3.use_folder_attr ? YES : NO;
  FolderAttrNum = opt.transfer3.folder_attr;
  // [転送4]タブ
  SetLocalKanjiCodeImm(
    opt.transfer4.local_kanjicode == modes::SJIS    ? KANJI_SJIS    :
    opt.transfer4.local_kanjicode == modes::JIS     ? KANJI_JIS     :
    opt.transfer4.local_kanjicode == modes::EUC     ? KANJI_EUC     :
    opt.transfer4.local_kanjicode == modes::UTF8N   ? KANJI_UTF8N   :
    opt.transfer4.local_kanjicode == modes::UTF8BOM ? KANJI_UTF8BOM : -1);
  MarkAsInternet = opt.transfer4.mark_as_internet ? YES : NO;
  // [ミラーリング]タブ
  wchar2VectorWstr(MirrorNoTrn, opt.mirroring.no_trn, opt.mirroring.no_trn_cnt);
  wchar2VectorWstr(MirrorNoDel, opt.mirroring.no_del, opt.mirroring.no_del_cnt);
  MirrorFnameCnv = opt.mirroring.fname_cnv ? YES : NO;
  MirUpDelNotify = opt.mirroring.up_del_notify ? YES : NO;
  MirDownDelNotify = opt.mirroring.down_del_notify ? YES : NO;
  MirrorNoTransferContents = opt.mirroring.no_transfer_contents ? YES : NO;
  // [操作]タブ
  RecvMode =
    opt.operation.recv_mode == modes::OVERWRITE ? TRANS_OVW :
    opt.operation.recv_mode == modes::CONFIRM   ? TRANS_DLG : -1;
  SendMode =
    opt.operation.send_mode == modes::OVERWRITE ? TRANS_OVW :
    opt.operation.send_mode == modes::CONFIRM   ? TRANS_DLG : -1;
  DclickOpen =
    opt.operation.dclick_mode == modes::OPEN ? YES : NO;
  MoveMode =
    opt.operation.move_mode == modes::NOCONFIRM ? MOVE_NODLG   :
    opt.operation.move_mode == modes::CONFIRM   ? MOVE_DLG     :
    opt.operation.move_mode == modes::DISABLE   ? MOVE_DISABLE : -1;
  // [表示1]タブ
  DispIgnoreHide = opt.view1.disp_ignore_hide ? YES : NO;
  DispDrives = opt.view1.disp_drives ? YES : NO;
  DispFileIcon = opt.view1.disp_file_icon ? YES : NO;
  DispTimeSeconds = opt.view1.disp_time_seconds ? YES : NO;
  // [表示2]タブ
  DispPermissionsNumber = opt.view2.disp_permissions_number ? YES : NO;
  AutoRefreshFileList = opt.view2.auto_refresh_filelist ? YES : NO;
  RemoveOldLog = opt.view2.remove_old_log ? YES : NO;
  // [接続/切断]タブ
  ConnectOnStart = opt.connecting.connect_on_start ? YES : NO;
  ConnectAndSet = opt.connecting.connect_and_set ? YES : NO;
  RasClose = opt.connecting.ras_close ? YES : NO;
  RasCloseNotify = opt.connecting.ras_close_notify ? YES : NO;
  FileHist = opt.connecting.file_hist;
  PassToHist = opt.connecting.pass_to_hist ? YES : NO;
  QuickAnonymous = opt.connecting.quick_anonymous ? YES : NO;
  SendQuit = opt.connecting.send_quit ? YES : NO;
  NoRasControl = opt.connecting.no_ras_control ? YES : NO;
  UPnPEnabled = opt.connecting.upnp_enabled ? YES : NO;
  // [FireWall]タブ
  FwallType = opt.firewall.type;
  FwallHost = opt.firewall.host;
  FwallPort = opt.firewall.port;
  FwallUser = opt.firewall.username;
  FwallPass = opt.firewall.password;
  FwallDelimiter = opt.firewall.delimiter;
  FwallSecurity = opt.firewall.security;
  FwallResolve = opt.firewall.resolve ? YES : NO;
  FwallLower = opt.firewall.lower ? YES : NO;
  FwallDefault = opt.firewall.fwall_default ? YES : NO;
  PasvDefault = opt.firewall.pasv_default ? YES : NO;
  FwallNoSaveUser = opt.firewall.no_save_user ? YES : NO;
  // [ツール]タブ
  for (int i = 0; i < ffftp_option_tool::VIEWER_CNT; ++i) {
    ViewerName[i] = opt.tool.viewer_name[i];
  }
  // [その他]タブ
  SaveWinPos = opt.other.save_win_pos ? YES : NO;
  RegType = opt.other.reg_type ? YES : NO;
  EncryptAllSettings = opt.other.encrypt_all_settings ? YES : NO;
  DebugConsole = opt.other.debug_console ? YES : NO;
}
#endif 

// 現在のオプションを取得する
LIBFFFTP_FUNCTION(void option(ffftp_option& opt))
#ifndef LIBFFFTP_DECL
{
  // vector<wstring>からwchar_tの配列に変換する関数オブジェクト
  auto vectorWstr2Wchar = [](const wchar_t**& out_str, size_t& out_cnt, const std::vector<std::wstring>& in_str) {
    delete[] out_str;
    out_str = nullptr;
    out_cnt = in_str.size();
    if (!in_str.empty()) {
      out_str = new const wchar_t*[out_cnt];
      for (int i = 0; const auto& str : in_str) {
        out_str[i++] = str.c_str();
      }
    }
  };
  // [ユーザー]タブ
  opt.user.user_mail_adrs = UserMailAdrs.c_str();
  // [転送1]タブ
  opt.transfer1 = {
      .trans_mode =
          AskTransferType() == TYPE_A ? modes::ASCII  :
          AskTransferType() == TYPE_I ? modes::BINARY :
          AskTransferType() == TYPE_X ? modes::AUTO   : -1,
      .rm_eof = RmEOF == YES,
      .save_timestamp = SaveTimeStamp == YES,
      .vax_semicolon = VaxSemicolon == YES,
      .make_all_dir = MakeAllDir == YES,
      .abort_on_list_error = AbortOnListError == YES,
  };
  vectorWstr2Wchar(opt.transfer1.ascii_ext, opt.transfer1.ascii_ext_cnt, AsciiExt);
  // [転送2]タブ
  opt.transfer2 = {
      .fname_cnv =
          FnameCnv == FNAME_LOWER ? modes::LOWER :
          FnameCnv == FNAME_UPPER ? modes::UPPER :
          FnameCnv == FNAME_NOCNV ? modes::NOCNV : -1,
      .timeout = TimeOut,
      .default_local_path = DefaultLocalPath.c_str(),
  };
  // [転送3]タブ
  delete[] opt.transfer3.attrlist_fname;
  delete[] opt.transfer3.attrlist_attr;
  opt.transfer3.attrlist_fname = nullptr;
  opt.transfer3.attrlist_attr = nullptr;
  opt.transfer3.attrlist_cnt = 0;
  if (!DefAttrList.empty()) {
    assert(DefAttrList.size() % 2 == 0);
    size_t list_cnt = DefAttrList.size() / 2;
    opt.transfer3.attrlist_fname = new const wchar_t*[list_cnt];
    opt.transfer3.attrlist_attr = new int[list_cnt];
    int i = 0;
    for (std::vector<std::wstring>::const_iterator it = DefAttrList.begin();
         it != DefAttrList.end();) {
      opt.transfer3.attrlist_fname[i] = (it++)->c_str();
      opt.transfer3.attrlist_attr[i] = std::stoi((it++)->c_str());
      ++i;
    }
    opt.transfer3.attrlist_cnt = list_cnt;
  }
  opt.transfer3.use_folder_attr = FolderAttr == YES;
  opt.transfer3.folder_attr = FolderAttrNum;
  // [転送4]タブ
  opt.transfer4 = {
      .local_kanjicode =
          AskLocalKanjiCode() == KANJI_SJIS    ? modes::SJIS    :
          AskLocalKanjiCode() == KANJI_JIS     ? modes::JIS     :
          AskLocalKanjiCode() == KANJI_EUC     ? modes::EUC     :
          AskLocalKanjiCode() == KANJI_UTF8N   ? modes::UTF8N   :
          AskLocalKanjiCode() == KANJI_UTF8BOM ? modes::UTF8BOM : -1,
      .mark_as_internet = MarkAsInternet == YES,
  };
  // [ミラーリング]タブ
  vectorWstr2Wchar(opt.mirroring.no_trn, opt.mirroring.no_trn_cnt, MirrorNoTrn);
  vectorWstr2Wchar(opt.mirroring.no_del, opt.mirroring.no_del_cnt, MirrorNoDel);
  opt.mirroring.fname_cnv = MirrorFnameCnv == YES;
  opt.mirroring.up_del_notify = MirUpDelNotify == YES;
  opt.mirroring.down_del_notify = MirDownDelNotify == YES;
  opt.mirroring.no_transfer_contents = MirrorNoTransferContents == YES;
  // [操作]タブ
  opt.operation = {
      .recv_mode =
          RecvMode == TRANS_OVW ? modes::OVERWRITE :
          RecvMode == TRANS_DLG ? modes::CONFIRM   : -1,
      .send_mode =
          SendMode == TRANS_OVW ? modes::OVERWRITE :
          SendMode == TRANS_DLG ? modes::CONFIRM   : -1,
      .dclick_mode =
          DclickOpen == YES ? modes::OPEN : modes::DOWNLOAD,
      .move_mode =
          MoveMode == MOVE_NODLG   ? modes::NOCONFIRM :
          MoveMode == MOVE_DLG     ? modes::CONFIRM   :
          MoveMode == MOVE_DISABLE ? modes::DISABLE   : -1,
  };
  // [表示1]タブ
  opt.view1 = {
      .font = -1,  // TODO: 未実装
      .disp_ignore_hide = DispIgnoreHide == YES,
      .disp_drives = DispDrives == YES,
      .disp_file_icon = DispFileIcon == YES,
      .disp_time_seconds = DispTimeSeconds == YES,

  };
  // [表示2]タブ
  opt.view2 = {
      .disp_permissions_number = DispPermissionsNumber == YES,
      .auto_refresh_filelist = AutoRefreshFileList == YES,
      .remove_old_log = RemoveOldLog == YES,
  };
  // [接続/切断]タブ
  opt.connecting = {
      .connect_on_start = ConnectOnStart == YES,
      .connect_and_set = ConnectAndSet == YES,
      .ras_close = RasClose == YES,
      .ras_close_notify = RasCloseNotify == YES,
      .file_hist = FileHist,
      .pass_to_hist = PassToHist == YES,
      .quick_anonymous = QuickAnonymous == YES,
      .send_quit = SendQuit == YES,
      .no_ras_control = NoRasControl == YES,
      .upnp_enabled = UPnPEnabled == YES,
  };
  // [FireWall]タブ
  opt.firewall = {
      .type = FwallType,
      .host = FwallHost.c_str(),
      .port = FwallPort,
      .username = FwallUser.c_str(),
      .password = FwallPass.c_str(),
      .delimiter = static_cast<wchar_t>(FwallDelimiter),
      .security = FwallSecurity,
      .resolve = FwallResolve == YES,
      .lower = FwallLower == YES,
      .fwall_default = FwallDefault == YES,
      .pasv_default = PasvDefault == YES,
      .no_save_user = FwallNoSaveUser == YES,
  };
  // [ツール]タブ
  for (int i = 0; i < ffftp_option_tool::VIEWER_CNT; ++i) {
    opt.tool.viewer_name[i] = ViewerName[i].c_str();
  }
  // [その他]タブ
  opt.other = {
      .save_win_pos = SaveWinPos == YES,
      .reg_type = RegType == YES,
      .encrypt_all_settings = EncryptAllSettings == YES,
      .debug_console = DebugConsole == YES,
  };
}
#endif

LIBFFFTP_FUNCTION(void showSoundSettings(void))
#ifndef LIBFFFTP_DECL
{
  __pragma(warning(suppress : 28159))
  WinExec(std::format("{} mmsys.cpl,,2"sv, (systemDirectory() / L"control.exe").string()).c_str(), SW_NORMAL);
}
#endif

}  // namespace libffftp

#endif
