#ifndef FFFTP_OPTION_50BC8B9D_E3EC_4111_98A7_D9921D9927DC_H_
#define FFFTP_OPTION_50BC8B9D_E3EC_4111_98A7_D9921D9927DC_H_

#ifndef __cplusplus
#include <wchar.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* [ユーザー]タブのUIデータ */
struct ffftp_option_user {};

/* [転送1]タブのUIデータ */
struct ffftp_option_transfer1 {};

/* [転送2]タブのUIデータ */
struct ffftp_option_transfer2 {};

/* [転送3]タブのUIデータ */
struct ffftp_option_transfer3 {};

/* [転送4]タブのUIデータ */
struct ffftp_option_transfer4 {};

/* [ミラーリング]タブのUIデータ */
struct ffftp_option_mirroring {};

/* [操作]タブのUIデータ */
struct ffftp_option_operation {};

/* [表示1]タブのUIデータ */
struct ffftp_option_view1 {};

/* [表示2]タブのUIデータ */
struct ffftp_option_view2 {};

/* [接続/切断]タブのUIデータ */
struct ffftp_option_connecting {};

/* [FireWall]タブのUIデータ */
struct ffftp_option_firewall {};

/* [ツール]タブのUIデータ */
struct ffftp_option_tool {};

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
