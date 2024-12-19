#pragma once

#include "callback.h"  // コールバック関数プロトタイプ宣言はcallback.hに記載
#include "common.h"
#include "ffftp_common.h"
#include "ffftp_hostdata.h"
#include "ffftp_option.h"

// libffftpのために用意されたインターフェース
namespace libffftp {
// main.cpp
extern bool initialize();
extern void finalize();
extern const wchar_t* getApplicationName();
extern void getWindowTitle(std::wstring& title);
// hostman.cpp
extern HOSTDATA hostContext(ffftp_hostcontext_t hc);
extern ffftp_hostcontext_t hostContextFirst();
extern ffftp_hostcontext_t hostContextNext(ffftp_hostcontext_t hc);
extern ffftp_hostcontext_t hostContextNew(ffftp_hostcontext_t hc, const ffftp_hostdata* hdata);
extern ffftp_hostcontext_t hostContextNewGroup(ffftp_hostcontext_t hc, const wchar_t* group_name);
extern ffftp_hostcontext_t hostContextModify(ffftp_hostcontext_t hc, const ffftp_hostdata* hdata);
extern ffftp_hostcontext_t hostContextModifyGroup(ffftp_hostcontext_t hc, const wchar_t* group_name);
extern ffftp_hostcontext_t hostContextCopy(ffftp_hostcontext_t hc);
extern ffftp_hostcontext_t hostContextDelete(ffftp_hostcontext_t hc);
extern void hostContextUp(ffftp_hostcontext_t hc);
extern void hostContextDown(ffftp_hostcontext_t hc);
extern void hostContextSetDataDefault(const ffftp_hostdata* hdata);
extern void hostContextDataDefault(ffftp_hostdata* hdata);
extern void hostContextData(ffftp_hostcontext_t hc, ffftp_hostdata* hdata);
extern const wchar_t* hostContextName(ffftp_hostcontext_t hc);
extern int hostContextLevel(ffftp_hostcontext_t hc);
extern bool connect(ffftp_hostcontext_t hc);
extern void showHelp(int id);
// taskwin.cpp
extern std::wstring getTaskMessage();
// connect.cpp
extern void setAskSaveCryptCallback(bool (*func)());
// option.cpp
extern void setOption(const ffftp_option& opt);
extern void option(ffftp_option& opt);
extern void showSoundSettings(void);

}  // namespace libffftp
