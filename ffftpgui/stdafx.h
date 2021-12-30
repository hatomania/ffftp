#include "ffftp.h"
#include <QtWidgets>
#include <QDebug>
#include <QtGui/QStandardItemModel>
#include <vector>

#define DECLARE_CONSTANT_CHAR(x) extern const char* const x;
#define DECLARE_CONSTANT_QSTRING(x) extern const QString x;

DECLARE_CONSTANT_CHAR(kEmptyString)
DECLARE_CONSTANT_CHAR(kResImage_closedfolder16x16)
DECLARE_CONSTANT_CHAR(kResImage_desktop16x16)

DECLARE_CONSTANT_QSTRING(kAskSaveCryptTitle)
DECLARE_CONSTANT_QSTRING(kAskSaveCryptBody)
