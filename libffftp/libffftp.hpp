#pragma once

#include "common.h"
#include "callback.h"// コールバック関数プロトタイプ宣言はcallback.hに記載
#include "ffftp_hostdata.h"

// libffftpのために用意されたインターフェース
namespace libffftp {
// main.cpp
extern bool initialize();
extern void finalize();
extern const wchar_t* getApplicationName();
extern void getWindowTitle(std::wstring& title);
// hostman.cpp
extern const void* hostContextFirst(int* index = nullptr);
extern const void* hostContextNext(const void* hc, int* index=nullptr);
extern void hostContextNew(int index, const hostdata* hdata);
extern int hostContextUp(int index);
extern int hostContextDown(int index);
extern void hostContextData(int index, hostdata* hdata);
extern int getHostIndex(const void* hc);
extern int currentHostIndex();
extern HOSTDATA getHostContext(const void* hc);
extern int getHostContextLevel(const void* hc);
// taskwin.cpp
extern std::wstring getTaskMessage();
// connect.cpp
extern bool connect(int index);
extern void setAskSaveCryptCallback(bool (*func)());
}
