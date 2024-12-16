#ifndef FFFTP_OPTION_50BC8B9D_E3EC_4111_98A7_D9921D9927DC_H_
#define FFFTP_OPTION_50BC8B9D_E3EC_4111_98A7_D9921D9927DC_H_

#ifndef __cplusplus
#include <wchar.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

enum modes {
  AUTO,
  ASCII,
  BINARY,

  LOWER,
  UPPER,
  NOCNV,

  SJIS,
  JIS,
  EUC,
  UTF8N,
  UTF8BOM,

  NOCONFIRM,
  CONFIRM,
  OVERWRITE,
  OPEN,
  DOWNLOAD,
  DISABLE,
};

/* [ユーザー]タブのUIデータ */
struct ffftp_option_user {
  const wchar_t* user_mail_adrs;
};

/* [転送1]タブのUIデータ */
struct ffftp_option_transfer1 {
  int trans_mode;
  const wchar_t** ascii_ext;
  size_t ascii_ext_cnt;
  bool rm_eof;
  bool save_timestamp;
  bool vax_semicolon;
  bool make_all_dir;
  bool abort_on_list_error;
};

/* [転送2]タブのUIデータ */
struct ffftp_option_transfer2 {
  int fname_cnv;
  int timeout;
  const wchar_t* default_local_path;
};

/* [転送3]タブのUIデータ */
struct ffftp_option_transfer3 {
  const wchar_t** attrlist_fname;
  int* attrlist_attr;
  size_t attrlist_cnt;
  bool use_folder_attr;
  int folder_attr;
};

/* [転送4]タブのUIデータ */
struct ffftp_option_transfer4 {
  int local_kanjicode;
  bool mark_as_internet;
};

/* [ミラーリング]タブのUIデータ */
struct ffftp_option_mirroring {
  const wchar_t** no_trn;
  size_t no_trn_cnt;
  const wchar_t** no_del;
  size_t no_del_cnt;
  bool fname_cnv;
  bool up_del_notify;
  bool down_del_notify;
  bool no_transfer_contents;
};

/* [操作]タブのUIデータ */
struct ffftp_option_operation {
  int recv_mode;
  int send_mode;
  int dclick_mode;
  int move_mode;
};

/* [表示1]タブのUIデータ */
struct ffftp_option_view1 {
  int font;
  bool disp_ignore_hide;
  bool disp_drives;
  bool disp_file_icon;
  bool disp_time_seconds;
};

/* [表示2]タブのUIデータ */
struct ffftp_option_view2 {
  bool disp_permissions_number;
  bool auto_refresh_filelist;
  bool remove_old_log;
};

/* [接続/切断]タブのUIデータ */
struct ffftp_option_connecting {
  bool connect_on_start;
  bool connect_and_set;
  bool ras_close;
  bool ras_close_notify;
  int file_hist;
  bool pass_to_hist;
  bool quick_anonymous;
  bool send_quit;
  bool no_ras_control;
  bool upnp_enabled;
};

/* [FireWall]タブのUIデータ */
struct ffftp_option_firewall {
  int type;
  const wchar_t* host;
  int port;
  const wchar_t* username;
  const wchar_t* password;
  wchar_t delimiter;
  int security;
  bool resolve;
  bool lower;
  bool fwall_default;
  bool pasv_default;
  bool no_save_user;
};

/* [ツール]タブのUIデータ */
struct ffftp_option_tool {
  enum { VIEWER_CNT = 3 };
  const wchar_t* viewer_name[VIEWER_CNT];
};

/* [その他]タブのUIデータ */
struct ffftp_option_other {};

struct ffftp_option {
  ffftp_option_user user;
  ffftp_option_transfer1 transfer1;
  ffftp_option_transfer2 transfer2;
  ffftp_option_transfer3 transfer3;
  ffftp_option_transfer4 transfer4;
  ffftp_option_mirroring mirroring;
  ffftp_option_operation operation;
  ffftp_option_view1 view1;
  ffftp_option_view2 view2;
  ffftp_option_connecting connecting;
  ffftp_option_firewall firewall;
  ffftp_option_tool tool;
  ffftp_option_other other;
};

#ifdef __cplusplus
}
#endif

#endif /* FFFTP_OPTION_50BC8B9D_E3EC_4111_98A7_D9921D9927DC_H_ */
