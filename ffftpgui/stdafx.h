#include "ffftp.h"
#include <QtWidgets/QtWidgets>
#include <QtCore/QDebug>
#include <QtGui/QStandardItemModel>
#include <vector>

#define DECLARE_CONSTANT_CHAR(x) extern const char* const x;
#define DECLARE_CONSTANT_QSTRING(x) extern const QString x;

DECLARE_CONSTANT_CHAR(kEmptyString)
DECLARE_CONSTANT_CHAR(kResImage_closedfolder16x16)
DECLARE_CONSTANT_CHAR(kResImage_cleanfile16x16)
DECLARE_CONSTANT_CHAR(kResImage_desktop16x16)

DECLARE_CONSTANT_QSTRING(kAskSaveCryptTitle)
DECLARE_CONSTANT_QSTRING(kAskSaveCryptBody)
DECLARE_CONSTANT_QSTRING(kPlzInputYourMasterPwd)

DECLARE_CONSTANT_QSTRING(kStringName)
DECLARE_CONSTANT_QSTRING(kStringDate)
DECLARE_CONSTANT_QSTRING(kStringSize)
DECLARE_CONSTANT_QSTRING(kStringExtension)
DECLARE_CONSTANT_QSTRING(kStringPermission)
DECLARE_CONSTANT_QSTRING(kStringOwner)
