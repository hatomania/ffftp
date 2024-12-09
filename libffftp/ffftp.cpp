/*=============================================================================
* ＦＦＦＴＰ共通定義ファイル
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

#include "ffftp.h"

#include "common.h"
#include "libffftp.hpp"

LIBFFFTP_DECLSPEC bool LIBFFFTP_CALLCONV ffftp_initialize() {
  return libffftp::initialize();
}

LIBFFFTP_DECLSPEC void LIBFFFTP_CALLCONV ffftp_finalize() {
  libffftp::finalize();
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

LIBFFFTP_DECLSPEC const wchar_t* LIBFFFTP_CALLCONV
ffftp_get_application_name() {
  return libffftp::getApplicationName();
}

LIBFFFTP_DECLSPEC const wchar_t* LIBFFFTP_CALLCONV ffftp_getwindowtitle() {
  static std::wstring windowtitle{};
  libffftp::getWindowTitle(windowtitle);
  return windowtitle.c_str();
}

LIBFFFTP_DECLSPEC const hostcontext_t LIBFFFTP_CALLCONV
ffftp_hostcontext_first() {
  return (const hostcontext_t)libffftp::hostContextFirst();
}

LIBFFFTP_DECLSPEC const hostcontext_t LIBFFFTP_CALLCONV
ffftp_hostcontext_next(const hostcontext_t hc) {
  return (const hostcontext_t)libffftp::hostContextNext(hc);
}

LIBFFFTP_DECLSPEC void LIBFFFTP_CALLCONV
ffftp_hostdata_initialize(hostdata* hdata) {
  std::memset(static_cast<void*>(hdata), 0, sizeof(hostdata));
}
LIBFFFTP_DECLSPEC void LIBFFFTP_CALLCONV
ffftp_hostdata_finalize(hostdata* hdata) {
  delete[] hdata->dialup.dial_entries;
}

LIBFFFTP_DECLSPEC void LIBFFFTP_CALLCONV
ffftp_hostcontext_new(const hostcontext_t hc, const hostdata* hdata) {
  libffftp::hostContextNew(hc, hdata);
}

LIBFFFTP_DECLSPEC void LIBFFFTP_CALLCONV
ffftp_hostcontext_up(const hostcontext_t hc) {
  libffftp::hostContextUp(hc);
}

LIBFFFTP_DECLSPEC void LIBFFFTP_CALLCONV
ffftp_hostcontext_down(const hostcontext_t hc) {
  libffftp::hostContextDown(hc);
}

LIBFFFTP_DECLSPEC void LIBFFFTP_CALLCONV
ffftp_hostcontext_hostdata_default(hostdata* hdata) {
  libffftp::hostContextDataDefault(hdata);
}

LIBFFFTP_DECLSPEC void LIBFFFTP_CALLCONV
ffftp_hostcontext_hostdata(const hostcontext_t hc, hostdata* hdata) {
  libffftp::hostContextData(hc, hdata);
}

LIBFFFTP_DECLSPEC const wchar_t* LIBFFFTP_CALLCONV
ffftp_hostcontext_getname(const hostcontext_t hc) {
  static HOSTDATA hdata;
  hdata = libffftp::hostContext(hc);
  return hdata.HostName.c_str();
}

LIBFFFTP_DECLSPEC int LIBFFFTP_CALLCONV
ffftp_hostcontext_getlevel(const hostcontext_t hc) {
  return libffftp::hostContextLevel(hc);
}

LIBFFFTP_DECLSPEC bool LIBFFFTP_CALLCONV
ffftp_hostcontext_isgroup(const hostcontext_t hc) {
  return libffftp::hostContext(hc).Level & SET_LEVEL_GROUP;
}

LIBFFFTP_DECLSPEC const wchar_t* LIBFFFTP_CALLCONV ffftp_gettaskmessage() {
  static std::wstring msg{};
  msg = libffftp::getTaskMessage();
  return msg.c_str();
}

LIBFFFTP_DECLSPEC bool LIBFFFTP_CALLCONV ffftp_connect(int index) {
  return libffftp::connect(index);
}

LIBFFFTP_DECLSPEC void LIBFFFTP_CALLCONV
ffftp_setcallback_asksavecrypt(bool (*func)()) {
  libffftp::setAskSaveCryptCallback(func);
}

LIBFFFTP_DECLSPEC void LIBFFFTP_CALLCONV
ffftp_setcallback_askmasterpassword(bool (*func)(const wchar_t** passwd)){
    LIBFFFTP_CALLBACK_SETTER(AskMasterPassword)}

LIBFFFTP_DECLSPEC void LIBFFFTP_CALLCONV
    ffftp_setcallback_askmasterpassword2nd(bool (*func)(
        const wchar_t** passwd)){LIBFFFTP_CALLBACK_SETTER(AskMasterPassword2nd)}

LIBFFFTP_DECLSPEC void LIBFFFTP_CALLCONV
    ffftp_setcallback_askretrymasterpassword(bool (*func)()) {
  LIBFFFTP_CALLBACK_SETTER(AskRetryMasterPassword)
}
