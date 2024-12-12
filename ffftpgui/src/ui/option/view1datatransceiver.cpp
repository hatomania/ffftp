#include "view1datatransceiver.hpp"

#include "ffftp_option.h"

IMPL_DATATRANSCEIVER_BEGIN(OptionView1Form);

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
  option.view1 = {
  };
}

IMPL_DATATRANSCEIVER_END(OptionView1Form);
