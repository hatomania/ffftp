#include "optionotherform.hpp"

#include "ui_optionotherform.h"

#include "ffftp.h"
#include "stdafx.h"
#include "ui/uicommon.h"

namespace {
using ThisData = OptionOtherForm::Data;
inline const ThisData& castData(const BaseForm::Data& data) {
  return static_cast<const ThisData&>(data);
}
inline ThisData& castData(BaseForm::Data& data) {
  return static_cast<ThisData&>(data);
}
}  // namespace

class OptionOtherForm::Private {
 public:
  Private();
  ~Private();
  Ui::OptionOtherForm ui;
};
OptionOtherForm::Private::Private() : ui() {}
OptionOtherForm::Private::~Private() {}

OptionOtherForm::Data::Data()
    : save_win_pos(false),
      reg_type(false),
      encrypt_all_settings(false),
      debug_console(false) {}

OptionOtherForm::Data::Data(
  bool save_win_pos,
  bool reg_type,
  bool encrypt_all_settings,
  bool debug_console)
    : save_win_pos(save_win_pos),
      reg_type(reg_type),
      encrypt_all_settings(encrypt_all_settings),
      debug_console(debug_console) {}

OptionOtherForm::OptionOtherForm(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);
}
OptionOtherForm::~OptionOtherForm() {}

int OptionOtherForm::helpID() const {
  return kHelpTopicOptionOther;
}

void OptionOtherForm::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void OptionOtherForm::updateUi(const BaseForm::Data& data) {
  const ThisData& data_in = castData(data);
  UI_SETCHECKED(d_->ui.checkBox_SaveWinPos, data_in.save_win_pos);
  UI_SETCHECKED(d_->ui.checkBox_RegType, data_in.reg_type);
  UI_SETCHECKED(d_->ui.checkBox_EncryptAllSettings, data_in.encrypt_all_settings);
  UI_SETCHECKED(d_->ui.checkBox_DebugConsole, data_in.debug_console);
}

void OptionOtherForm::updateData(BaseForm::Data& data) const {
  ThisData& data_out = castData(data);
  UI_ISCHECKED(data_out.save_win_pos, d_->ui.checkBox_SaveWinPos);
  UI_ISCHECKED(data_out.reg_type, d_->ui.checkBox_RegType);
  UI_ISCHECKED(data_out.encrypt_all_settings, d_->ui.checkBox_EncryptAllSettings);
  UI_ISCHECKED(data_out.debug_console, d_->ui.checkBox_DebugConsole);
}

void OptionOtherForm::onClick_pushButton_OpenSound() {
  ffftp_showsound();
}
