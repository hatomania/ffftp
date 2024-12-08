#ifndef FFFTPGUI_UI_HOST_DIALUPDATATRANSCEIVER_HPP_
#define FFFTPGUI_UI_HOST_DIALUPDATATRANSCEIVER_HPP_

#include "ffftp_hostdata.h"
#include "ui/base/formdatatransceiver.hpp"
#include "hostsettingdialupform.hpp"

DATATRANSCEIVER_BEGIN(HostSettingDialupForm)
DATATRANSCEIVER_SEND(hdata_in) {
  const hostdata& hdata = *static_cast<const hostdata*>(hdata_in);
  ThisData form_data;
  form_data.dialup = hdata.dialup.dialup;
  form_data.dial_entries.clear();
  for (int i = 0; i < hdata.dialup.dial_entries_cnt; ++i) {
    form_data.dial_entries.push_back(hdata.dialup.dial_entries[i]);
  }
  form_data.dial_entry = hdata.dialup.dial_entry;
  form_data.dialup_always = hdata.dialup.dialup_always;
  form_data.dialup_notify = hdata.dialup.dialup_notify;
  form().setData(form_data);
}
DATATRANSCEIVER_RECEIVE(hdata_out) {
  static ThisData form_data;
  form_data = static_cast<const ThisData&>(form().data());
  hostdata& hdata = *static_cast<hostdata*>(hdata_out);
  hdata.dialup = {
      .dialup = form_data.dialup,
      .dial_entry = form_data.dial_entry.c_str(),
      .dialup_always = form_data.dialup_always,
      .dialup_notify = form_data.dialup_notify,
  };
}
DATATRANSCEIVER_END()

#endif  // FFFTPGUI_UI_HOST_DIALUPDATATRANSCEIVER_HPP_
