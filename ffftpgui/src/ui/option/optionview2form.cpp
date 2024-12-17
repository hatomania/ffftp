#include "optionview2form.hpp"

#include "ui_optionview2form.h"

#include "stdafx.h"
#include "ui/uicommon.h"

namespace {
using ThisData = OptionView2Form::Data;
inline const ThisData& castData(const BaseForm::Data& data) {
  return static_cast<const ThisData&>(data);
}
inline ThisData& castData(BaseForm::Data& data) {
  return static_cast<ThisData&>(data);
}
}  // namespace

class OptionView2Form::Private {
 public:
  Private();
  ~Private();
  Ui::OptionView2Form ui;
};
OptionView2Form::Private::Private() : ui() {}
OptionView2Form::Private::~Private() {}

OptionView2Form::Data::Data()
    : disp_permissions_number(false),
      auto_refresh_filelist(false),
      remove_old_log(false) {}

OptionView2Form::Data::Data(
  bool disp_permissions_number,
  bool auto_refresh_filelist,
  bool remove_old_log)
    : disp_permissions_number(disp_permissions_number),
      auto_refresh_filelist(auto_refresh_filelist),
      remove_old_log(remove_old_log) {}

OptionView2Form::OptionView2Form(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);
//  d_->ui.lineEdit_Port->setValidator(new QIntValidator(0, 0xFFFF, this));
}
OptionView2Form::~OptionView2Form() {}

int OptionView2Form::helpID() const {
  return kHelpTopicOptionView2;
}

void OptionView2Form::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void OptionView2Form::updateUi(const BaseForm::Data& data) {
  const ThisData& data_in = castData(data);
  UI_SETCHECKED(d_->ui.checkBox_DispPermissionsNumber, data_in.disp_permissions_number);
  UI_SETCHECKED(d_->ui.checkBox_AutoRefreshFileList, data_in.auto_refresh_filelist);
  UI_SETCHECKED(d_->ui.checkBox_RemoveOldLog, data_in.remove_old_log);
}

void OptionView2Form::updateData(BaseForm::Data& data) const {
  ThisData& data_out = castData(data);
  UI_ISCHECKED(data_out.disp_permissions_number, d_->ui.checkBox_DispPermissionsNumber);
  UI_ISCHECKED(data_out.auto_refresh_filelist, d_->ui.checkBox_AutoRefreshFileList);
  UI_ISCHECKED(data_out.remove_old_log, d_->ui.checkBox_RemoveOldLog);
}
