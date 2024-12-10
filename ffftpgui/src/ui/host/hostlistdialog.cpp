#include "hostlistdialog.hpp"

#include <QStandardItem>
#include <QStandardItemModel>

#include "ffftp.h"
#include "hostsettingsdialog.hpp"
#include "stdafx.h"
#include "ui_hostlistdialog.h"

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class HostListDialog::Private {
 public:
  Private();
  ~Private();
  Ui::HostListDialogClass ui;
  hostcontext_t selected_hc;
};
HostListDialog::Private::Private() : ui(), selected_hc(nullptr) {}
HostListDialog::Private::~Private() {}

HostListDialog::HostListDialog(QWidget* parent)
    : QDialog(parent), d_(new Private()) {
  d_->ui.setupUi(this);
}
HostListDialog::~HostListDialog() {}

const hostcontext_t HostListDialog::hostcontext() const {
  return d_->selected_hc;
}

void HostListDialog::accept() {
  d_->selected_hc = d_->ui.treeView_HostList->currentHostContext();
  QDialog::accept();
}

void HostListDialog::onClick_pushButton_NewHost() {
  hostcontext_t hc = d_->ui.treeView_HostList->currentHostContext();
  if (hc) {
    hostdata hdata;
    ffftp_hostdata_initialize(&hdata);
    ffftp_hostcontext_hostdata_default(&hdata);
    if (showSettingDialog(hdata)) {
      hostcontext_t new_hc = ffftp_hostcontext_new(hc, &hdata);
      d_->ui.treeView_HostList->update();
      d_->ui.treeView_HostList->setCurrentIndex(new_hc);
    }
    ffftp_hostdata_finalize(&hdata);
  }
}

void HostListDialog::onClick_pushButton_NewGroup() {
  qDebug() << __FUNCTION__ << "called!";
}

void HostListDialog::onClick_pushButton_Mod() {
  hostcontext_t hc = d_->ui.treeView_HostList->currentHostContext();
  if (hc) {
    hostdata hdata;
    ffftp_hostdata_initialize(&hdata);
    ffftp_hostcontext_hostdata(hc, &hdata);
    if (showSettingDialog(hdata)) {
      // TODO: newのまま
      hostcontext_t new_hc = ffftp_hostcontext_new(hc, &hdata);
      d_->ui.treeView_HostList->update();
      d_->ui.treeView_HostList->setCurrentIndex(new_hc);
    }
    ffftp_hostdata_finalize(&hdata);
  }
}

void HostListDialog::onClick_pushButton_Copy() {
  qDebug() << __FUNCTION__ << "called!";
}

void HostListDialog::onClick_pushButton_Del() {
  qDebug() << __FUNCTION__ << "called!";
}

void HostListDialog::onClick_pushButton_Up() {
  hostcontext_t hc = d_->ui.treeView_HostList->currentHostContext();
  if (hc) {
    ffftp_hostcontext_up(hc);
    d_->ui.treeView_HostList->update();
    d_->ui.treeView_HostList->setCurrentIndex(hc);
  }
}

void HostListDialog::onClick_pushButton_Down() {
  hostcontext_t hc = d_->ui.treeView_HostList->currentHostContext();
  if (hc) {
    ffftp_hostcontext_down(hc);
    d_->ui.treeView_HostList->update();
    d_->ui.treeView_HostList->setCurrentIndex(hc);
  }
}

void HostListDialog::onClick_pushButton_Default() {
  qDebug() << __FUNCTION__ << "called!";
}

void HostListDialog::onClick_pushButton_Help() {
  qDebug() << __FUNCTION__ << "called!";
}

bool HostListDialog::showSettingDialog(hostdata& in_out_data) /* const */ {
  bool ret = false;
  HostSettingsDialog setting_dlg(
      in_out_data,
      this);  // 関数のおしりにconst付けるとthisもconst型になり型不一致でエラー
  if (setting_dlg.exec() == QDialog::Accepted) {
    setting_dlg.hostData(in_out_data);
    ret = true;
  }
  return ret;
}
