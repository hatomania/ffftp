/*=============================================================================
*							ＦＦＦＴＰ共通定義ファイル
*
===============================================================================
/ Copyright (C) 2021 K.C. All rights reserved.
/
/ Redistribution and use in source and binary forms, with or without 
/ modification, are permitted provided that the following conditions 
/ are met:
/
/  1. Redistributions of source code must retain the above copyright 
/     notice, this list of conditions and the following disclaimer.
/  2. Redistributions in binary form must reproduce the above copyright 
/     notice, this list of conditions and the following disclaimer in the 
/     documentation and/or other materials provided with the distribution.
/
/ THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR 
/ IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
/ OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
/ IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, 
/ INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
/ BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF 
/ USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON 
/ ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
/ (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF 
/ THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
/============================================================================*/

#include "common.h"
#include "ffftp.h"

extern int InitApp(int cmdShow);
extern DWORD MainThreadId;

class FFFTP {
public:
    explicit FFFTP();
    bool isOk() const { return isok_; }
private:
    bool isok_;
};

FFFTP::FFFTP() : isok_(false) {
    Sound::Register();

    // マルチコアCPUの特定環境下でファイル通信中にクラッシュするバグ対策
#ifdef DISABLE_MULTI_CPUS
    SetProcessAffinityMask(GetCurrentProcess(), 1);
#endif
    MainThreadId = GetCurrentThreadId();

    if (OleInitialize(nullptr) != S_OK) {
        Message(IDS_FAIL_TO_INIT_OLE, MB_OK | MB_ICONERROR);
        isok_ = false;
    }

    LoadUPnP();
    LoadTaskbarList3();
    LoadZoneID();

    if (!LoadSSL()) {
        Message(IDS_ERR_SSL, MB_OK | MB_ICONERROR);
        isok_ = false;
    }

    if (InitApp(SW_SHOWDEFAULT) != FFFTP_SUCCESS) {
        isok_ = false;
    }

    isok_ = true;
}

static FFFTP* _ffftp = nullptr;

LIBFFFTP_DECLSPEC bool LIBFFFTP_CALLCONV ffftp_initialize() {
    _ffftp = new FFFTP();
    bool isok = _ffftp->isOk();
    if (!isok) { ffftp_finalize(); }
    return isok;
}

LIBFFFTP_DECLSPEC void LIBFFFTP_CALLCONV ffftp_finalize() {
    delete _ffftp;
}

LIBFFFTP_DECLSPEC void LIBFFFTP_CALLCONV ffftp_playsound_connected() {
    Sound::Connected.Play();
}

LIBFFFTP_DECLSPEC void LIBFFFTP_CALLCONV ffftp_playsound_transferred() {
    Sound::Transferred.Play();
}

LIBFFFTP_DECLSPEC void LIBFFFTP_CALLCONV ffftp_playsound_error() {
    Sound::Error.Play();
}
