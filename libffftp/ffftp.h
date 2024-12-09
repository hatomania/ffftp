/*=============================================================================
* ＦＦＦＴＰインターフェースファイル
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

#include "ffftp_hostdata.h"

#ifdef LIBFFFTP_EXPORTS
#define LIBFFFTP_DECLSPEC __declspec(dllexport)
#else
#define LIBFFFTP_DECLSPEC __declspec(dllimport)
#endif

#define LIBFFFTP_CALLCONV __cdecl

#ifndef __cplusplus
#include <wchar.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief libffftpの初期化を行う。
 *
 * 他のインターフェースを使用する前に呼び出さなければならない。@n
 * 呼び出しは1度だけ行う。複数回呼び出した場合の動作は未定義です。
 *
 * @retval true  成功
 * @retval false 失敗
 */
LIBFFFTP_DECLSPEC bool LIBFFFTP_CALLCONV ffftp_initialize();

/**
 * @brief libffftpの後処理を行う。
 *
 * アプリケーション終了時に1度だけ呼び出さなければならない。@n
 * 呼び出しは1度だけ行う。複数回呼び出した場合の動作は未定義です。
 */
LIBFFFTP_DECLSPEC void LIBFFFTP_CALLCONV ffftp_finalize();

LIBFFFTP_DECLSPEC void LIBFFFTP_CALLCONV ffftp_playsound_connected();
LIBFFFTP_DECLSPEC void LIBFFFTP_CALLCONV ffftp_playsound_transferred();
LIBFFFTP_DECLSPEC void LIBFFFTP_CALLCONV ffftp_playsound_error();

LIBFFFTP_DECLSPEC const wchar_t* LIBFFFTP_CALLCONV ffftp_get_application_name();
LIBFFFTP_DECLSPEC const wchar_t* LIBFFFTP_CALLCONV ffftp_getwindowtitle();

/**
 * @brief ユーザーが登録したホストを参照するコンテキスト。
 *
 * ホストの操作（新規追加、編集、削除等）はこのコンテキストを使って行います。
 */
typedef void* hostcontext_t;

/**
 * @brief 先頭のホストコンテキストを取得する。
 *
 * @return 先頭のホストコンテキスト。ホストリストが空の場合はnullptrを返す
 */
LIBFFFTP_DECLSPEC const hostcontext_t LIBFFFTP_CALLCONV
ffftp_hostcontext_first();

/**
 * @brief 指定したホストコンテキストの次のホストコンテキストを取得する。
 *
 * @param hc ホストコンテキスト
 * @return 指定したホストコンテキストの次のホストコンテキスト。次がない場合はnullptrを返す
 */
LIBFFFTP_DECLSPEC const hostcontext_t LIBFFFTP_CALLCONV
ffftp_hostcontext_next(const hostcontext_t hc);

/**
 * @brief hostdataの初期化を行う。
 *
 * hostdataを使用する前に、この関数を呼び出してhostdataを初期化しなければならない。
 * @param[in] hdata 初期化するhostdataへのポインタ
 */
LIBFFFTP_DECLSPEC void LIBFFFTP_CALLCONV
ffftp_hostdata_initialize(hostdata* hdata);
/**
 * @brief hostdataの後処理を行う。
 *
 * hostdataを使用し終わったらスコープを抜ける前に、この関数を呼び出してhostdataの後処理をしなければならない。@n
 * これを怠るとメモリリークを引き起こす可能性があります。
 * @param[in] hdata 後処理するhostdataへのポインタ
 */
LIBFFFTP_DECLSPEC void LIBFFFTP_CALLCONV
ffftp_hostdata_finalize(hostdata* hdata);

/**
 * @brief ホストを追加する。
 *
 * @param hc 追加の位置を示すホストコンテキスト。このホストコンテキストの次にホストが追加される。先頭に追加するにはnullptrを指定する。
 * @param hdata 追加するホスト情報のhostdataへのポインタ
 */
LIBFFFTP_DECLSPEC void LIBFFFTP_CALLCONV
ffftp_hostcontext_new(const hostcontext_t hc, const hostdata* hdata);

/**
 * @brief 指定したホストを、ホストリスト上のひとつ上へ移動する。
 *
 * @param hc 上へ移動するホストを示すホストコンテキスト
 */
LIBFFFTP_DECLSPEC void LIBFFFTP_CALLCONV
ffftp_hostcontext_up(const hostcontext_t hc);

/**
 * @brief 指定したホストを、ホストリスト上のひとつ下へ移動する。
 *
 * @param hc 下へ移動するホストを示すホストコンテキスト
 */
LIBFFFTP_DECLSPEC void LIBFFFTP_CALLCONV
ffftp_hostcontext_down(const hostcontext_t hc);

/**
 * @brief hostdataのデフォルト値を取得する。
 *
 * @param[out] hdata 結果を格納するhostdataへのポインタ
 */
LIBFFFTP_DECLSPEC void LIBFFFTP_CALLCONV
ffftp_hostcontext_hostdata_default(hostdata* hdata);

/**
 * @brief 指定したホストコンテキストのhostdataを取得する。
 *
 * @param[in]  hc hostdataを取得したいホストのホストコンテキストの
 * @param[out] hdata 結果を格納するhostdataへのポインタ
 */
LIBFFFTP_DECLSPEC void LIBFFFTP_CALLCONV
ffftp_hostcontext_hostdata(const hostcontext_t hc, hostdata* hdata);

LIBFFFTP_DECLSPEC const wchar_t* LIBFFFTP_CALLCONV
ffftp_hostcontext_getname(const hostcontext_t hc);
LIBFFFTP_DECLSPEC int LIBFFFTP_CALLCONV
ffftp_hostcontext_getlevel(const hostcontext_t hc);
LIBFFFTP_DECLSPEC bool LIBFFFTP_CALLCONV
ffftp_hostcontext_isgroup(const hostcontext_t hc);

LIBFFFTP_DECLSPEC const wchar_t* LIBFFFTP_CALLCONV ffftp_gettaskmessage();

LIBFFFTP_DECLSPEC bool LIBFFFTP_CALLCONV ffftp_connect(int index);
LIBFFFTP_DECLSPEC void LIBFFFTP_CALLCONV
ffftp_setcallback_asksavecrypt(bool (*func)());
LIBFFFTP_DECLSPEC void LIBFFFTP_CALLCONV
ffftp_setcallback_askmasterpassword(bool (*func)(const wchar_t** passwd));
LIBFFFTP_DECLSPEC void LIBFFFTP_CALLCONV
ffftp_setcallback_askmasterpassword2nd(bool (*func)(const wchar_t** passwd));
LIBFFFTP_DECLSPEC void LIBFFFTP_CALLCONV
ffftp_setcallback_askretrymasterpassword(bool (*func)());

#ifdef __cplusplus
}
#endif

#endif /* !FFFTP_2C8AE9F9_6CDE_41C7_AE02_CE4A7248088A_H_ */
