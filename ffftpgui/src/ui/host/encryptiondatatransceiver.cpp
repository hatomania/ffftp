#include "encryptiondatatransceiver.hpp"

#include "ffftp_hostdata.h"

IMPL_DATATRANSCEIVER_BEGIN(HostSettingEncryptionForm);

IMPL_DATATRANSCEIVER_SEND(hdata_in) {
  const hostdata& hdata = *static_cast<const hostdata*>(hdata_in);
  ThisData form_data{
      hdata.encryption.use_no_encryption,
      hdata.encryption.use_ftp_es,
      hdata.encryption.use_ftp_is,
  };
  form().setData(form_data);
}

IMPL_DATATRANSCEIVER_RECEIVE(hdata_out) {
  static ThisData form_data;
  form_data = static_cast<const ThisData&>(form().data());
  hostdata& hdata = *static_cast<hostdata*>(hdata_out);
  hdata.encryption = {
    .use_no_encryption = form_data.use_no_encryption,
    .use_ftp_es = form_data.use_ftp_es,
    .use_ftp_is = form_data.use_ftp_is,
  };
}

IMPL_DATATRANSCEIVER_END(HostSettingEncryptionForm);
