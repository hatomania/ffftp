#pragma once

#include "common.h"

// libffftpのために用意されたインターフェース
namespace libffftp {
// main.cpp
extern bool initialize();
extern void finalize();
extern void getWindowTitle(std::wstring& title);
// hostman.cpp
extern const void* hostContextFirst(int* index = nullptr);
extern const void* hostContextNext(const void* hc, int* index=nullptr);
extern int hostContextUp(int index);
extern int hostContextDown(int index);
extern int getHostIndex(const void* hc);
extern HOSTDATA getHostContext(const void* hc);
extern int getHostContextLevel(const void* hc);
// taskwin.cpp
extern std::wstring getTaskMessage();
}
