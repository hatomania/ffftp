#include "optionmirroringform.hpp"

#include "ui_optionmirroringform.h"

#include "stdafx.h"
#include "ui/uicommon.h"

namespace {
using ThisData = OptionMirroringForm::Data;
inline const ThisData& castData(const BaseForm::Data& data) {
  return static_cast<const ThisData&>(data);
}
inline ThisData& castData(BaseForm::Data& data) {
  return static_cast<ThisData&>(data);
}
}  // namespace

class OptionMirroringForm::Private {
 public:
  Private();
  ~Private();
  Ui::OptionMirroringForm ui;
};
OptionMirroringForm::Private::Private() : ui() {}
OptionMirroringForm::Private::~Private() {}

OptionMirroringForm::Data::Data()
    : no_trn{},
      no_del{},
      fname_cnv{false},
      up_del_notify{false},
      down_del_notify{false},
      no_transfer_contents{false} {}

OptionMirroringForm::Data::Data(
  const std::vector<std::wstring>& no_trn,
  const std::vector<std::wstring>& no_del,
  bool fname_cnv,
  bool up_del_notify,
  bool down_del_notify,
  bool no_transfer_contents)
    : no_trn{no_trn},
      no_del{no_del},
      fname_cnv{fname_cnv},
      up_del_notify{up_del_notify},
      down_del_notify{down_del_notify},
      no_transfer_contents{no_transfer_contents} {}

OptionMirroringForm::OptionMirroringForm(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);
  d_->ui.widget_NoTrn->init(kStringFileNameNotTrans,  'I', kStringAlsoSpecifyFolder);
  d_->ui.widget_NoDel->init(kStringFileNameNotDelete, 'A', kStringAlsoSpecifyFolder);
}
OptionMirroringForm::~OptionMirroringForm() {}

int OptionMirroringForm::helpID() const {
  return kHelpTopicOptionMirroring;
}

void OptionMirroringForm::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void OptionMirroringForm::updateUi(const BaseForm::Data& data) {
  const ThisData& data_in = castData(data);
  d_->ui.widget_NoTrn->setData(data_in.no_trn);
  d_->ui.widget_NoDel->setData(data_in.no_del);
  UI_SETCHECKED(d_->ui.checkBox_FnameCnv, data_in.fname_cnv);
  UI_SETCHECKED(d_->ui.checkBox_UpDelNotify, data_in.up_del_notify);
  UI_SETCHECKED(d_->ui.checkBox_DownDelNotify, data_in.down_del_notify);
  UI_SETCHECKED(d_->ui.checkBox_NoTransferContents, data_in.no_transfer_contents);
}

void OptionMirroringForm::updateData(BaseForm::Data& data) const {
  ThisData& data_out = castData(data);
  data_out.no_trn = d_->ui.widget_NoTrn->toVectorStdWString();
  data_out.no_del = d_->ui.widget_NoDel->toVectorStdWString();
  UI_ISCHECKED(data_out.fname_cnv, d_->ui.checkBox_FnameCnv);
  UI_ISCHECKED(data_out.up_del_notify, d_->ui.checkBox_UpDelNotify);
  UI_ISCHECKED(data_out.down_del_notify, d_->ui.checkBox_DownDelNotify);
  UI_ISCHECKED(data_out.no_transfer_contents, d_->ui.checkBox_NoTransferContents);
}
