#include "hostquickdialog.hpp"

#include "ui_hostquickdialog.h"

#include "ffftp.h"
#include "stdafx.h"
#include "ui/uicommon.h"

class HostQuickDialog::Private {
 public:
  Private();
  ~Private();
  Ui::HostQuickDialog ui;
};
HostQuickDialog::Private::Private() : ui{} {}
HostQuickDialog::Private::~Private() {}

HostQuickDialog::Data::Data()
    : history{},
      hostname{},
      username{},
      password{},
      use_firewall{false},
      use_passive{false} {}

HostQuickDialog::Data::Data(
    const QStringList& history,
    const QString username,
    const QString password,
    bool use_firewall,
    bool use_passive)
    : history{history},
      hostname{},
      username{username},
      password{password},
      use_firewall{use_firewall},
      use_passive{use_passive} {}

HostQuickDialog::HostQuickDialog(const Data& data, QWidget* parent)
    : QDialog(parent), d_(new Private()) {
  d_->ui.setupUi(this);
  d_->ui.comboBox_Host->lineEdit()->setMaxLength(1024);
  for (const auto& str : data.history) {
    UI_ADDITEM(d_->ui.comboBox_Host, str);
  }
  UI_SETTEXT(d_->ui.comboBox_Host->lineEdit(), kEmptyString);
  UI_SETTEXT(d_->ui.lineEdit_Username, data.username);
  UI_SETTEXT(d_->ui.lineEdit_Password, data.password);
  UI_SETCHECKED(d_->ui.checkBox_Firewall, data.use_firewall);
  UI_SETCHECKED(d_->ui.checkBox_PASV, data.use_passive);
}
HostQuickDialog::~HostQuickDialog() {}

const HostQuickDialog::Data& HostQuickDialog::data() const {
  static Data data{};
  UI_TEXT(data.hostname, d_->ui.comboBox_Host->lineEdit());
  UI_TEXT(data.username, d_->ui.lineEdit_Username);
  UI_TEXT(data.password, d_->ui.lineEdit_Password);
  UI_ISCHECKED(data.use_firewall, d_->ui.checkBox_Firewall);
  UI_ISCHECKED(data.use_passive, d_->ui.checkBox_PASV);
  return data;
}
