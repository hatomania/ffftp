#ifndef FFFTP_COMMON_BB06576E_ED0F_43DD_98E3_B0A1925B1EAC_H_
#define FFFTP_COMMON_BB06576E_ED0F_43DD_98E3_B0A1925B1EAC_H_

#ifndef __cplusplus
#include <wchar.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief ユーザーが登録したホストを参照するコンテキスト。
 *
 * ホストの操作（新規追加、編集、削除、複製等）はこのコンテキストを使って行います。
 */
typedef void* ffftp_hostcontext_t;

struct ffftp_procparam {
  void* param1;
  void* param2;
  void* param3;
  void* param4;
};

enum ffftp_procmsg {
  SHOW_MESSAGEBOX,
  SHOW_DIALOGBOX,
};

typedef unsigned long long (*ffftp_proc_callback)(unsigned long long msg, ffftp_procparam param);

enum ffftp_dialogid {
  ABOUT_DLG =                       104,
  TRANSFER_DLG =                    109,
  RENAME_DLG =                      110,
  DELETE_DLG =                      111,
  HOSTLIST_DLG =                    112,
  HOSTSET_DLG =                     113,
  HSET_MAIN_DLG =                   113,
  USER_DLG =                        115,
  OPT_USER_DLG =                    115,
  TOOL_DLG =                        116,
  OPT_TOOL_DLG =                    116,
  PERMIT_DLG =                      117,
  CHMOD_DLG =                       117,
  SORT_DLG =                        118,
  TRMODE_DLG =                      119,
  MKDIR_DLG =                       120,
  OPT_MISC_DLG =                    121,
  HOSTNAME_DLG =                    122,
  PASSWD_DLG =                      123,
  USERNAME_DLG =                    124,
  CHDIR_DLG =                       125,
  EXIT_DLG =                        126,
  EXIST_DLG =                       127,
  DOWN_EXIST_DLG =                  127,
  OPT_TRMODE_DLG =                  128,
  OPT_TRMODE2_DLG =                 128,
  OPT_NOTIFY_DLG =                  129,
  BMARK_DLG =                       130,
  OPT_FIRE_DLG =                    131,
  HSET_ADV_DLG =                    132,
  DISKFULL_DLG =                    133,
  FIND_DLG =                        134,
  DOWNERR_DLG =                     137,
  UPERR_DLG =                       138,
  HSET_CODE_DLG =                   139,
  OPT_TRMODE_DLG1 =                 140,
  OPT_TRMODE1_DLG =                 140,
  EXIST_DLG1 =                      141,
  UP_EXIST_DLG =                    142,
  REGINIT_DLG =                     143,
  HOSTCONNECT_DLG =                 144,
  UPDOWN_AS_DLG =                   145,
  RE_PASSWD_DLG =                   146,
  SAVEPASS_DLG =                    147,
  SEL_LOCAL_DLG =                   148,
  SEL_REMOTE_DLG =                  149,
  MIRROR_UP_DLG =                   150,
  ACCOUNT_DLG =                     151,
  OPT_MIRROR_DLG =                  152,
  SOMECMD_DLG =                     153,
  DOWNNAME_DLG =                    154,
  OPT_CONNECT_DLG =                 155,
  RASNOTIFY_DLG =                   156,
  FILESIZE_DLG =                    157,
  FILESIZE_NOTIFY_DLG =             158,
  HSET_ADV2_DLG =                   159,
  CWDERR_DLG =                      160,
  OPT_TRMODE3_DLG =                 161,
  DEF_ATTR_DLG =                    162,
  FNAME_IN_DLG =                    163,
  OTP_NOTIFY_DLG =                  164,
  OTP_CALC_DLG =                    165,
  MIRROR_NOTIFY_DLG =               166,
  MIRRORDOWN_NOTIFY_DLG =           167,
  MIRROR_DOWN_DLG =                 168,
  CHDIR_BR_DLG =                    169,
  FILTER_DLG =                      170,
  GROUP_DLG =                       172,
  HOSTDEL_DLG =                     173,
  GROUPDEL_DLG =                    174,
  NORESUME_DLG =                    175,
  FORCERENAME_DLG =                 176,
  HSET_DIALUP_DLG =                 177,
  RASRECONNECT_DLG =                178,
  OPT_DISP1_DLG =                   181,
  BMARK_EDIT_DLG =                  182,
  OPT_TOOL_DLG1 =                   183,
  MOVE_NOTIFY_DLG =                 185,
  FORCEPASSCHANGE_DLG =             186,
  NEWMASTERPASSWD_DLG =             187,
  MASTERPASSWD_DLG =                188,
  HSET_CRYPT_DLG =                  189,
  HSET_ADV3_DLG =                   190,
  SAVECRYPT_DLG =                   191,
  UPDATESSLROOT_DLG =               192,
  UPDOWN_AS_WITH_EXT_DLG =          193,
  INI_FROM_REG_DLG =                194,
  OPT_TRMODE4_DLG =                 195,
  OPT_DISP2_DLG =                   196,
  CORRUPTSETTINGS_DLG =             198,
  CERTERR_DLG =                     199,
};

#ifdef __cplusplus
}
#endif

#endif /* FFFTP_COMMON_BB06576E_ED0F_43DD_98E3_B0A1925B1EAC_H_ */
