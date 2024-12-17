#include "optiontransfer1form.hpp"

#include "ui_optiontransfer1form.h"

#include "stdafx.h"
#include "ui/uicommon.h"

namespace {
using ThisData = OptionTransfer1Form::Data;
inline const ThisData& castData(const BaseForm::Data& data) {
  return static_cast<const ThisData&>(data);
}
inline ThisData& castData(BaseForm::Data& data) {
  return static_cast<ThisData&>(data);
}
}  // namespace

class OptionTransfer1Form::Private {
 public:
  Private();
  ~Private();
  Ui::OptionTransfer1Form ui;
};
OptionTransfer1Form::Private::Private() : ui() {}
OptionTransfer1Form::Private::~Private() {}

OptionTransfer1Form::Data::Data()
    : trans_mode(Modes::kAuto),
      ascii_ext(),
      rm_eof(false),
      save_timestamp(false),
      vax_semicolon(false),
      make_all_dir(false),
      abort_on_list_error(false) {}

OptionTransfer1Form::Data::Data(
    Modes trans_mode,
    const std::vector<std::wstring>& ascii_ext,
    bool rm_eof,
    bool save_timestamp,
    bool vax_semicolon,
    bool make_all_dir,
    bool abort_on_list_error)
    : trans_mode(trans_mode),
      ascii_ext(ascii_ext),
      rm_eof(rm_eof),
      save_timestamp(save_timestamp),
      vax_semicolon(vax_semicolon),
      make_all_dir(make_all_dir),
      abort_on_list_error(abort_on_list_error) {}

OptionTransfer1Form::OptionTransfer1Form(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);
  d_->ui.widget_AsciiExt->setup(kStringFileNameAsciiMode, 'I');
}
OptionTransfer1Form::~OptionTransfer1Form() {}

int OptionTransfer1Form::helpID() const {
  return kHelpTopicOptionTransfer1;
}

void OptionTransfer1Form::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void OptionTransfer1Form::updateUi(const BaseForm::Data& data) {
  const ThisData& data_in = castData(data);
  RadioButtons<Modes> radios{
    { Modes::kAuto,   *d_->ui.radioButton_TransModeAuto  },
    { Modes::kASCII,  *d_->ui.radioButton_TransModeASCII },
    { Modes::kBinary, *d_->ui.radioButton_TransModeBin   },
  };
  radios.setChecked(data_in.trans_mode);
  d_->ui.widget_AsciiExt->setData(data_in.ascii_ext);
  UI_SETCHECKED(d_->ui.checkBox_RmEOF, data_in.rm_eof);
  UI_SETCHECKED(d_->ui.checkBox_SaveTimeStamp, data_in.save_timestamp);
  UI_SETCHECKED(d_->ui.checkBox_VaxSemicolon, data_in.vax_semicolon);
  UI_SETCHECKED(d_->ui.checkBox_MakeAllDir, data_in.make_all_dir);
  UI_SETCHECKED(d_->ui.checkBox_AbortOnListError, data_in.abort_on_list_error);
  updateEnabled();
}

void OptionTransfer1Form::updateData(BaseForm::Data& data) const {
  ThisData& data_out = castData(data);
  const RadioButtons<Modes> radios{
    { Modes::kAuto,   *d_->ui.radioButton_TransModeAuto  },
    { Modes::kASCII,  *d_->ui.radioButton_TransModeASCII },
    { Modes::kBinary, *d_->ui.radioButton_TransModeBin   },
  };
  data_out.trans_mode = radios.checked();
  data_out.ascii_ext = d_->ui.widget_AsciiExt->toVectorStdWString();
  UI_ISCHECKED(data_out.rm_eof, d_->ui.checkBox_RmEOF);
  UI_ISCHECKED(data_out.save_timestamp, d_->ui.checkBox_SaveTimeStamp);
  UI_ISCHECKED(data_out.vax_semicolon, d_->ui.checkBox_VaxSemicolon);
  UI_ISCHECKED(data_out.make_all_dir, d_->ui.checkBox_MakeAllDir);
  UI_ISCHECKED(data_out.abort_on_list_error, d_->ui.checkBox_AbortOnListError);
}

void OptionTransfer1Form::updateEnabled() {
  UI_SETENABLED(d_->ui.widget_AsciiExt, d_->ui.radioButton_TransModeAuto->isChecked());
}

void OptionTransfer1Form::onClick_radioButton_TransModeASCII() { updateEnabled(); }
void OptionTransfer1Form::onClick_radioButton_TransModeBin()   { updateEnabled(); }
void OptionTransfer1Form::onClick_radioButton_TransModeAuto()  { updateEnabled(); }
