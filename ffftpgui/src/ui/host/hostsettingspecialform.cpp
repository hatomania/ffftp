#include "hostsettingspecialform.hpp"

#include "ui_hostsettingspecialform.h"

#include "stdafx.h"
#include "ui/uicommon.h"

namespace {
constexpr const wchar_t* const kDefChmodCmd = L"SITE CHMOD";
constexpr const wchar_t* const kDefLsName = L"-alL";
using ThisData = HostSettingSpecialForm::Data;
inline const ThisData& castData(const BaseForm::Data& data) {
  return static_cast<const ThisData&>(data);
}
inline ThisData& castData(BaseForm::Data& data) {
  return static_cast<ThisData&>(data);
}
}  // namespace

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class HostSettingSpecialForm::Private {
 public:
  Private();
  ~Private();
  Ui::HostSettingSpecialForm ui;
};
HostSettingSpecialForm::Private::Private() {}
HostSettingSpecialForm::Private::~Private() {}

HostSettingSpecialForm::Data::Data()
    : list_cmd_only(false),
      use_mlsd(false),
      use_nlst_r(false),
      no_fullpath(false),
      chmod_cmd(),
      host_type(0),
      ls_name() {}

HostSettingSpecialForm::Data::Data(bool list_cmd_only, bool use_mlsd,
                                   bool use_nlst_r, bool no_fullpath,
                                   const std::wstring& chmod_cmd, int host_type,
                                   const std::wstring& ls_name)
    : list_cmd_only(list_cmd_only),
      use_mlsd(use_mlsd),
      use_nlst_r(use_nlst_r),
      no_fullpath(no_fullpath),
      chmod_cmd(chmod_cmd),
      host_type(host_type),
      ls_name(ls_name) {}

HostSettingSpecialForm::HostSettingSpecialForm(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);
}
HostSettingSpecialForm::~HostSettingSpecialForm() {}

int HostSettingSpecialForm::helpID() const {
  return kHelpTopicHostSettingSpecial;
}

void HostSettingSpecialForm::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void HostSettingSpecialForm::updateUi(const BaseForm::Data& data) {
  const ThisData& data_in = castData(data);
  UI_SETCHECKED(d_->ui.checkBox_ListCmdOnly, data_in.list_cmd_only);
  UI_SETCHECKED(d_->ui.checkBox_UseMLSD, data_in.use_mlsd);
  UI_SETCHECKED(d_->ui.checkBox_UseNLST_R, data_in.use_nlst_r);
  UI_SETCHECKED(d_->ui.checkBox_NoFullPath, data_in.no_fullpath);
  UI_SETTEXT(d_->ui.lineEdit_ChmodCmd, QString(data_in.chmod_cmd));
  UI_SETCURRENTINDEX(d_->ui.comboBox_HostType, data_in.host_type);
  UI_SETTEXT(d_->ui.lineEdit_LsName, QString(data_in.ls_name));
  updateEnabled();
}

void HostSettingSpecialForm::updateData(BaseForm::Data& data) const {
  ThisData& data_out = castData(data);
  UI_ISCHECKED(data_out.list_cmd_only, d_->ui.checkBox_ListCmdOnly);
  UI_ISCHECKED(data_out.use_mlsd, d_->ui.checkBox_UseMLSD);
  UI_ISCHECKED(data_out.use_nlst_r, d_->ui.checkBox_UseNLST_R);
  UI_ISCHECKED(data_out.no_fullpath, d_->ui.checkBox_NoFullPath);
  UI_TEXT(data_out.chmod_cmd, d_->ui.lineEdit_ChmodCmd).toStdWString();
  UI_CURRENTINDEX(data_out.host_type, d_->ui.comboBox_HostType);
  UI_TEXT(data_out.ls_name, d_->ui.lineEdit_LsName).toStdWString();
}

void HostSettingSpecialForm::updateEnabled() const {
  UI_ISCHECKED(bool ischecked_ListCmdOnly, d_->ui.checkBox_ListCmdOnly);
  bool enabled_ListCmdOnly = true;
  bool enabled_UseMLSD = true;
  bool enabled_UseNLST_R = true;
  bool enabled_NoFullPath = true;
  if (ischecked_ListCmdOnly) {
    enabled_UseNLST_R = false;
  } else {
    enabled_UseMLSD = false;
  }
  UI_CURRENTINDEX(int index_HostType, d_->ui.comboBox_HostType);
  if (index_HostType == 2) {  // "VAX VMS"選択時
    enabled_ListCmdOnly = enabled_UseNLST_R = enabled_UseNLST_R = false;
  } else if (index_HostType == 8) {  // "NonStop Server"選択時
    ischecked_ListCmdOnly = true;
    enabled_ListCmdOnly = enabled_UseNLST_R = enabled_UseNLST_R = false;
  } else {
    enabled_ListCmdOnly = true;
    enabled_UseNLST_R = !ischecked_ListCmdOnly;
    enabled_NoFullPath = true;
  }
  UI_SETCHECKED(d_->ui.checkBox_ListCmdOnly, ischecked_ListCmdOnly);
  UI_SETENABLED(d_->ui.checkBox_ListCmdOnly, enabled_ListCmdOnly);
  UI_SETENABLED(d_->ui.checkBox_UseMLSD, enabled_UseMLSD);
  UI_SETENABLED(d_->ui.checkBox_UseNLST_R, enabled_UseNLST_R);
  UI_SETENABLED(d_->ui.checkBox_NoFullPath, enabled_NoFullPath);
}

// [標準]ボタン（属性変更コマンド）をクリックしたときの処理
void HostSettingSpecialForm::onClick_pushButton_StdChmodCmd() {
  UI_SETTEXT(d_->ui.lineEdit_ChmodCmd, QString(kDefChmodCmd));
}
// [標準]ボタン（NLSTファイル名/オプション）をクリックしたときの処理
void HostSettingSpecialForm::onClick_pushButton_StdLsName() {
  UI_SETTEXT(d_->ui.lineEdit_LsName, QString(kDefLsName));
}

// [LISTコマンドでファイル一覧を取得]チェックボックスをクリックしたときの処理
void HostSettingSpecialForm::onClick_checkBox_ListCmdOnly() { updateEnabled(); }

// [ホストの種類]コンボボックスのリストを選択したときの処理
void HostSettingSpecialForm::onCurrentIndexChanged_comboBox_HostType(int) {
  updateEnabled();
}
