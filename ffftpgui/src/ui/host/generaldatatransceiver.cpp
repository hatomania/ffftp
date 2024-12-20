#include "generaldatatransceiver.hpp"

#include "ffftp_hostdata.h"

IMPL_DATATRANSCEIVER_BEGIN(HostSettingGeneralForm);

IMPL_DATATRANSCEIVER_SEND(hdata_in) {
  const ffftp_hostdata& hdata = *static_cast<const ffftp_hostdata*>(hdata_in);
  ThisData form_data{
      hdata.general.host_name,
      hdata.general.host_adrs,
      hdata.general.username,
      hdata.general.password,
      hdata.general.anonymous_password,
      hdata.general.anonymous,
      hdata.general.initdir_local,
      hdata.general.initdir_remote,
      hdata.general.initdir_remote_now,
      hdata.general.enabled_curdir,
      hdata.general.last_dir,
  };
  form().setData(form_data);
}

IMPL_DATATRANSCEIVER_RECEIVE(hdata_out) {
  static ThisData form_data;
  form_data = static_cast<const ThisData&>(form().data());
  ffftp_hostdata& hdata = *static_cast<ffftp_hostdata*>(hdata_out);
  hdata.general = {
      .host_name = form_data.host_name.c_str(),
      .host_adrs = form_data.host_adrs.c_str(),
      .username = form_data.username.c_str(),
      .password = form_data.password.c_str(),
      .anonymous_password = form_data.anonymous_password.c_str(),
      .anonymous = form_data.anonymous,
      .initdir_local = form_data.initdir_local.c_str(),
      .initdir_remote = form_data.initdir_remote.c_str(),
      .initdir_remote_now = form_data.initdir_remote_now.c_str(),
      .last_dir = form_data.last_dir,
  };
}

IMPL_DATATRANSCEIVER_END(HostSettingGeneralForm);
