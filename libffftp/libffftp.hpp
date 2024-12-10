#pragma once

#include "callback.h"  // コールバック関数プロトタイプ宣言はcallback.hに記載
#include "common.h"
#include "ffftp_hostdata.h"

// libffftpのために用意されたインターフェース
namespace libffftp {
// main.cpp
extern bool initialize();
extern void finalize();
extern const wchar_t* getApplicationName();
extern void getWindowTitle(std::wstring& title);
// hostman.cpp
extern const void* hostContextFirst();
extern const void* hostContextNext(const void* hc);
extern const void* hostContextNew(const void* hc, const hostdata* hdata);
extern void hostContextUp(const void* hc);
extern void hostContextDown(const void* hc);
extern void hostContextDataDefault(hostdata* hdata);
extern void hostContextData(const void* hc, hostdata* hdata);
extern HOSTDATA hostContext(const void* hc);
extern int hostContextLevel(const void* hc);
extern bool connect(const void* hc);
// taskwin.cpp
extern std::wstring getTaskMessage();
// connect.cpp
extern void setAskSaveCryptCallback(bool (*func)());
}  // namespace libffftp
