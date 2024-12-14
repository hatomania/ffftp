#include "operationdatatransceiver.hpp"

#include "ffftp_option.h"

IMPL_DATATRANSCEIVER_BEGIN(OptionOperationForm);

IMPL_DATATRANSCEIVER_SEND(option_in) {
  const ffftp_option& opt = *static_cast<const ffftp_option*>(option_in);
  ThisData form_data{
    opt.operation.recv_mode   == modes::OVERWRITE ? Form::Modes::kOverwrite :
    opt.operation.recv_mode   == modes::CONFIRM   ? Form::Modes::kConfirm   : Form::Modes::kOverwrite,
    opt.operation.send_mode   == modes::OVERWRITE ? Form::Modes::kOverwrite :
    opt.operation.send_mode   == modes::CONFIRM   ? Form::Modes::kConfirm   : Form::Modes::kOverwrite,
    opt.operation.dclick_mode == modes::OPEN      ? Form::Modes::kOpen :
    opt.operation.dclick_mode == modes::DOWNLOAD  ? Form::Modes::kDownload  : Form::Modes::kOpen,
    opt.operation.move_mode   == modes::NOCONFIRM ? Form::Modes::kNoConfirm :
    opt.operation.move_mode   == modes::CONFIRM   ? Form::Modes::kConfirm   :
    opt.operation.move_mode   == modes::DISABLE   ? Form::Modes::kDisable   : Form::Modes::kNoConfirm,
  };
  form().setData(form_data);
}

IMPL_DATATRANSCEIVER_RECEIVE(option_out) {
  static ThisData form_data;
  form_data = static_cast<const ThisData&>(form().data());
  ffftp_option& opt = *static_cast<ffftp_option*>(option_out);
  opt.operation = {
    .recv_mode =
      form_data.recv_mode   == Form::Modes::kOverwrite ? modes::OVERWRITE :
      form_data.recv_mode   == Form::Modes::kConfirm   ? modes::CONFIRM   : modes::OVERWRITE,
    .send_mode =
      form_data.send_mode   == Form::Modes::kOverwrite ? modes::OVERWRITE :
      form_data.send_mode   == Form::Modes::kConfirm   ? modes::CONFIRM   : modes::OVERWRITE,
    .dclick_mode =
      form_data.dclick_mode == Form::Modes::kOpen      ? modes::OPEN :
      form_data.dclick_mode == Form::Modes::kDownload  ? modes::DOWNLOAD  : modes::OPEN,
    .move_mode =
      form_data.move_mode   == Form::Modes::kNoConfirm ? modes::NOCONFIRM :
      form_data.move_mode   == Form::Modes::kConfirm   ? modes::CONFIRM   :
      form_data.move_mode   == Form::Modes::kDisable   ? modes::DISABLE   : modes::NOCONFIRM,
  };
}

IMPL_DATATRANSCEIVER_END(OptionOperationForm);
