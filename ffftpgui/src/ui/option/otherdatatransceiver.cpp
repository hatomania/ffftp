#include "otherdatatransceiver.hpp"

#include "ffftp_option.h"

IMPL_DATATRANSCEIVER_BEGIN(OptionOtherForm);

IMPL_DATATRANSCEIVER_SEND(option_in) {
  const ffftp_option& opt = *static_cast<const ffftp_option*>(option_in);
  ThisData form_data{
    opt.other.save_win_pos,
    opt.other.reg_type,
    opt.other.encrypt_all_settings,
    opt.other.debug_console,
  };
  form().setData(form_data);
}

IMPL_DATATRANSCEIVER_RECEIVE(option_out) {
  static ThisData form_data;
  form_data = static_cast<const ThisData&>(form().data());
  ffftp_option& opt = *static_cast<ffftp_option*>(option_out);
  opt.other = {
    .save_win_pos = form_data.save_win_pos,
    .reg_type = form_data.reg_type,
    .encrypt_all_settings = form_data.encrypt_all_settings,
    .debug_console = form_data.debug_console,
  };
}

IMPL_DATATRANSCEIVER_END(OptionOtherForm);
