#ifndef FFFTPGUI_UI_HOST_GENERALDATATRANSCEIVER_HPP_
#define FFFTPGUI_UI_HOST_GENERALDATATRANSCEIVER_HPP_

#include "ffftp_hostdata.h"
#include "ui/base/formdatatransceiver.hpp"
#include "hostsettinggeneralform.hpp"

DATATRANSCEIVER_BEGIN(HostSettingGeneralForm)
DATATRANSCEIVER_SEND(hdata_in) {
  const hostdata& hdata = *static_cast<const hostdata*>(hdata_in);
  ThisData form_data{
      hdata.general.host_name,      hdata.general.host_adrs,
      hdata.general.username,       hdata.general.password,
      hdata.general.anonymous,      hdata.general.initdir_local,
      hdata.general.initdir_remote, hdata.general.initdir_remote_now,
      hdata.general.enabled_curdir, hdata.general.last_dir,
  };
  form().setData(form_data);
}
DATATRANSCEIVER_RECEIVE(hdata_out) {
  static ThisData form_data;
  form_data = static_cast<const ThisData&>(form().data());
  hostdata& hdata = *static_cast<hostdata*>(hdata_out);
  hdata.general = {
      .host_name = form_data.host_name.c_str(),
      .host_adrs = form_data.host_adrs.c_str(),
      .username = form_data.username.c_str(),
      .password = form_data.password.c_str(),
      .anonymous = form_data.anonymous,
      .initdir_local = form_data.initdir_local.c_str(),
      .initdir_remote = form_data.initdir_remote.c_str(),
      .initdir_remote_now = form_data.initdir_remote_now.c_str(),
      .last_dir = form_data.last_dir,
  };
}
DATATRANSCEIVER_END()

#endif  // FFFTPGUI_UI_HOST_GENERALDATATRANSCEIVER_HPP_
