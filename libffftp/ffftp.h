/*=============================================================================
*						ＦＦＦＴＰインターフェースファイル
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

#ifndef FFFTP_2C8AE9F9_6CDE_41C7_AE02_CE4A7248088A_H_
#define FFFTP_2C8AE9F9_6CDE_41C7_AE02_CE4A7248088A_H_

#ifdef LIBFFFTP_EXPORTS
#define LIBFFFTP_DECLSPEC __declspec(dllexport)
#else
#define LIBFFFTP_DECLSPEC __declspec(dllimport)
#endif

#define LIBFFFTP_CALLCONV __cdecl

#ifdef __cplusplus
extern "C" {
#endif

LIBFFFTP_DECLSPEC bool LIBFFFTP_CALLCONV ffftp_initialize();
LIBFFFTP_DECLSPEC void LIBFFFTP_CALLCONV ffftp_finalize();

LIBFFFTP_DECLSPEC void LIBFFFTP_CALLCONV ffftp_playsound_connected();
LIBFFFTP_DECLSPEC void LIBFFFTP_CALLCONV ffftp_playsound_transferred();
LIBFFFTP_DECLSPEC void LIBFFFTP_CALLCONV ffftp_playsound_error();

LIBFFFTP_DECLSPEC const wchar_t* LIBFFFTP_CALLCONV ffftp_get_window_title();

typedef void* hostcontext_t;
#ifdef __cplusplus
LIBFFFTP_DECLSPEC const hostcontext_t LIBFFFTP_CALLCONV ffftp_hostcontext_first(int* index = nullptr);
LIBFFFTP_DECLSPEC const hostcontext_t LIBFFFTP_CALLCONV ffftp_hostcontext_next(const hostcontext_t hc, int* index = nullptr);
#else
LIBFFFTP_DECLSPEC const hostcontext_t LIBFFFTP_CALLCONV ffftp_hostcontext_first(int* index = NULL);
LIBFFFTP_DECLSPEC const hostcontext_t LIBFFFTP_CALLCONV ffftp_hostcontext_next(const hostcontext_t hc, int* index = NULL);
#endif
LIBFFFTP_DECLSPEC int LIBFFFTP_CALLCONV ffftp_hostcontext_up(int index);
LIBFFFTP_DECLSPEC int LIBFFFTP_CALLCONV ffftp_hostcontext_down(int index);
LIBFFFTP_DECLSPEC int LIBFFFTP_CALLCONV ffftp_hostcontext_getindex(const hostcontext_t hc);
LIBFFFTP_DECLSPEC const wchar_t* LIBFFFTP_CALLCONV ffftp_hostcontext_getname(const hostcontext_t hc);
LIBFFFTP_DECLSPEC int LIBFFFTP_CALLCONV ffftp_hostcontext_getlevel(const hostcontext_t hc);
LIBFFFTP_DECLSPEC bool LIBFFFTP_CALLCONV ffftp_hostcontext_isgroup(const hostcontext_t hc);

#ifdef __cplusplus
}
#endif

#endif /* !FFFTP_2C8AE9F9_6CDE_41C7_AE02_CE4A7248088A_H_ */
