#include "optionoperationform.hpp"

#include "ui_optionoperationform.h"

#include "stdafx.h"
#include "ui/uicommon.h"

namespace {
using ThisData = OptionOperationForm::Data;
inline const ThisData& castData(const BaseForm::Data& data) {
  return static_cast<const ThisData&>(data);
}
inline ThisData& castData(BaseForm::Data& data) {
  return static_cast<ThisData&>(data);
}
}  // namespace

class OptionOperationForm::Private {
 public:
  Private();
  ~Private();
  Ui::OptionOperationForm ui;
};
OptionOperationForm::Private::Private() : ui() {}
OptionOperationForm::Private::~Private() {}

OptionOperationForm::Data::Data()
    : recv_mode(Modes::kOverwrite),
      send_mode(Modes::kOverwrite),
      dclick_mode(Modes::kOpen),
      move_mode(Modes::kNoConfirm){}

OptionOperationForm::Data::Data(Modes recv_mode, Modes send_mode, Modes dclick_mode, Modes move_mode)
    : recv_mode(recv_mode),
      send_mode(send_mode),
      dclick_mode(dclick_mode),
      move_mode(move_mode){}

OptionOperationForm::OptionOperationForm(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);
}
OptionOperationForm::~OptionOperationForm() {}

int OptionOperationForm::helpID() const {
  return kHelpTopicOptionOperation;
}

void OptionOperationForm::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void OptionOperationForm::updateUi(const BaseForm::Data& data) {
  const ThisData& data_in = castData(data);
  RadioButtons<Modes> radios_rm{
    { Modes::kOverwrite, *d_->ui.radioButton_RMOverwrite },
    { Modes::kConfirm,   *d_->ui.radioButton_RMConfirm   },
  };
  RadioButtons<Modes> radios_sm{
    { Modes::kOverwrite, *d_->ui.radioButton_SMOverwrite },
    { Modes::kConfirm,   *d_->ui.radioButton_SMConfirm   },
  };
  RadioButtons<Modes> radios_dm{
    { Modes::kOpen,     *d_->ui.radioButton_DMOpen     },
    { Modes::kDownload, *d_->ui.radioButton_DMDownload },
  };
  RadioButtons<Modes> radios_mm{
    { Modes::kNoConfirm, *d_->ui.radioButton_MMNoConfirm },
    { Modes::kConfirm,   *d_->ui.radioButton_MMConfirm   },
    { Modes::kDisable,   *d_->ui.radioButton_MMDisable   },
  };
  radios_rm.setChecked(data_in.recv_mode);
  radios_sm.setChecked(data_in.send_mode);
  radios_dm.setChecked(data_in.dclick_mode);
  radios_mm.setChecked(data_in.move_mode);
}

void OptionOperationForm::updateData(BaseForm::Data& data) const {
  ThisData& data_out = castData(data);
  const RadioButtons<Modes> radios_rm{
    { Modes::kOverwrite, *d_->ui.radioButton_RMOverwrite },
    { Modes::kConfirm,   *d_->ui.radioButton_RMConfirm   },
  };
  const RadioButtons<Modes> radios_sm{
    { Modes::kOverwrite, *d_->ui.radioButton_SMOverwrite },
    { Modes::kConfirm,   *d_->ui.radioButton_SMConfirm   },
  };
  const RadioButtons<Modes> radios_dm{
    { Modes::kOpen,     *d_->ui.radioButton_DMOpen     },
    { Modes::kDownload, *d_->ui.radioButton_DMDownload },
  };
  const RadioButtons<Modes> radios_mm{
    { Modes::kNoConfirm, *d_->ui.radioButton_MMNoConfirm },
    { Modes::kConfirm,   *d_->ui.radioButton_MMConfirm   },
    { Modes::kDisable,   *d_->ui.radioButton_MMDisable   },
  };
  data_out.recv_mode   = radios_rm.checked();
  data_out.send_mode   = radios_sm.checked();
  data_out.dclick_mode = radios_dm.checked();
  data_out.move_mode   = radios_mm.checked();
}
