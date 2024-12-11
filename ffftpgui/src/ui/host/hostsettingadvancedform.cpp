#include "hostsettingadvancedform.hpp"

#include "ui_hostsettingadvancedform.h"

#include "stdafx.h"
#include "ui/uicommon.h"

namespace {
constexpr int kDefPort = 21;
using ThisData = HostSettingAdvancedForm::Data;
inline const ThisData& castData(const BaseForm::Data& data) {
  return static_cast<const ThisData&>(data);
}
inline ThisData& castData(BaseForm::Data& data) {
  return static_cast<ThisData&>(data);
}
}  // namespace

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class HostSettingAdvancedForm::Private {
 public:
  Private();
  ~Private();
  Ui::HostSettingAdvancedForm ui;
};
HostSettingAdvancedForm::Private::Private() {}
HostSettingAdvancedForm::Private::~Private() {}

HostSettingAdvancedForm::Data::Data()
    : firewall(false),
      pasv(false),
      syncmove(false),
      port(0),
      account(),
      timezone(0),
      security(0),
      initcmd() {}

HostSettingAdvancedForm::Data::Data(bool firewall, bool pasv, bool syncmove,
                                    int port, const std::wstring& account,
                                    int timezone, int security,
                                    const std::wstring& initcmd)
    : firewall(firewall),
      pasv(pasv),
      syncmove(syncmove),
      port(port),
      account(account),
      timezone(timezone),
      security(security),
      initcmd(initcmd) {}

HostSettingAdvancedForm::HostSettingAdvancedForm(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);
  d_->ui.lineEdit_Port->setValidator(new QIntValidator(0, 0xFFFF, this));
}
HostSettingAdvancedForm::~HostSettingAdvancedForm() {}

int HostSettingAdvancedForm::helpID() const {
  return kHelpTopicHostSettingAdvanced;
}

void HostSettingAdvancedForm::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void HostSettingAdvancedForm::updateUi(const BaseForm::Data& data) {
  const ThisData& data_in = castData(data);
  UI_SETCHECKED(d_->ui.checkBox_Firewall, data_in.firewall);
  UI_SETCHECKED(d_->ui.checkBox_Pasv, data_in.pasv);
  UI_SETCHECKED(d_->ui.checkBox_SyncMove, data_in.syncmove);
  UI_SETTEXT(d_->ui.lineEdit_Port, QString::number(data_in.port));
  UI_SETTEXT(d_->ui.lineEdit_Account, QString(data_in.account));
  UI_SETCURRENTINDEX(d_->ui.comboBox_Timezone, data_in.timezone);
  UI_SETCURRENTINDEX(d_->ui.comboBox_Security, data_in.security);
  UI_SETPLAINTEXT(d_->ui.plainTextEdit_InitCmd, QString(data_in.initcmd));
}

void HostSettingAdvancedForm::updateData(BaseForm::Data& data) const {
  ThisData& data_out = castData(data);
  UI_ISCHECKED(data_out.firewall, d_->ui.checkBox_Firewall);
  UI_ISCHECKED(data_out.pasv, d_->ui.checkBox_Pasv);
  UI_ISCHECKED(data_out.syncmove, d_->ui.checkBox_SyncMove);
  UI_TEXT(data_out.port, d_->ui.lineEdit_Port).toInt();
  UI_TEXT(data_out.account, d_->ui.lineEdit_Account).toStdWString();
  UI_CURRENTINDEX(data_out.timezone, d_->ui.comboBox_Timezone);
  UI_CURRENTINDEX(data_out.security, d_->ui.comboBox_Security);
  UI_TOPLAINTEXT(data_out.initcmd, d_->ui.plainTextEdit_InitCmd).toStdWString();
}

void HostSettingAdvancedForm::onClick_pushButton_StdPort() {
  UI_SETTEXT(d_->ui.lineEdit_Port, QString::number(kDefPort));
}
