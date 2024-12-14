#include "view2datatransceiver.hpp"

#include "ffftp_option.h"

IMPL_DATATRANSCEIVER_BEGIN(OptionView2Form);

IMPL_DATATRANSCEIVER_SEND(option_in) {
  const ffftp_option& opt = *static_cast<const ffftp_option*>(option_in);
  ThisData form_data{
    opt.view2.disp_permissions_number,
    opt.view2.auto_refresh_filelist,
    opt.view2.remove_old_log,
  };
  form().setData(form_data);
}

IMPL_DATATRANSCEIVER_RECEIVE(option_out) {
  static ThisData form_data;
  form_data = static_cast<const ThisData&>(form().data());
  ffftp_option& opt = *static_cast<ffftp_option*>(option_out);
  opt.view2 = {
    .disp_permissions_number = form_data.disp_permissions_number,
    .auto_refresh_filelist = form_data.auto_refresh_filelist,
    .remove_old_log = form_data.remove_old_log,
  };
}

IMPL_DATATRANSCEIVER_END(OptionView2Form);
