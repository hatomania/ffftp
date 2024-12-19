#pragma once

#include "callback.h"  // コールバック関数プロトタイプ宣言はcallback.hに記載
#include "common.h"
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
extern HOSTDATA hostContext(const void* hc);
extern const void* hostContextFirst();
extern const void* hostContextNext(const void* hc);
extern const void* hostContextNew(const void* hc, const hostdata* hdata);
extern const void* hostContextNewGroup(const void* hc, const wchar_t* group_name);
extern const void* hostContextModify(const void* hc, const hostdata* hdata);
extern const void* hostContextModifyGroup(const void* hc, const wchar_t* group_name);
extern const void* hostContextCopy(const void* hc);
extern const void* hostContextDelete(const void* hc);
extern void hostContextUp(const void* hc);
extern void hostContextDown(const void* hc);
extern void hostContextSetDataDefault(const hostdata* hdata);
extern void hostContextDataDefault(hostdata* hdata);
extern void hostContextData(const void* hc, hostdata* hdata);
extern const wchar_t* hostContextName(const void* hc);
extern int hostContextLevel(const void* hc);
extern bool connect(const void* hc);
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
