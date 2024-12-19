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
};

typedef int (*ffftp_proc_callback)(unsigned int msg, ffftp_procparam param);

#ifdef __cplusplus
}
#endif

#endif /* FFFTP_COMMON_BB06576E_ED0F_43DD_98E3_B0A1925B1EAC_H_ */
