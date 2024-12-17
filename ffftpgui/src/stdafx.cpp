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

#define IMPL_CONST_INT(x, v) const int x = v
#define IMPL_CONST_CHAR(x, v) const char* const x = v
#define IMPL_CONST_WCHAR(x, v) const wchar_t* const x = v
#define IMPL_CONST_QSTRING(x, v) const QString x = QObject::tr(v)

IMPL_CONST_CHAR(kEmptyString, "");
IMPL_CONST_CHAR(kResImage_closedfolder16x16, ":/closedfolder16x16.png");
IMPL_CONST_CHAR(kResImage_cleanfile16x16, ":/cleanfile16x16.png");
IMPL_CONST_CHAR(kResImage_desktop16x16, ":/desktop16x16.png");

// ユーザーに表示する文字列には必ずQObject::tr()で囲ってください
// この文字列は翻訳可能文字列となり、Qt
// Linguistソフトウェアでtsファイルを編集できるようになります
IMPL_CONST_QSTRING(kAskSaveCryptTitle, "暗号化の状態の保存");
IMPL_CONST_QSTRING(
    kAskSaveCryptBody,
    "現在の暗号化の状態を保存しますか？\n"
    "「はい」を選択すると次回から他の暗号化方式を試行しなくなります。");
IMPL_CONST_QSTRING(kPlzInputYourMasterPwd,
                   "設定されているマスターパスワードを入力してください:");
IMPL_CONST_QSTRING(
    kAskRetryInputYourMasterPwd,
    "指定されたマスターパスワードが登録されたものと一致しません。"
    "再度入力しますか？\n"
    "「いいえ」を選ぶと記憶されたFTPパスワードは利用できません。");

IMPL_CONST_QSTRING(kStringName, "名前");
IMPL_CONST_QSTRING(kStringDate, "日付");
IMPL_CONST_QSTRING(kStringSize, "サイズ");
IMPL_CONST_QSTRING(kStringExtension, "種類");
IMPL_CONST_QSTRING(kStringPermission, "属性");
IMPL_CONST_QSTRING(kStringAttribute, "属性");
IMPL_CONST_QSTRING(kStringOwner, "所有者");
IMPL_CONST_QSTRING(kStringGroupName, "グループ名");
IMPL_CONST_QSTRING(kStringGroupNameNew, "グループを追加");
IMPL_CONST_QSTRING(kStringGroupNameMod, "グループ名を変更");
IMPL_CONST_QSTRING(kStringGroupNameAccess, "グループ名(&G):");
IMPL_CONST_QSTRING(kStringDeleteHost, "ホストの削除");
IMPL_CONST_QSTRING(kStringDeleteHostMsg, "ホストの設定を削除しますか？");
IMPL_CONST_QSTRING(kStringDeleteGroup, "グループの削除");
IMPL_CONST_QSTRING(kStringDeleteGroupMsg,
                   "グループとグループ内の全てのホストの設定を削除しますか？");
IMPL_CONST_QSTRING(kStringFileName, "ファイル名");
IMPL_CONST_QSTRING(kStringFileNameAccess, "ファイル名(&F):");
IMPL_CONST_QSTRING(kStringAlsoSpecifyFolder, "フォルダ名も指定できます");
IMPL_CONST_QSTRING(kStringFileNameNotTrans, "転送しないファイル名(&F)");
IMPL_CONST_QSTRING(kStringFileNameNotDelete, "削除しないファイル名(&R)");
IMPL_CONST_QSTRING(kStringFileNameAsciiMode, "アスキーモードのファイル名(&F)");
IMPL_CONST_QSTRING(kStringFileAttrUploaded, "アップロードするファイルの属性(&P)");

IMPL_CONST_INT(kHelpTopicHostList, 27);
IMPL_CONST_INT(kHelpTopicHostSettingGeneral, 28);
IMPL_CONST_INT(kHelpTopicHostSettingAdvanced, 29);
IMPL_CONST_INT(kHelpTopicHostSettingKanjiCode, 30);
IMPL_CONST_INT(kHelpTopicHostSettingDialup, 31);
IMPL_CONST_INT(kHelpTopicHostSettingSpecial, 32);
IMPL_CONST_INT(kHelpTopicHostSettingEncryption, 65);
IMPL_CONST_INT(kHelpTopicHostSettingFeature, 66);
IMPL_CONST_INT(kHelpTopicOptionUser, 41);
IMPL_CONST_INT(kHelpTopicOptionTransfer1, 42);
IMPL_CONST_INT(kHelpTopicOptionTransfer2, 43);
IMPL_CONST_INT(kHelpTopicOptionTransfer3, 44);
IMPL_CONST_INT(kHelpTopicOptionTransfer4, 67);
IMPL_CONST_INT(kHelpTopicOptionMirroring, 45);
IMPL_CONST_INT(kHelpTopicOptionOperation, 46);
IMPL_CONST_INT(kHelpTopicOptionView1, 47);
IMPL_CONST_INT(kHelpTopicOptionView2, 68);
IMPL_CONST_INT(kHelpTopicOptionConnecting, 48);
IMPL_CONST_INT(kHelpTopicOptionFirewall, 49);
IMPL_CONST_INT(kHelpTopicOptionTool, 50);
IMPL_CONST_INT(kHelpTopicOptionOther, 52);
IMPL_CONST_INT(kHelpTopicAttrSetting, 17);
