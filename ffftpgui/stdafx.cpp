﻿#include "stdafx.h"

#ifdef _MSC_VER
// コンパイル時に文字列リテラルをUTF-8に変換する
// Qtが扱う文字列はすべてUTF-8にしなければならないが
// コンパイラはShift-JIS(CP932)に変換してしまうため
// 全角文字列はQtのウィジェット上では文字化けしてしまう
#pragma execution_character_set("utf-8")
#endif

#define IMPLEMENT_CONSTANT_CHAR(x, str) const char* const x = str;

IMPLEMENT_CONSTANT_CHAR(kEmptyString, "")
IMPLEMENT_CONSTANT_CHAR(kResImage_closedfolder16x16, ":/resource/closedfolder16x16.png")
IMPLEMENT_CONSTANT_CHAR(kResImage_desktop16x16, ":/resource/desktop16x16.png")

// ユーザーに表示する文字列には必ずQObject::tr()で囲ってください
// この文字列は翻訳可能文字列となり、Qt Linguistソフトウェアでtsファイルを編集できるようになります
const QString kAskSaveCryptTitle = QObject::tr("暗号化の状態の保存");
const QString kAskSaveCryptBody = QObject::tr("現在の暗号化の状態を保存しますか？\n「はい」を選択すると次回から他の暗号化方式を試行しなくなります。");