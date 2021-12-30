#include "stdafx.h"

#define IMPLEMENT_CONSTANT_CHAR(x, str) const char* const x = str;
#define IMPLEMENT_CONSTANT_QSTRING(x, str) const QString x{ QObject::tr(QString::fromWCharArray(str).toStdString().c_str()) };

IMPLEMENT_CONSTANT_CHAR(kEmptyString, "")
IMPLEMENT_CONSTANT_CHAR(kResImage_closedfolder16x16, ":/resource/closedfolder16x16.png")
IMPLEMENT_CONSTANT_CHAR(kResImage_desktop16x16, ":/resource/desktop16x16.png")

IMPLEMENT_CONSTANT_QSTRING(kAskSaveCryptTitle, L"暗号化の状態の保存")
IMPLEMENT_CONSTANT_QSTRING(kAskSaveCryptBody, L"現在の暗号化の状態を保存しますか？\n「はい」を選択すると次回から他の暗号化方式を試行しなくなります。")
