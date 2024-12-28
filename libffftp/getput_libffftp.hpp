#ifdef LIBFFFTP_OTHER

#ifndef LIBFFFTP_USE_WIN32API

// Transferクラスは直接ここに書きたいが、ここに直接書くとなぜかMOCがうまく動作してくれない
#include "transfer_libffftp.hpp"

static std::unique_ptr<Transfer> transferThread[MAX_DATA_CONNECTION]{};

// ファイル転送スレッドを起動する
int MakeTransferThread() noexcept {
  ClearAll = NO;
  ForceAbort = NO;
  fTransferThreadExit = false;
  for (int i = 0; i < MAX_DATA_CONNECTION; i++) {
    completed[i] = CreateEventW(nullptr, true, true, nullptr);
    transferThread[i] = std::make_unique<Transfer>(i);
//    QMetaObject::invokeMethod(transferThread[i].get(), "transfer", Qt::QueuedConnection);
  }
  completed[MAX_DATA_CONNECTION] = CreateEventW(nullptr, false, false, nullptr);
  return FFFTP_SUCCESS;
}

// ファイル転送スレッドを終了する
void CloseTransferThread() noexcept {
  for (int i = 0; i < MAX_DATA_CONNECTION; i++) {
    transferThread[i].reset();
  }
}

#endif  // LIBFFFTP_USE_WIN32API

#else  // LIBFFFTP_OTHER

#ifndef _WINDOWS
// Windows以外のプラットフォームでは、ゾーン関連の関数は何もしない
int LoadZoneID() { return FFFTP_SUCCESS; }
void FreeZoneID() {}
int IsZoneIDLoaded() noexcept { return YES; }
bool MarkFileAsDownloadedFromInternet([[maybe_unused]] const fs::path &path) { return true; }
#endif  //_WINDOWS

#endif  // LIBFFFTP_OTHER
