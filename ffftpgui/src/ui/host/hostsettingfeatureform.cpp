#include "hostsettingfeatureform.hpp"

#include "ui_hostsettingfeatureform.h"

namespace {
constexpr int kDefPort = 21;
}

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class HostSettingFeatureForm::Private {
 public:
  Private() {}
  ~Private() = default;
  Ui::HostSettingFeatureForm ui;
};

HostSettingFeatureForm::Data::Data()
    : use_firewall(false),
      use_pasv_mode(true),
      use_folder_samemove(false),
      port(kDefPort),
      account(""),
      timezone(21),
      security(1),
      cmd_when_connect("") {}

HostSettingFeatureForm::HostSettingFeatureForm(QWidget* parent)
    : QWidget(parent), d_(new HostSettingFeatureForm::Private()) {
  d_->ui.setupUi(this);
  d_->ui.lineEdit_Port->setValidator(new QIntValidator(0, 0xFFFF, this));
  setDataAsDefault();
}

void HostSettingFeatureForm::setData(const Data& data) const {
  d_->ui.checkBox_UseFirewall->setChecked(data.use_firewall);
  d_->ui.checkBox_UserPASVMode->setChecked(data.use_pasv_mode);
  d_->ui.checkBox_UseFolderSameMove->setChecked(data.use_folder_samemove);
  d_->ui.lineEdit_Port->setText(QString::number(data.port));
  d_->ui.lineEdit_Account->setText(data.account);
  d_->ui.comboBox_Timezone->setCurrentIndex(data.timezone);
  d_->ui.comboBox_Security->setCurrentIndex(data.security);
  d_->ui.plainTextEdit_CmdWhenConnect->setPlainText(data.cmd_when_connect);
}

const HostSettingFeatureForm::Data& HostSettingFeatureForm::getData()
    const {
  static Data data;
  data.use_firewall = d_->ui.checkBox_UseFirewall->isChecked();
  data.use_pasv_mode = d_->ui.checkBox_UserPASVMode->isChecked();
  data.use_folder_samemove = d_->ui.checkBox_UseFolderSameMove->isChecked();
  data.port = d_->ui.lineEdit_Port->text().toInt();
  data.account = d_->ui.lineEdit_Account->text();
  data.timezone = d_->ui.comboBox_Timezone->currentIndex();
  data.security = d_->ui.comboBox_Security->currentIndex();
  data.cmd_when_connect = d_->ui.plainTextEdit_CmdWhenConnect->toPlainText();
  return data;
}

void HostSettingFeatureForm::setDataAsDefault() const {
  this->setData(Data());
}

void HostSettingFeatureForm::onClick_pushButton_StdPort() {
  d_->ui.lineEdit_Port->setText(QString::number(kDefPort));
}
