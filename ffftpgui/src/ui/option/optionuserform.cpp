#include "optionuserform.hpp"

#include "ui_optionuserform.h"

#include "stdafx.h"
#include "ui/uicommon.h"

namespace {
using ThisData = OptionUserForm::Data;
inline const ThisData& castData(const BaseForm::Data& data) {
  return static_cast<const ThisData&>(data);
}
inline ThisData& castData(BaseForm::Data& data) {
  return static_cast<ThisData&>(data);
}
}  // namespace

class OptionUserForm::Private {
 public:
  Private();
  ~Private();
  Ui::OptionUserForm ui;
};
OptionUserForm::Private::Private() : ui() {}
OptionUserForm::Private::~Private() {}

OptionUserForm::Data::Data() : user_mail_adrs() {}
OptionUserForm::Data::Data(const std::wstring& user_mail_adrs)
    : user_mail_adrs(user_mail_adrs) {}

OptionUserForm::OptionUserForm(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);
}
OptionUserForm::~OptionUserForm() {}

void OptionUserForm::firstFocus() const {
  d_->ui.lineEdit_UserMailAdrs->setFocus();
  d_->ui.lineEdit_UserMailAdrs->selectAll();
}

int OptionUserForm::helpID() const {
  return kHelpTopicOptionUser;
}

void OptionUserForm::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void OptionUserForm::updateUi(const BaseForm::Data& data) {
  const ThisData& data_in = castData(data);
  UI_SETTEXT(d_->ui.lineEdit_UserMailAdrs, QString(data_in.user_mail_adrs));
}

void OptionUserForm::updateData(BaseForm::Data& data) const {
  ThisData& data_out = castData(data);
  UI_TEXT(data_out.user_mail_adrs, d_->ui.lineEdit_UserMailAdrs).toStdWString();
}
