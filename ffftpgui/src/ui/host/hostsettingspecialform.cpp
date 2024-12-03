#include "hostsettingspecialform.hpp"

#include "stdafx.h"
#include "ui_hostsettingspecialform.h"

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class HostSettingSpecialForm::Private {
 public:
  Private() {}
  ~Private() {}
  Ui::HostSettingSpecialForm ui;
};

HostSettingSpecialForm::Data::Data()
    : max_connection(1),
      reuse_main_socket(true),
      ignore_PASV_addr(false),
      keep_connection_freq(60),
      proc_when_error(0),
      reconnect_after_error(true) {}

HostSettingSpecialForm::HostSettingSpecialForm(QWidget* parent)
    : QWidget(parent), d_(new HostSettingSpecialForm::Private()) {
  d_->ui.setupUi(this);
  setDataAsDefault();
}

void HostSettingSpecialForm::setData(const Data& data) const {
  d_->ui.spinBox_MaxConnection->setValue(data.max_connection);
  d_->ui.checkBox_ReuseMainSocket->setChecked(data.reuse_main_socket);
  d_->ui.checkBox_IgnorePASVAddr->setChecked(data.ignore_PASV_addr);
  d_->ui.spinBox_KeepConnectionFreq->setValue(data.keep_connection_freq);
  d_->ui.comboBox_ProcWhenError->setCurrentIndex(data.proc_when_error);
  d_->ui.checkBox_ReconnectAfterError->setChecked(data.reconnect_after_error);
}

const HostSettingSpecialForm::Data& HostSettingSpecialForm::getData() const {
  static Data data;
  data.max_connection = d_->ui.spinBox_MaxConnection->value();
  data.reuse_main_socket = d_->ui.checkBox_ReuseMainSocket->isChecked();
  data.ignore_PASV_addr = d_->ui.checkBox_IgnorePASVAddr->isChecked();
  data.keep_connection_freq = d_->ui.spinBox_KeepConnectionFreq->value();
  data.proc_when_error = d_->ui.comboBox_ProcWhenError->currentIndex();
  data.reconnect_after_error = d_->ui.checkBox_ReconnectAfterError->isChecked();
  return data;
}

void HostSettingSpecialForm::setDataAsDefault() const { this->setData(Data()); }
