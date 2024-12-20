#include "featuredatatransceiver.hpp"

#include "ffftp_hostdata.h"

IMPL_DATATRANSCEIVER_BEGIN(HostSettingFeatureForm);

IMPL_DATATRANSCEIVER_SEND(hdata_in) {
  const ffftp_hostdata& hdata = *static_cast<const ffftp_hostdata*>(hdata_in);
  ThisData form_data{
    hdata.feature.max_thread_cnt,
    hdata.feature.reuse_cmdsocket,
    hdata.feature.no_pasv_adrs,
    hdata.feature.noop_interval,
    hdata.feature.error_mode,
    hdata.feature.reconnect,
  };
  form().setData(form_data);
}

IMPL_DATATRANSCEIVER_RECEIVE(hdata_out) {
  static ThisData form_data;
  form_data = static_cast<const ThisData&>(form().data());
  ffftp_hostdata& hdata = *static_cast<ffftp_hostdata*>(hdata_out);
  hdata.feature = {
    .max_thread_cnt = form_data.max_thread_cnt,
    .reuse_cmdsocket = form_data.reuse_cmdsocket,
    .no_pasv_adrs = form_data.no_pasv_adrs,
    .noop_interval = form_data.noop_interval,
    .error_mode = form_data.error_mode,
    .reconnect = form_data.reconnect,
  };
}

IMPL_DATATRANSCEIVER_END(HostSettingFeatureForm);
