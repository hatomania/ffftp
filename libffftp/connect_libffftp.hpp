﻿#ifdef LIBFFFTP_OTHER

// 途中でダイアログを表示してユーザに問い合わせる部分の実装はコールバック関数に委ねる
// libffftpを使う側が責任をもって自前のGUIフレームワークに合わせた実装をする
static bool AskSaveCryptDefaultCallback() {
  return (bool)Dialog(GetFtpInst(), savecrypt_dlg, GetMainHwnd());
}
typedef bool (*AskSaveCryptFunc)();
static AskSaveCryptFunc asksavecrypt_func = AskSaveCryptDefaultCallback;


#else

#include "libffftp_common.hpp"

// libffftpのために用意されたインターフェース
namespace libffftp {

LIBFFFTP_FUNCTION(void setAskSaveCryptCallback(bool (*func)()))
#ifndef LIBFFFTP_DECL
{
  asksavecrypt_func = func;
}
#endif

}  // namespace libffftp

#endif