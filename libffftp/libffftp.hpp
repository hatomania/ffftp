#pragma once

#include "common.h"

// libffftpのために用意されたインターフェース
namespace libffftp {
// main.cpp
extern bool initialize();
extern void finalize();
extern const wchar_t* getApplicationName();
extern void getWindowTitle(std::wstring& title);
LIBFFFTP_DECLARE_CALLBACK(bool, AskMasterPassword, (const wchar_t** passwd))
LIBFFFTP_DECLARE_CALLBACK(bool, AskMasterPassword2nd, (const wchar_t** passwd))
LIBFFFTP_DECLARE_CALLBACK(bool, AskRetryMasterPassword, ())
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
// connect.cpp
extern bool connect(int index);
extern void setAskSaveCryptCallback(bool (*func)());
}
