#include"dialupdatatransceiver.hpp"

#include "ffftp_hostdata.h"

IMPL_DATATRANSCEIVER_BEGIN(HostSettingDialupForm);

IMPL_DATATRANSCEIVER_SEND(hdata_in) {
  const ffftp_hostdata& hdata = *static_cast<const ffftp_hostdata*>(hdata_in);
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

IMPL_DATATRANSCEIVER_RECEIVE(hdata_out) {
  static ThisData form_data;
  form_data = static_cast<const ThisData&>(form().data());
  ffftp_hostdata& hdata = *static_cast<ffftp_hostdata*>(hdata_out);
  hdata.dialup = {
      .dialup = form_data.dialup,
      .dial_entry = form_data.dial_entry.c_str(),
      .dialup_always = form_data.dialup_always,
      .dialup_notify = form_data.dialup_notify,
  };
}

IMPL_DATATRANSCEIVER_END(HostSettingDialupForm);
