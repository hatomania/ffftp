#include "optiontransfer3form.hpp"

#include <QIntValidator>

#include "ui_optiontransfer3form.h"

#include "stdafx.h"
#include "ui/uicommon.h"

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
};
OptionTransfer3Form::Private::Private() : ui() {}
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
  d_->ui.lineEdit_FolderAttr->setValidator(new QIntValidator(0, 777, this));
  d_->ui.widget_DefAttrList->setup(kStringFileAttrUploaded, 'A', {kStringFileName, kStringAttribute});

}
OptionTransfer3Form::~OptionTransfer3Form() {}

int OptionTransfer3Form::helpID() const { return kHelpTopicOptionTransfer3; }

void OptionTransfer3Form::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void OptionTransfer3Form::updateUi(const BaseForm::Data& data) {
  const ThisData& data_in = castData(data);
  for (const auto& [fname, attr] : data_in.attr_list) {
    d_->ui.widget_DefAttrList->addData({fname, std::to_wstring(attr)});
  }
  UI_SETCHECKED(d_->ui.groupBox_UseFolderAttr, data_in.use_folder_attr);
  UI_SETTEXT(d_->ui.lineEdit_FolderAttr, QString::number(data_in.folder_attr));
}

void OptionTransfer3Form::updateData(BaseForm::Data& data) const {
  ThisData& data_out = castData(data);
  const std::vector<std::vector<std::wstring>>& rowdata = d_->ui.widget_DefAttrList->data();
  data_out.attr_list.clear();
  data_out.attr_list.reserve(rowdata.size());
  for (const auto& v : rowdata) {
    assert(v.size() == 2);
    data_out.attr_list.push_back(std::make_pair(v.at(0), std::stoi(v.at(1))));
  }
  UI_ISCHECKED(data_out.use_folder_attr, d_->ui.groupBox_UseFolderAttr);
  UI_TEXT(data_out.folder_attr, d_->ui.lineEdit_FolderAttr).toInt();
}
