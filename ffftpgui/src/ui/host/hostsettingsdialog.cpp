#include "hostsettingsdialog.hpp"

#include "hostsettingbasicform.hpp"
#include "stdafx.h"
#include "ui_hostsettingsdialog.h"

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class HostSettingsDialog::Private {
 public:
  Private() {}
  ~Private() {}
  Ui::HostSettingsDialog ui;
};

HostSettingsDialog::HostSettingsDialog(QWidget* parent)
    : QDialog(parent), d_(new HostSettingsDialog::Private()) {
  d_->ui.setupUi(this);
}

void HostSettingsDialog::accept() {
  qDebug() << __FUNCTION__ << "called!";
  QDialog::accept();
}

void HostSettingsDialog::help() { qDebug() << __FUNCTION__ << "called!"; }
