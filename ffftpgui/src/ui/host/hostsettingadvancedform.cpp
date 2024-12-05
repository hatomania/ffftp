#include "hostsettingadvancedform.hpp"

#include "ui/uicommon.h"
#include "ui_hostsettingadvancedform.h"

namespace {
constexpr int kDefPort = 21;
inline const HostSettingAdvancedForm::Data& castData(
    const BaseForm::Data& data) {
  return static_cast<const HostSettingAdvancedForm::Data&>(data);
}
inline HostSettingAdvancedForm::Data& castData(BaseForm::Data& data) {
  return static_cast<HostSettingAdvancedForm::Data&>(data);
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
HostSettingAdvancedForm ::~HostSettingAdvancedForm() {}

void HostSettingAdvancedForm::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void HostSettingAdvancedForm::updateUi(const BaseForm::Data& data) {
  const HostSettingAdvancedForm::Data& data_ = castData(data);
  UI_SETCHECKED(d_->ui.checkBox_Firewall, data_.firewall);
  UI_SETCHECKED(d_->ui.checkBox_Pasv, data_.pasv);
  UI_SETCHECKED(d_->ui.checkBox_SyncMove, data_.syncmove);
  UI_SETTEXT(d_->ui.lineEdit_Port, QString::number(data_.port));
  UI_SETTEXT(d_->ui.lineEdit_Account, QString(data_.account));
  UI_SETCURRENTINDEX(d_->ui.comboBox_Timezone, data_.timezone);
  UI_SETCURRENTINDEX(d_->ui.comboBox_Security, data_.security);
  UI_SETPLAINTEXT(d_->ui.plainTextEdit_InitCmd, QString(data_.initcmd));
}

void HostSettingAdvancedForm::updateData(BaseForm::Data& data) const {
  HostSettingAdvancedForm::Data& data_ = castData(data);
  UI_ISCHECKED(data_.firewall, d_->ui.checkBox_Firewall);
  UI_ISCHECKED(data_.pasv, d_->ui.checkBox_Pasv);
  UI_ISCHECKED(data_.syncmove, d_->ui.checkBox_SyncMove);
  UI_TEXT(data_.port, d_->ui.lineEdit_Port).toInt();
  UI_TEXT(data_.account, d_->ui.lineEdit_Account).toStdWString();
  UI_CURRENTINDEX(data_.timezone, d_->ui.comboBox_Timezone);
  UI_CURRENTINDEX(data_.security, d_->ui.comboBox_Security);
  UI_TOPLAINTEXT(data_.initcmd, d_->ui.plainTextEdit_InitCmd).toStdWString();
}

void HostSettingAdvancedForm::onClick_pushButton_StdPort() {
  UI_SETTEXT(d_->ui.lineEdit_Port, QString::number(kDefPort));
}
