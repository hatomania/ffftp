#ifndef FFFTP_COMMON_BB06576E_ED0F_43DD_98E3_B0A1925B1EAC_H_
#define FFFTP_COMMON_BB06576E_ED0F_43DD_98E3_B0A1925B1EAC_H_

#ifdef LIBFFFTP_EXPORTS
#define LIBFFFTP_DECLSPEC __declspec(dllexport)
#else
#define LIBFFFTP_DECLSPEC __declspec(dllimport)
#endif

#define LIBFFFTP_CALLCONV __stdcall

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

typedef unsigned long long (LIBFFFTP_CALLCONV *ffftp_proc_callback)(unsigned long long msg, ffftp_procparam param);

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
  OPTION_DLG,
};

enum ffftp_messageid {
  SID_REMOVE_READONLY             = 223,
  SID_MASTER_PASSWORD_INCORRECT   = 225,
  SID_FAIL_TO_INIT_OLE            = 224,
  SID_ERR_SSL                     = 202,
  SID_FOUND_NEW_VERSION_INI       = 229,
  SID_MANAGE_STATEFUL_FTP         = 227,
  SID_FAIL_TO_MANAGE_STATEFUL_FTP = 228,
  SID_NEED_RESTART                = 221,
  SID_PASSWORD_ISNOT_IDENTICAL    = 226,
  SID_FAIL_TO_EXEC_REDEDIT        = 220,
  SID_MUST_BE_REG_OR_INI          = 222,
  SID_CANT_SAVE_TO_INI            = 219,
  SID_FAIL_TO_EXPORT              = 230,
  SID_NEED_EXSITING_WINSCP_INI    = 231,
};

enum ffftp_eventid {
  EID_DEFAULT,
  EID_CREATE,
  EID_TIMER,
  EID_MENU_CONNECT,
  EID_MENU_CONNECT_NUM,
  EID_MENU_SET_CONNECT,
  EID_MENU_QUICK,
  EID_MENU_DISCONNECT,
  EID_MENU_HIST_01,
  EID_MENU_HIST_02,
  EID_MENU_HIST_03,
  EID_MENU_HIST_04,
  EID_MENU_HIST_05,
  EID_MENU_HIST_06,
  EID_MENU_HIST_07,
  EID_MENU_HIST_08,
  EID_MENU_HIST_09,
  EID_MENU_HIST_10,
  EID_MENU_HIST_11,
  EID_MENU_HIST_12,
  EID_MENU_HIST_13,
  EID_MENU_HIST_14,
  EID_MENU_HIST_15,
  EID_MENU_HIST_16,
  EID_MENU_HIST_17,
  EID_MENU_HIST_18,
  EID_MENU_HIST_19,
  EID_MENU_HIST_20,
  EID_MENU_UPDIR,
  EID_MENU_DCLICK,
  EID_MENU_OPEN,
  EID_MENU_OPEN1,
  EID_MENU_OPEN2,
  EID_MENU_OPEN3,
  EID_MENU_REMOTE_UPDIR,
  EID_MENU_LOCAL_UPDIR,
  EID_MENU_REMOTE_CHDIR,
  EID_MENU_LOCAL_CHDIR,
  EID_MENU_DOWNLOAD,
  EID_MENU_DOWNLOAD_AS,
  EID_MENU_DOWNLOAD_AS_FILE,
  EID_MENU_DOWNLOAD_ALL,
  EID_MENU_DOWNLOAD_NAME,
  EID_MENU_UPLOAD,
  EID_MENU_UPLOAD_AS,
  EID_MENU_UPLOAD_ALL,
  EID_MENU_MIRROR_UPLOAD,
  EID_MENU_MIRROR_DOWNLOAD,
  EID_MENU_FILESIZE,
  EID_MENU_DELETE,
  EID_MENU_RENAME,
  EID_MENU_MKDIR,
  EID_MENU_CHMOD,
  EID_MENU_SOMECMD,
  EID_MENU_OPTION,
  EID_MENU_FILTER,
  EID_MENU_SORT,
  EID_MENU_EXIT,
  EID_MENU_AUTO_EXIT,
  EID_MENU_ABOUT,
  EID_MENU_TEXT,
  EID_MENU_BINARY,
  EID_MENU_AUTO,
  EID_MENU_XFRMODE,
  EID_MENU_KNJ_SJIS,
  EID_MENU_KNJ_EUC,
  EID_MENU_KNJ_JIS,
  EID_MENU_KNJ_UTF8N,
  EID_MENU_KNJ_UTF8BOM,
  EID_MENU_KNJ_NONE,
  EID_MENU_L_KNJ_SJIS,
  EID_MENU_L_KNJ_EUC,
  EID_MENU_L_KNJ_JIS,
  EID_MENU_L_KNJ_UTF8N,
  EID_MENU_L_KNJ_UTF8BOM,
  EID_MENU_KANACNV,
  EID_MENU_REFRESH,
  EID_MENU_LIST,
  EID_MENU_REPORT,
  EID_REFRESH_LOCAL,
  EID_REFRESH_REMOTE,
  EID_COMBO_LOCAL,
  EID_COMBO_REMOTE,
  EID_MENU_HELP,
  EID_MENU_HELP_TROUBLE,
  EID_MENU_BMARK_ADD,
  EID_MENU_BMARK_ADD_LOCAL,
  EID_MENU_BMARK_ADD_BOTH,
  EID_MENU_BMARK_EDIT,
  EID_MENU_SELECT_ALL,
  EID_MENU_SELECT,
  EID_MENU_FIND,
  EID_MENU_FINDNEXT,
  EID_MENU_DOTFILE,
  EID_MENU_SYNC,
  EID_MENU_IMPORT_WS,
  EID_MENU_REGSAVE,
  EID_MENU_REGLOAD,
  EID_MENU_REGINIT,
  EID_MENU_CHANGEPASSWD,
  EID_MENU_DIRINFO,
  EID_MENU_TASKINFO,
  EID_MENU_ABORT,
  EID_MENU_OTPCALC,
  EID_MENU_FW_FTP_FILTER,
  EID_MENU_URL_COPY,
  EID_MENU_APPKEY,
  EID_MENU_SWITCH_OSS,
  EID_MENU_REMOTE_MOVE_UPDIR,
  EID_MENU_EXPORT_FILEZILLA_XML,
  EID_MENU_EXPORT_WINSCP_INI,
  EID_TTN_GETDISPINFOW,
  EID_LVN_COLUMNCLICK,
  EID_LVN_ITEMCHANGED,
  EID_SIZE,
  EID_MOVING,
  EID_SETFOCUS,
  EID_LBUTTONDOWN,
  EID_LBUTTONUP,
  EID_MOUSEMOVE,
  EID_CHANGE_COND,
  EID_REFRESH_LOCAL_FLG,
  EID_REFRESH_REMOTE_FLG,
  EID_RECONNECTSOCKET,
  EID_MAINTHREADRUNNER,
  EID_PAINT,
  EID_DESTROY,
  EID_QUERYENDSESSION,
  EID_CLOSE,
};

struct ffftp_procparam_quickconnect {
  const wchar_t* history[20];
  size_t history_cnt;
  const wchar_t* hostname;
  const wchar_t* username;
  const wchar_t* password;
  bool use_firewall;
  bool use_passive;
};

#ifdef __cplusplus
}
#endif

#endif /* FFFTP_COMMON_BB06576E_ED0F_43DD_98E3_B0A1925B1EAC_H_ */
