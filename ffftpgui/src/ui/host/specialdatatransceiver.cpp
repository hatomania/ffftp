#include "specialdatatransceiver.hpp"

#include "ffftp_hostdata.h"

IMPL_DATATRANSCEIVER_BEGIN(HostSettingSpecialForm);

IMPL_DATATRANSCEIVER_SEND(hdata_in) {
  const ffftp_hostdata& hdata = *static_cast<const ffftp_hostdata*>(hdata_in);
  ThisData form_data{
      hdata.special.list_cmd_only, hdata.special.use_mlsd,
      hdata.special.use_nlst_r,    hdata.special.no_fullpath,
      hdata.special.chmod_cmd,     hdata.special.host_type,
      hdata.special.ls_name,
  };
  form().setData(form_data);
}

IMPL_DATATRANSCEIVER_RECEIVE(hdata_out) {
  static ThisData form_data;
  form_data = static_cast<const ThisData&>(form().data());
  ffftp_hostdata& hdata = *static_cast<ffftp_hostdata*>(hdata_out);
  hdata.special = {
      .list_cmd_only = form_data.list_cmd_only,
      .use_mlsd = form_data.use_mlsd,
      .use_nlst_r = form_data.use_nlst_r,
      .no_fullpath = form_data.no_fullpath,
      .chmod_cmd = form_data.chmod_cmd.c_str(),
      .host_type = form_data.host_type,
      .ls_name = form_data.ls_name.c_str(),
  };
}

IMPL_DATATRANSCEIVER_END(HostSettingSpecialForm);
