#include <QString>

#define DECL_CONST_INT(x) extern const int x
#define DECL_CONST_CHAR(x) extern const char* const x
#define DECL_CONST_WCHAR(x) extern const wchar_t* const x
#define DECL_CONST_QSTRING(x) extern const QString x

DECL_CONST_CHAR(kEmptyString);
DECL_CONST_CHAR(kResImage_closedfolder16x16);
DECL_CONST_CHAR(kResImage_cleanfile16x16);
DECL_CONST_CHAR(kResImage_desktop16x16);

DECL_CONST_QSTRING(kAskSaveCryptTitle);
DECL_CONST_QSTRING(kAskSaveCryptBody);
DECL_CONST_QSTRING(kPlzInputYourMasterPwd);
DECL_CONST_QSTRING(kAskRetryInputYourMasterPwd);

DECL_CONST_QSTRING(kStringName);
DECL_CONST_QSTRING(kStringDate);
DECL_CONST_QSTRING(kStringSize);
DECL_CONST_QSTRING(kStringExtension);
DECL_CONST_QSTRING(kStringPermission);
DECL_CONST_QSTRING(kStringAttribute);
DECL_CONST_QSTRING(kStringOwner);
DECL_CONST_QSTRING(kStringGroupName);
DECL_CONST_QSTRING(kStringGroupNameNew);
DECL_CONST_QSTRING(kStringGroupNameMod);
DECL_CONST_QSTRING(kStringGroupNameAccess);
DECL_CONST_QSTRING(kStringDeleteHost);
DECL_CONST_QSTRING(kStringDeleteHostMsg);
DECL_CONST_QSTRING(kStringDeleteGroup);
DECL_CONST_QSTRING(kStringDeleteGroupMsg);
DECL_CONST_QSTRING(kStringFileName);
DECL_CONST_QSTRING(kStringFileNameAccess);
DECL_CONST_QSTRING(kStringAlsoSpecifyFolder);
DECL_CONST_QSTRING(kStringFileNameNotTrans);
DECL_CONST_QSTRING(kStringFileNameNotDelete);
DECL_CONST_QSTRING(kStringFileNameAsciiMode);

DECL_CONST_INT(kHelpTopicHostList);
DECL_CONST_INT(kHelpTopicHostSettingGeneral);
DECL_CONST_INT(kHelpTopicHostSettingAdvanced);
DECL_CONST_INT(kHelpTopicHostSettingKanjiCode);
DECL_CONST_INT(kHelpTopicHostSettingDialup);
DECL_CONST_INT(kHelpTopicHostSettingSpecial);
DECL_CONST_INT(kHelpTopicHostSettingEncryption);
DECL_CONST_INT(kHelpTopicHostSettingFeature);
DECL_CONST_INT(kHelpTopicOptionUser);
DECL_CONST_INT(kHelpTopicOptionTransfer1);
DECL_CONST_INT(kHelpTopicOptionTransfer2);
DECL_CONST_INT(kHelpTopicOptionTransfer3);
DECL_CONST_INT(kHelpTopicOptionTransfer4);
DECL_CONST_INT(kHelpTopicOptionMirroring);
DECL_CONST_INT(kHelpTopicOptionOperation);
DECL_CONST_INT(kHelpTopicOptionView1);
DECL_CONST_INT(kHelpTopicOptionView2);
DECL_CONST_INT(kHelpTopicOptionConnecting);
DECL_CONST_INT(kHelpTopicOptionFirewall);
DECL_CONST_INT(kHelpTopicOptionTool);
DECL_CONST_INT(kHelpTopicOptionOther);
DECL_CONST_INT(kHelpTopicAttrSetting);
