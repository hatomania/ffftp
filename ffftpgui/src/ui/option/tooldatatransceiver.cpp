#include "tooldatatransceiver.hpp"

#include "ffftp_option.h"

IMPL_DATATRANSCEIVER_BEGIN(OptionToolForm);

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
  option.tool = {
  };
}

IMPL_DATATRANSCEIVER_END(OptionToolForm);
