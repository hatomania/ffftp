#include "optiontransfer2form.hpp"

#include <QFileDialog>

#include "ui_optiontransfer2form.h"

#include "stdafx.h"
#include "ui/uicommon.h"

namespace {
using ThisData = OptionTransfer2Form::Data;
inline const ThisData& castData(const BaseForm::Data& data) {
  return static_cast<const ThisData&>(data);
}
inline ThisData& castData(BaseForm::Data& data) {
  return static_cast<ThisData&>(data);
}
}  // namespace

class OptionTransfer2Form::Private {
 public:
  Private();
  ~Private();
  Ui::OptionTransfer2Form ui;
};
OptionTransfer2Form::Private::Private() : ui() {}
OptionTransfer2Form::Private::~Private() {}

OptionTransfer2Form::Data::Data()
    : fname_cnv(Modes::kLower), timeout(0), default_local_path() {}

OptionTransfer2Form::Data::Data(
  Modes fname_cnv,
  int timeout,
  const std::wstring& default_local_path)
    : fname_cnv(fname_cnv),
      timeout(timeout),
      default_local_path(default_local_path) {}

OptionTransfer2Form::OptionTransfer2Form(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);
}
OptionTransfer2Form::~OptionTransfer2Form() {}

int OptionTransfer2Form::helpID() const { return kHelpTopicOptionTransfer2; }

void OptionTransfer2Form::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void OptionTransfer2Form::updateUi(const BaseForm::Data& data) {
  const ThisData& data_in = castData(data);
  RadioButtons<Modes> radios_fname{
      {Modes::kLower, *d_->ui.radioButton_FnameCnvLower},
      {Modes::kUpper, *d_->ui.radioButton_FnameCnvUpper},
      {Modes::kNoCnv, *d_->ui.radioButton_FnameCnvNoCnv},
  };
  radios_fname.setChecked(data_in.fname_cnv);
  UI_SETVALUE(d_->ui.spinBox_TimeOut, data_in.timeout);
  UI_SETTEXT(d_->ui.lineEdit_DefaultLocalPath, QString(data_in.default_local_path));
}

void OptionTransfer2Form::updateData(BaseForm::Data& data) const {
  ThisData& data_out = castData(data);
  const RadioButtons<Modes> radios_fname{
      {Modes::kLower, *d_->ui.radioButton_FnameCnvLower},
      {Modes::kUpper, *d_->ui.radioButton_FnameCnvUpper},
      {Modes::kNoCnv, *d_->ui.radioButton_FnameCnvNoCnv},
  };
  data_out.fname_cnv = radios_fname.checked();
  UI_VALUE(data_out.timeout, d_->ui.spinBox_TimeOut);
  UI_TEXT(data_out.default_local_path, d_->ui.lineEdit_DefaultLocalPath).toStdWString();
}

void OptionTransfer2Form::onClick_toolButton_DefaultLocalPath() {
  QString dirpath = QFileDialog::getExistingDirectory(
      this, QString(), d_->ui.lineEdit_DefaultLocalPath->text());
  if (!dirpath.isEmpty()) {
    d_->ui.lineEdit_DefaultLocalPath->setText(dirpath);
  }
}
