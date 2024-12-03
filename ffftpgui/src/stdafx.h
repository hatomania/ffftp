#include <QString>

#define DECL_CONST_CHAR(x) extern const char* const x;
#define DECL_CONST_WCHAR(x) extern const wchar_t* const x;
#define DECL_CONST_QSTRING(x) extern const QString x;

DECL_CONST_WCHAR(kEmptyString)
DECL_CONST_CHAR(kResImage_closedfolder16x16)
DECL_CONST_CHAR(kResImage_cleanfile16x16)
DECL_CONST_CHAR(kResImage_desktop16x16)

DECL_CONST_QSTRING(kAskSaveCryptTitle)
DECL_CONST_QSTRING(kAskSaveCryptBody)
DECL_CONST_QSTRING(kPlzInputYourMasterPwd)
DECL_CONST_QSTRING(kAskRetryInputYourMasterPwd)

DECL_CONST_QSTRING(kStringName)
DECL_CONST_QSTRING(kStringDate)
DECL_CONST_QSTRING(kStringSize)
DECL_CONST_QSTRING(kStringExtension)
DECL_CONST_QSTRING(kStringPermission)
DECL_CONST_QSTRING(kStringOwner)
