
#include "stdafx.h"

#include <QObject>
#include <QString>

#ifdef _MSC_VER
// コンパイル時に文字列リテラルをUTF-8に変換する
// Qtが扱う文字列はすべてUTF-8にしなければならないが
// コンパイラはShift-JIS(CP932)に変換してしまうため
// 全角文字列はQtのウィジェット上では文字化けしてしまう
#pragma execution_character_set("utf-8")
// プロジェクト全体で使用するグローバル変数の初期化処理を、
// 他のソースコードで定義されたグローバル変数の初期化処理より先に実行する
// これがないと下記のQString型定数が空文字列のまま参照されてしまうことがある
#pragma init_seg(lib)
#endif

#define IMPL_CONST_CHAR(x, str) const char* const x = str;
#define IMPL_CONST_WCHAR(x, str) const wchar_t* const x = str;
#define IMPL_CONST_QSTRING(x, str) const QString x = QObject::tr(str);

IMPL_CONST_WCHAR(kEmptyString, L"")
IMPL_CONST_CHAR(kResImage_closedfolder16x16, ":/closedfolder16x16.png")
IMPL_CONST_CHAR(kResImage_cleanfile16x16, ":/cleanfile16x16.png")
IMPL_CONST_CHAR(kResImage_desktop16x16, ":/desktop16x16.png")

// ユーザーに表示する文字列には必ずQObject::tr()で囲ってください
// この文字列は翻訳可能文字列となり、Qt
// Linguistソフトウェアでtsファイルを編集できるようになります
IMPL_CONST_QSTRING(kAskSaveCryptTitle, "暗号化の状態の保存")
IMPL_CONST_QSTRING(
    kAskSaveCryptBody,
    "現在の暗号化の状態を保存しますか？\n"
    "「はい」を選択すると次回から他の暗号化方式を試行しなくなります。")
IMPL_CONST_QSTRING(kPlzInputYourMasterPwd,
                   "設定されているマスターパスワードを入力してください:")
IMPL_CONST_QSTRING(
    kAskRetryInputYourMasterPwd,
    "指定されたマスターパスワードが登録されたものと一致しません。"
    "再度入力しますか？\n"
    "「いいえ」を選ぶと記憶されたFTPパスワードは利用できません。")

IMPL_CONST_QSTRING(kStringName, "名前")
IMPL_CONST_QSTRING(kStringDate, "日付")
IMPL_CONST_QSTRING(kStringSize, "サイズ")
IMPL_CONST_QSTRING(kStringExtension, "種類")
IMPL_CONST_QSTRING(kStringPermission, "属性")
IMPL_CONST_QSTRING(kStringOwner, "所有者")
