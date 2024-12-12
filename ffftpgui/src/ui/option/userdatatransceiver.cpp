﻿#include "userdatatransceiver.hpp"

#include "ffftp_option.h"

IMPL_DATATRANSCEIVER_BEGIN(OptionUserForm);

IMPL_DATATRANSCEIVER_SEND(option_in) {
  const ffftp_option& hdata = *static_cast<const ffftp_option*>(option_in);
  ThisData form_data{
  };
  form().setData(form_data);
}

IMPL_DATATRANSCEIVER_RECEIVE(option_out) {
  static ThisData form_data;
  form_data = static_cast<const ThisData&>(form().data());
  ffftp_option& option = *static_cast<ffftp_option*>(option_out);
  option.user = {
  };
}

IMPL_DATATRANSCEIVER_END(OptionUserForm);
