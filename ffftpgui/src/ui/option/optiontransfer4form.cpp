#include "optiontransfer4form.hpp"

#include "ui_optiontransfer4form.h"

#include "stdafx.h"
#include "ui/uicommon.h"

namespace {
using ThisData = OptionTransfer4Form::Data;
inline const ThisData& castData(const BaseForm::Data& data) {
  return static_cast<const ThisData&>(data);
}
inline ThisData& castData(BaseForm::Data& data) {
  return static_cast<ThisData&>(data);
}
}  // namespace

class OptionTransfer4Form::Private {
 public:
  Private();
  ~Private();
  Ui::OptionTransfer4Form ui;
};
OptionTransfer4Form::Private::Private() : ui() {}
OptionTransfer4Form::Private::~Private() {}

OptionTransfer4Form::Data::Data()
    : local_kanjicode(OptionTransfer4Form::Codes::kSJIS),
      mark_as_internet(false) {}

OptionTransfer4Form::Data::Data(Codes local_kanjicode, bool mark_as_internet)
    : local_kanjicode(local_kanjicode),
      mark_as_internet(mark_as_internet) {}

OptionTransfer4Form::OptionTransfer4Form(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);
}
OptionTransfer4Form::~OptionTransfer4Form() {}

int OptionTransfer4Form::helpID() const {
  return kHelpTopicOptionTransfer4;
}

void OptionTransfer4Form::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void OptionTransfer4Form::updateUi(const BaseForm::Data& data) {
  const ThisData& data_in = castData(data);
  RadioButtons<Codes> radios{
    { Codes::kSJIS,    *d_->ui.radioButton_CodeSJIS    },
    { Codes::kJIS,     *d_->ui.radioButton_CodeJIS     },
    { Codes::kEUC,     *d_->ui.radioButton_CodeEUC     },
    { Codes::kUTF8N,   *d_->ui.radioButton_CodeUTF8N   },
    { Codes::kUTF8BOM, *d_->ui.radioButton_CodeUTF8BOM },
  };
  radios.setChecked(data_in.local_kanjicode);
  UI_SETCHECKED(d_->ui.checkBox_MarkAsInternet, data_in.mark_as_internet);
}

void OptionTransfer4Form::updateData(BaseForm::Data& data) const {
  ThisData& data_out = castData(data);
  const RadioButtons<Codes> radios{
    { Codes::kSJIS,    *d_->ui.radioButton_CodeSJIS    },
    { Codes::kJIS,     *d_->ui.radioButton_CodeJIS     },
    { Codes::kEUC,     *d_->ui.radioButton_CodeEUC     },
    { Codes::kUTF8N,   *d_->ui.radioButton_CodeUTF8N   },
    { Codes::kUTF8BOM, *d_->ui.radioButton_CodeUTF8BOM },
  };
  data_out.local_kanjicode = radios.checked();
  UI_ISCHECKED(data_out.mark_as_internet, d_->ui.checkBox_MarkAsInternet);
}
