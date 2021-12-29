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
#include "libffftp.hpp"
#include "ffftp.h"

class FFFTP {
public:
    explicit FFFTP();
    virtual ~FFFTP();
    bool isOk() const { return isok_; }
    const wchar_t* getWindowTitle() const;
private:
    bool isok_;
};

FFFTP::FFFTP() : isok_(false) {
    isok_ = libffftp::initialize();
}

FFFTP::~FFFTP() {
    libffftp::finalize();
}

const wchar_t* FFFTP::getWindowTitle() const {
    static std::wstring windowtitle{};
    libffftp::getWindowTitle(windowtitle);
    return windowtitle.c_str();
}

static FFFTP* _ffftp = nullptr;

LIBFFFTP_DECLSPEC bool LIBFFFTP_CALLCONV ffftp_initialize() {
    if (!_ffftp) { _ffftp = new FFFTP(); }
    bool isok = _ffftp->isOk();
    if (!isok) { ffftp_finalize(); }
    return isok;
}

LIBFFFTP_DECLSPEC void LIBFFFTP_CALLCONV ffftp_finalize() {
    delete _ffftp;
    _ffftp = nullptr;
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

LIBFFFTP_DECLSPEC const wchar_t* LIBFFFTP_CALLCONV ffftp_get_window_title() {
    return _ffftp->getWindowTitle();
}

LIBFFFTP_DECLSPEC const hostcontext_t LIBFFFTP_CALLCONV ffftp_hostcontext_first(int* index) {
    return (const hostcontext_t)libffftp::hostContextFirst(index);
}

LIBFFFTP_DECLSPEC const hostcontext_t LIBFFFTP_CALLCONV ffftp_hostcontext_next(const hostcontext_t hc, int* index) {
    return (const hostcontext_t)libffftp::hostContextNext(hc, index);
}

LIBFFFTP_DECLSPEC int LIBFFFTP_CALLCONV ffftp_hostcontext_up(int index) {
    return libffftp::hostContextUp(index);
}

LIBFFFTP_DECLSPEC int LIBFFFTP_CALLCONV ffftp_hostcontext_down(int index) {
    return libffftp::hostContextDown(index);
}

LIBFFFTP_DECLSPEC int LIBFFFTP_CALLCONV ffftp_hostcontext_getindex(const hostcontext_t hc) {
    return libffftp::getHostIndex(hc);
}

LIBFFFTP_DECLSPEC const wchar_t* LIBFFFTP_CALLCONV ffftp_hostcontext_getname(const hostcontext_t hc) {
    static HOSTDATA hdata;
    hdata = libffftp::getHostContext(hc);
    return hdata.HostName.c_str();
}

LIBFFFTP_DECLSPEC int LIBFFFTP_CALLCONV ffftp_hostcontext_getlevel(const hostcontext_t hc) {
    return libffftp::getHostContextLevel(hc);
}

LIBFFFTP_DECLSPEC bool LIBFFFTP_CALLCONV ffftp_hostcontext_isgroup(const hostcontext_t hc) {
    return libffftp::getHostContext(hc).Level & SET_LEVEL_GROUP;
}
