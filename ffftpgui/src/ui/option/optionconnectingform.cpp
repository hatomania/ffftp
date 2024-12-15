#include "optionconnectingform.hpp"

#include "ui_optionconnectingform.h"

#include "stdafx.h"
#include "ui/uicommon.h"

namespace {
using ThisData = OptionConnectingForm::Data;
inline const ThisData& castData(const BaseForm::Data& data) {
  return static_cast<const ThisData&>(data);
}
inline ThisData& castData(BaseForm::Data& data) {
  return static_cast<ThisData&>(data);
}
}  // namespace

class OptionConnectingForm::Private {
 public:
  Private();
  ~Private();
  Ui::OptionConnectingForm ui;
};
OptionConnectingForm::Private::Private() : ui() {}
OptionConnectingForm::Private::~Private() {}

OptionConnectingForm::Data::Data()
  : connect_on_start(false),
    connect_and_set(false),
    ras_close(false),
    ras_close_notify(false),
    file_hist(0),
    pass_to_hist(false),
    quick_anonymous(false),
    send_quit(false),
    no_ras_control(false),
    upnp_enabled(false) {}

OptionConnectingForm::Data::Data(
  bool connect_on_start,
  bool connect_and_set,
  bool ras_close,
  bool ras_close_notify,
  int file_hist,
  bool pass_to_hist,
  bool quick_anonymous,
  bool send_quit,
  bool no_ras_control,
  bool upnp_enabled)
  : connect_on_start(connect_on_start),
    connect_and_set(connect_and_set),
    ras_close(ras_close),
    ras_close_notify(ras_close_notify),
    file_hist(file_hist),
    pass_to_hist(pass_to_hist),
    quick_anonymous(quick_anonymous),
    send_quit(send_quit),
    no_ras_control(no_ras_control),
    upnp_enabled(upnp_enabled) {}

OptionConnectingForm::OptionConnectingForm(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);
}
OptionConnectingForm::~OptionConnectingForm() {}

int OptionConnectingForm::helpID() const {
  return kHelpTopicOptionConnecting;
}

void OptionConnectingForm::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void OptionConnectingForm::updateUi(const BaseForm::Data& data) {
  const ThisData& data_in = castData(data);
  UI_SETCHECKED(d_->ui.checkBox_ConnectOnStart, data_in.connect_on_start);
  UI_SETCHECKED(d_->ui.checkBox_ConnectAndSet, data_in.connect_and_set);
  UI_SETCHECKED(d_->ui.groupBox_RasClose, data_in.ras_close);
  UI_SETCHECKED(d_->ui.checkBox_RasCloseNotify, data_in.ras_close_notify);
  UI_SETVALUE(d_->ui.spinBox_FileHist, data_in.file_hist);
  UI_SETCHECKED(d_->ui.checkBox_PassToHist, data_in.pass_to_hist);
  UI_SETCHECKED(d_->ui.checkBox_QuickAnonymous, data_in.quick_anonymous);
  UI_SETCHECKED(d_->ui.checkBox_SendQuit, data_in.send_quit);
  UI_SETCHECKED(d_->ui.checkBox_NoRasControl, data_in.no_ras_control);
  UI_SETCHECKED(d_->ui.checkBox_UPnPEnabled, data_in.upnp_enabled);
}

void OptionConnectingForm::updateData(BaseForm::Data& data) const {
  ThisData& data_out = castData(data);
  UI_ISCHECKED(data_out.connect_on_start, d_->ui.checkBox_ConnectOnStart);
  UI_ISCHECKED(data_out.connect_and_set, d_->ui.checkBox_ConnectAndSet);
  UI_ISCHECKED(data_out.ras_close, d_->ui.groupBox_RasClose);
  UI_ISCHECKED(data_out.ras_close_notify, d_->ui.checkBox_RasCloseNotify);
  UI_VALUE(data_out.file_hist, d_->ui.spinBox_FileHist);
  UI_ISCHECKED(data_out.pass_to_hist, d_->ui.checkBox_PassToHist);
  UI_ISCHECKED(data_out.quick_anonymous, d_->ui.checkBox_QuickAnonymous);
  UI_ISCHECKED(data_out.send_quit, d_->ui.checkBox_SendQuit);
  UI_ISCHECKED(data_out.no_ras_control, d_->ui.checkBox_NoRasControl);
  UI_ISCHECKED(data_out.upnp_enabled, d_->ui.checkBox_UPnPEnabled);
}
