#include "view1datatransceiver.hpp"

#include "ffftp_option.h"

IMPL_DATATRANSCEIVER_BEGIN(OptionView1Form);

IMPL_DATATRANSCEIVER_SEND(option_in) {
  const ffftp_option& opt = *static_cast<const ffftp_option*>(option_in);
  ThisData form_data{
      opt.view1.font,  // TODO: フォント処理
      opt.view1.disp_ignore_hide,
      opt.view1.disp_drives,
      opt.view1.disp_file_icon,
      opt.view1.disp_time_seconds,
  };
  form().setData(form_data);
}

IMPL_DATATRANSCEIVER_RECEIVE(option_out) {
  static ThisData form_data;
  form_data = static_cast<const ThisData&>(form().data());
  ffftp_option& opt = *static_cast<ffftp_option*>(option_out);
  opt.view1 = {
      .font = form_data.font,  // TODO: フォント処理
      .disp_ignore_hide = form_data.disp_ignore_hide,
      .disp_drives = form_data.disp_drives,
      .disp_file_icon = form_data.disp_file_icon,
      .disp_time_seconds = form_data.disp_time_seconds,
  };
}

IMPL_DATATRANSCEIVER_END(OptionView1Form);
