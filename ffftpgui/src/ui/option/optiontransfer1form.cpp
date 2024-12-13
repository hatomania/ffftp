#include "optiontransfer1form.hpp"

#include <QInputDialog>
#include <QStandardItemModel>

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
  QStandardItemModel* model_extlist;
};
OptionTransfer1Form::Private::Private() : ui(), model_extlist(nullptr) {}
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
  d_->model_extlist = new QStandardItemModel(parent);
  d_->ui.listView_AsciiExt->setModel(d_->model_extlist);
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
  std::map<Modes, QRadioButton&> radios{
    { Modes::kAuto,   *d_->ui.radioButton_TransModeAuto },
    { Modes::kASCII,  *d_->ui.radioButton_TransModeASCII },
    { Modes::kBinary, *d_->ui.radioButton_TransModeBin },
  };
  radios.at(data_in.trans_mode).setChecked(true);
  d_->model_extlist->clear();
  for (const auto& str : data_in.ascii_ext) {
    addFileName(QString(str));
    // ラムダ式の場合
    //d_->model_extlist->appendRow([](const std::wstring& str) {
    //  QStandardItem* item = new QStandardItem(QString(str));
    //  item->setData(QString(str), kUserRole);
    //  return item;
    //}(str));
  }
  UI_SETCHECKED(d_->ui.checkBox_RmEOF, data_in.rm_eof);
  UI_SETCHECKED(d_->ui.checkBox_SaveTimeStamp, data_in.save_timestamp);
  UI_SETCHECKED(d_->ui.checkBox_VaxSemicolon, data_in.vax_semicolon);
  UI_SETCHECKED(d_->ui.checkBox_MakeAllDir, data_in.make_all_dir);
  UI_SETCHECKED(d_->ui.checkBox_AbortOnListError, data_in.abort_on_list_error);
  updateEnabled();
}

void OptionTransfer1Form::updateData(BaseForm::Data& data) const {
  ThisData& data_out = castData(data);
  std::map<Modes, QRadioButton&> radios{
    { Modes::kAuto,   *d_->ui.radioButton_TransModeAuto },
    { Modes::kASCII,  *d_->ui.radioButton_TransModeASCII },
    { Modes::kBinary, *d_->ui.radioButton_TransModeBin },
  };
  for (auto& [k, v]:radios) {
    if (v.isChecked()) {
      data_out.trans_mode = k;
      break;
    }
  }
  int rc = d_->model_extlist->rowCount();
  data_out.ascii_ext.clear();
  data_out.ascii_ext.reserve(rc);
  for (int i = 0; i < rc; ++i) {
    data_out.ascii_ext.push_back(
      d_->model_extlist->index(i, 0).data().toString().toStdWString());
  }
  UI_ISCHECKED(data_out.rm_eof, d_->ui.checkBox_RmEOF);
  UI_ISCHECKED(data_out.save_timestamp, d_->ui.checkBox_SaveTimeStamp);
  UI_ISCHECKED(data_out.vax_semicolon, d_->ui.checkBox_VaxSemicolon);
  UI_ISCHECKED(data_out.make_all_dir, d_->ui.checkBox_MakeAllDir);
  UI_ISCHECKED(data_out.abort_on_list_error, d_->ui.checkBox_AbortOnListError);
}

void OptionTransfer1Form::updateEnabled() {
  bool isdel = d_->ui.listView_AsciiExt->currentIndex().isValid();
  if (d_->ui.radioButton_TransModeAuto->isChecked()) {
    UI_SETENABLED(d_->ui.listView_AsciiExt, true);
    UI_SETENABLED(d_->ui.pushButton_AddExt, true);
    UI_SETENABLED(d_->ui.pushButton_DelExt, true & isdel);
  } else {
    UI_SETENABLED(d_->ui.listView_AsciiExt, false);
    UI_SETENABLED(d_->ui.pushButton_AddExt, false);
    UI_SETENABLED(d_->ui.pushButton_DelExt, false & isdel);
  }
}

void OptionTransfer1Form::onClick_radioButton_TransModeASCII() { updateEnabled(); }
void OptionTransfer1Form::onClick_radioButton_TransModeBin()   { updateEnabled(); }
void OptionTransfer1Form::onClick_radioButton_TransModeAuto()  { updateEnabled(); }
void OptionTransfer1Form::onClick_listView_AsciiExt()          { updateEnabled(); }

void OptionTransfer1Form::onClick_pushButton_AddExt() {
  if (QString fname{}; askFileName(fname)) {
    addFileName(fname);
    d_->ui.listView_AsciiExt->setCurrentIndex(
        d_->model_extlist->index(d_->model_extlist->rowCount() - 1, 0));
    updateEnabled();
  }
}
void OptionTransfer1Form::onClick_pushButton_DelExt() {
  d_->model_extlist->removeRow(d_->ui.listView_AsciiExt->currentIndex().row());
  updateEnabled();
}

bool OptionTransfer1Form::askFileName(QString& fname) {
  bool ok = false;
  fname = QInputDialog::getText(
    this, kStringFileName, kStringFileNameAccess,
    QLineEdit::Normal, kEmptyString, &ok);
  return ok;
}

void OptionTransfer1Form::addFileName(const QString& fname) {
  QStandardItem* item = new QStandardItem(fname);
  item->setData(fname);
  d_->model_extlist->appendRow(item);
}
