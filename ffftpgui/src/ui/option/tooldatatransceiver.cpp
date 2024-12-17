#include "tooldatatransceiver.hpp"

#include "ffftp_option.h"

IMPL_DATATRANSCEIVER_BEGIN(OptionToolForm);

IMPL_DATATRANSCEIVER_SEND(option_in) {
  const ffftp_option& opt = *static_cast<const ffftp_option*>(option_in);
  ThisData form_data{
    { opt.tool.viewer_name[0],
      opt.tool.viewer_name[1],
      opt.tool.viewer_name[2] },
  };
  form().setData(form_data);
}

IMPL_DATATRANSCEIVER_RECEIVE(option_out) {
  static ThisData form_data;
  form_data = static_cast<const ThisData&>(form().data());
  ffftp_option& opt = *static_cast<ffftp_option*>(option_out);
  opt.tool.viewer_name[0] = form_data.viewer_name[0].c_str();
  opt.tool.viewer_name[1] = form_data.viewer_name[1].c_str();
  opt.tool.viewer_name[2] = form_data.viewer_name[2].c_str();
}

IMPL_DATATRANSCEIVER_END(OptionToolForm);
