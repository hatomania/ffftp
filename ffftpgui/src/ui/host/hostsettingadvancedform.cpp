#include "hostsettingadvancedform.hpp"

#include "stdafx.h"
#include "ui_hostsettingadvancedform.h"

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class HostSettingAdvancedForm::Private {
 public:
  Private() {}
  ~Private() = default;
  Ui::HostSettingAdvancedForm ui;
  void enableControls() const;
};

namespace {
constexpr const char* const kDefCHMODCmd = "SITE CHMOD";
constexpr const char* const kDefNLST = "-alL";
}  // namespace

HostSettingAdvancedForm::Data::Data()
    : is_LIST_cmd(true),
      is_MLSD_cmd(true),
      is_NLST_cmd(true),
      not_fullpath(false),
      CHMOD_cmd(QString(kDefCHMODCmd)),
      host(0),
      NLST(QString(kDefNLST)) {}

void HostSettingAdvancedForm::Private::enableControls() const {
  int cidx = ui.comboBox_Host->currentIndex();
  if (cidx == 8) {
    ui.checkBox_LISTCmd->setChecked(true);
  }

  bool checked = ui.checkBox_LISTCmd->isChecked();
  if (checked) {
    ui.checkBox_MLSDCmd->setEnabled(true);
    ui.checkBox_UseNLSTR->setEnabled(false);
  } else {
    ui.checkBox_MLSDCmd->setEnabled(false);
    ui.checkBox_UseNLSTR->setEnabled(true);
  }
  if (cidx == 2 || cidx == 8) {
    ui.checkBox_LISTCmd->setEnabled(false);
    ui.checkBox_UseNLSTR->setEnabled(false);
    ui.checkBox_NotFullpath->setEnabled(false);
  } else {
    ui.checkBox_LISTCmd->setEnabled(true);
    if (!checked) {
      ui.checkBox_UseNLSTR->setEnabled(true);
    }
    ui.checkBox_NotFullpath->setEnabled(true);
  }
}

HostSettingAdvancedForm::HostSettingAdvancedForm(QWidget* parent)
    : QWidget(parent), d_(new HostSettingAdvancedForm::Private()) {
  d_->ui.setupUi(this);
  setDataAsDefault();
}

void HostSettingAdvancedForm::setData(const Data& data) const {
  d_->ui.checkBox_LISTCmd->setChecked(data.is_LIST_cmd);
  d_->ui.checkBox_MLSDCmd->setChecked(data.is_MLSD_cmd);
  d_->ui.checkBox_UseNLSTR->setChecked(data.is_NLST_cmd);
  d_->ui.checkBox_NotFullpath->setChecked(data.not_fullpath);
  d_->ui.lineEdit_CHMODCmd->setText(data.CHMOD_cmd);
  d_->ui.comboBox_Host->setCurrentIndex(data.host);
  d_->ui.lineEdit_NLST->setText(data.NLST);
  d_->enableControls();
}

const HostSettingAdvancedForm::Data& HostSettingAdvancedForm::getData() const {
  static Data data;
  return data;
}

void HostSettingAdvancedForm::setDataAsDefault() const {
  this->setData(Data());
}

void HostSettingAdvancedForm::onClick_pushButton_CHMODCmd() {
  d_->ui.lineEdit_CHMODCmd->setText(QString(kDefCHMODCmd));
}

void HostSettingAdvancedForm::onClick_pushButton_StdNLST() {
  d_->ui.lineEdit_NLST->setText(QString(kDefNLST));
}

void HostSettingAdvancedForm::onClick_checkBox_LISTCmd(bool checked) {
  d_->enableControls();
}

void HostSettingAdvancedForm::onCurrentIndexChanged_comboBox_Host(int index) {
  qDebug() << __FUNCTION__ << "called!";
  d_->enableControls();
}
