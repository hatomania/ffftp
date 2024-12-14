#include "optiontransfer3form.hpp"

#include <QStandardItemModel>

#include "ui_optiontransfer3form.h"

#include "stdafx.h"
#include "ui/uicommon.h"
#include "ui/common/fileandattributesettingdialog.hpp"

namespace {
using ThisData = OptionTransfer3Form::Data;
inline const ThisData& castData(const BaseForm::Data& data) {
  return static_cast<const ThisData&>(data);
}
inline ThisData& castData(BaseForm::Data& data) {
  return static_cast<ThisData&>(data);
}
}  // namespace

class OptionTransfer3Form::Private {
 public:
  Private();
  ~Private();
  Ui::OptionTransfer3Form ui;
  QStandardItemModel* model_extlist;
};
OptionTransfer3Form::Private::Private() : ui(), model_extlist(nullptr) {}
OptionTransfer3Form::Private::~Private() {}

OptionTransfer3Form::Data::Data()
    : attr_list(),
      use_folder_attr(false),
      folder_attr(0) {}

OptionTransfer3Form::Data::Data(
  const std::vector<std::pair<std::wstring, int>>& attr_list,
  bool use_folder_attr,
  int folder_attr)
    : attr_list(attr_list),
      use_folder_attr(use_folder_attr),
      folder_attr(folder_attr) {}

OptionTransfer3Form::OptionTransfer3Form(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);
  d_->model_extlist = new QStandardItemModel(parent);
  d_->model_extlist->setHorizontalHeaderLabels({kStringFileName, kStringAttribute});
  d_->ui.treeView_DefAttrList->setModel(d_->model_extlist);
  d_->ui.lineEdit_FolderAttr->setValidator(new QIntValidator(0, 777, this));
  updateEnabled();
}
OptionTransfer3Form::~OptionTransfer3Form() { delete d_->model_extlist; }

int OptionTransfer3Form::helpID() const { return kHelpTopicOptionTransfer3; }

void OptionTransfer3Form::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void OptionTransfer3Form::updateUi(const BaseForm::Data& data) {
  const ThisData& data_in = castData(data);
  for (const auto& [fname, attr] : data_in.attr_list) {
    addFileAttr(QString(fname), attr);
  }
  UI_SETCHECKED(d_->ui.groupBox_UseFolderAttr, data_in.use_folder_attr);
  UI_SETTEXT(d_->ui.lineEdit_FolderAttr, QString::number(data_in.folder_attr));
}

void OptionTransfer3Form::updateData(BaseForm::Data& data) const {
  ThisData& data_out = castData(data);
  int rc = d_->model_extlist->rowCount();
  data_out.attr_list.clear();
  data_out.attr_list.reserve(rc);
  for (int i = 0; i < rc; ++i) {
    data_out.attr_list.push_back(std::make_pair(
        d_->model_extlist->index(i, 0).data().toString().toStdWString(),
        d_->model_extlist->index(i, 1).data().toInt()));
  }
  UI_ISCHECKED(data_out.use_folder_attr, d_->ui.groupBox_UseFolderAttr);
  UI_TEXT(data_out.folder_attr, d_->ui.lineEdit_FolderAttr).toInt();
}

void OptionTransfer3Form::onClick_pushButton_AddAttr() {
  FileAndAttributeSettingDialog dialog{this};
  if (dialog.exec() == QDialog::Accepted) {
    QString fname{};
    int attr{0};
    dialog.fileAndAttribute(fname, attr);
    addFileAttr(fname, attr);
  }
}
void OptionTransfer3Form::onClick_pushButton_DelAttr() {
  d_->model_extlist->removeRow(d_->ui.treeView_DefAttrList->currentIndex().row());
  updateEnabled();
}
void OptionTransfer3Form::onClick_treeView_DefAttrList() { updateEnabled(); }

void OptionTransfer3Form::updateEnabled() {
  UI_SETENABLED(d_->ui.pushButton_DelAttr, d_->ui.treeView_DefAttrList->currentIndex().isValid());
}
bool OptionTransfer3Form::askFileAttr(QString& fname, int& attr) {
  return false;
}

void OptionTransfer3Form::addFileAttr(const QString& fname, int attr) {
  QStandardItem* item1 = new QStandardItem(fname);
  QStandardItem* item2 = new QStandardItem(QString::number(attr));
  item1->setData(fname);
  item2->setData(attr);
  d_->model_extlist->appendRow({item1, item2});
}
