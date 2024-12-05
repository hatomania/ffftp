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

struct hostdata {
  hostdata_general general;
  hostdata_advanced advanced;
};

#ifdef __cplusplus
}
#endif

#endif /* FFFTP_HOSTDATA_D848290B_D2A5_447A_8897_5A261BC047AC_H_ */
