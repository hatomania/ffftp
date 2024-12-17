#include "connectingdatatransceiver.hpp"

#include "ffftp_option.h"

IMPL_DATATRANSCEIVER_BEGIN(OptionConnectingForm);

IMPL_DATATRANSCEIVER_SEND(option_in) {
  const ffftp_option& opt = *static_cast<const ffftp_option*>(option_in);
  ThisData form_data{
      opt.connecting.connect_on_start,
      opt.connecting.connect_and_set,
      opt.connecting.ras_close,
      opt.connecting.ras_close_notify,
      opt.connecting.file_hist,
      opt.connecting.pass_to_hist,
      opt.connecting.quick_anonymous,
      opt.connecting.send_quit,
      opt.connecting.no_ras_control,
      opt.connecting.upnp_enabled,
  };
  form().setData(form_data);
}

IMPL_DATATRANSCEIVER_RECEIVE(option_out) {
  static ThisData form_data;
  form_data = static_cast<const ThisData&>(form().data());
  ffftp_option& opt = *static_cast<ffftp_option*>(option_out);
  opt.connecting = {
      .connect_on_start = form_data.connect_on_start,
      .connect_and_set = form_data.connect_and_set,
      .ras_close = form_data.ras_close,
      .ras_close_notify = form_data.ras_close_notify,
      .file_hist = form_data.file_hist,
      .pass_to_hist = form_data.pass_to_hist,
      .quick_anonymous = form_data.quick_anonymous,
      .send_quit = form_data.send_quit,
      .no_ras_control = form_data.no_ras_control,
      .upnp_enabled = form_data.upnp_enabled,
  };
}

IMPL_DATATRANSCEIVER_END(OptionConnectingForm);
