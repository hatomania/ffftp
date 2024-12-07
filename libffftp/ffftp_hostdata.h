#ifndef FFFTP_HOSTDATA_D848290B_D2A5_447A_8897_5A261BC047AC_H_
#define FFFTP_HOSTDATA_D848290B_D2A5_447A_8897_5A261BC047AC_H_

#ifndef __cplusplus
#include <wchar.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* [基本]タブのUIデータ */
struct hostdata_general {
  const wchar_t* host_name;
  const wchar_t* host_adrs;
  const wchar_t* username;
  const wchar_t* password;
  bool anonymous;
  const wchar_t* initdir_local;
  const wchar_t* initdir_remote;
  const wchar_t* initdir_remote_now;
  bool enabled_curdir;
  bool last_dir;
};

/* [拡張]タブのUIデータ */
struct hostdata_advanced {
  bool firewall;
  bool pasv;
  bool syncmove;
  int port;
  const wchar_t* account;
  int timezone;
  int security;
  const wchar_t* initcmd;
};

/* 文字コード */
enum kanjicodes {
  KC_NOP,
  KC_AUTO,
  KC_JIS,
  KC_SJIS,
  KC_EUC,
  KC_SMH,
  KC_SMC,
  KC_UTF8N,
  KC_UTF8BOM,
  KC_UTF8HFSX,
};

struct hostdata_kanjicode {
  int kanjicode;
  bool kanacnv;
  int kanjicode_name;
  bool kanacnv_name;
};

struct hostdata {
  hostdata_general general;
  hostdata_advanced advanced;
  hostdata_kanjicode kanjicode;
};

#ifdef __cplusplus
}
#endif

#endif /* FFFTP_HOSTDATA_D848290B_D2A5_447A_8897_5A261BC047AC_H_ */
