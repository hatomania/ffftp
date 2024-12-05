﻿#include "hostsettingsdialog.hpp"

#include "ffftp_hostdata.h"
#include "hostsettinggeneralform.hpp"
#include "stdafx.h"
#include "ui_hostsettingsdialog.h"

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class HostSettingsDialog::Private {
 public:
  Private() {}
  ~Private() {}
  Ui::HostSettingsDialog ui;
};

HostSettingsDialog::HostSettingsDialog(const hostdata& hdata, QWidget* parent)
    : QDialog(parent), d_(new HostSettingsDialog::Private()) {
  d_->ui.setupUi(this);
  setHostData(hdata);
}

void HostSettingsDialog::setHostData(const hostdata& hdata) {
  // [基本]タブへデータを入力
  HostSettingGeneralForm::Data data_tab_0{
      hdata.general.host_name,
      hdata.general.host_adrs,
      hdata.general.username,
      hdata.general.password,
      hdata.general.anonymous,
      hdata.general.initdir_local,
      hdata.general.initdir_remote,
      hdata.general.initdir_remote_now,
      hdata.general.enabled_curdir,
      hdata.general.last_dir,
  };
  d_->ui.tab_0->setData(data_tab_0);
}

#define DECL_FORMDATA(T, V)\
  static T::Data data_##V;\
  data_##V = static_cast<const T::Data&>(d_->ui.V->data());

void HostSettingsDialog::hostData(hostdata& hdata) const {
  DECL_FORMDATA(HostSettingGeneralForm, tab_0);

  hdata.general = {
      .host_name = data_tab_0.host_name.c_str(),
      .host_adrs = data_tab_0.host_adrs.c_str(),
      .username = data_tab_0.username.c_str(),
      .password = data_tab_0.password.c_str(),
      .anonymous = data_tab_0.anonymous,
      .initdir_local = data_tab_0.initdir_local.c_str(),
      .initdir_remote = data_tab_0.initdir_remote.c_str(),
      .initdir_remote_now = data_tab_0.initdir_remote_now.c_str(),
      .last_dir = data_tab_0.last_dir,
  };
}

void HostSettingsDialog::accept() {
  qDebug() << __FUNCTION__ << "called!";
  QDialog::accept();
}

void HostSettingsDialog::help() { qDebug() << __FUNCTION__ << "called!"; }
