#include "optionview1form.hpp"

#include "ui_optionview1form.h"

#include "stdafx.h"
#include "ui/uicommon.h"

namespace {
using ThisData = OptionView1Form::Data;
inline const ThisData& castData(const BaseForm::Data& data) {
  return static_cast<const ThisData&>(data);
}
inline ThisData& castData(BaseForm::Data& data) {
  return static_cast<ThisData&>(data);
}
}  // namespace

class OptionView1Form::Private {
 public:
  Private();
  ~Private();
  Ui::OptionView1Form ui;
};
OptionView1Form::Private::Private() : ui() {}
OptionView1Form::Private::~Private() {}

OptionView1Form::Data::Data()
    : font(-1),
      disp_ignore_hide(false),
      disp_drives(false),
      disp_file_icon(false),
      disp_time_seconds(false) {}

OptionView1Form::Data::Data(
  int font,
  bool disp_ignore_hide,
  bool disp_drives,
  bool disp_file_icon,
  bool disp_time_seconds)
    : font(font),
      disp_ignore_hide(disp_ignore_hide),
      disp_drives(disp_drives),
      disp_file_icon(disp_file_icon),
      disp_time_seconds(disp_time_seconds) {}

OptionView1Form::OptionView1Form(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);
}
OptionView1Form::~OptionView1Form() {}

int OptionView1Form::helpID() const {
  return kHelpTopicOptionView1;
}

void OptionView1Form::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void OptionView1Form::updateUi(const BaseForm::Data& data) {
  const ThisData& data_in = castData(data);
  // TODO: フォント処理
  UI_SETCHECKED(d_->ui.checkBox_DispIgnoreHide, data_in.disp_ignore_hide);
  UI_SETCHECKED(d_->ui.checkBox_DispDrives, data_in.disp_drives);
  UI_SETCHECKED(d_->ui.checkBox_DispFileIcon, data_in.disp_file_icon);
  UI_SETCHECKED(d_->ui.checkBox_DispTimeSeconds, data_in.disp_time_seconds);
}

void OptionView1Form::updateData(BaseForm::Data& data) const {
  ThisData& data_out = castData(data);
  // TODO: フォント処理
  UI_ISCHECKED(data_out.disp_ignore_hide, d_->ui.checkBox_DispIgnoreHide);
  UI_ISCHECKED(data_out.disp_drives, d_->ui.checkBox_DispDrives);
  UI_ISCHECKED(data_out.disp_file_icon, d_->ui.checkBox_DispFileIcon);
  UI_ISCHECKED(data_out.disp_time_seconds, d_->ui.checkBox_DispTimeSeconds);
}

#include <QMessageBox>
void OptionView1Form::onClick_pushButton_ChangeFont() {
  // TODO: フォント処理
  QMessageBox::information(this, "フォントの変更", "現在のバージョンではフォントを変更する機能は実装されていません。");
}
