#include "transfer2datatransceiver.hpp"

#include "ffftp_option.h"

IMPL_DATATRANSCEIVER_BEGIN(OptionTransfer2Form);

IMPL_DATATRANSCEIVER_SEND(option_in) {
  const ffftp_option& opt = *static_cast<const ffftp_option*>(option_in);
  static const std::map<modes, OptionTransfer2Form::Modes> modes_table{
      { modes::LOWER, OptionTransfer2Form::Modes::kLower },
      { modes::UPPER, OptionTransfer2Form::Modes::kUpper },
      { modes::NOCNV, OptionTransfer2Form::Modes::kNoCnv },
  };
  ThisData form_data{
      modes_table.at(static_cast<modes>(opt.transfer2.fname_cnv)),
      opt.transfer2.timeout,
      opt.transfer2.default_local_path,
  };
  form().setData(form_data);
}

IMPL_DATATRANSCEIVER_RECEIVE(option_out) {
  static ThisData form_data;
  form_data = static_cast<const ThisData&>(form().data());
  ffftp_option& opt = *static_cast<ffftp_option*>(option_out);
  static const std::map<OptionTransfer2Form::Modes, modes> modes_table{
      { OptionTransfer2Form::Modes::kLower, modes::LOWER },
      { OptionTransfer2Form::Modes::kUpper, modes::UPPER },
      { OptionTransfer2Form::Modes::kNoCnv, modes::NOCNV },
  };
  opt.transfer2 = {
      .fname_cnv = modes_table.at(form_data.fname_cnv),
      .timeout = form_data.timeout,
      .default_local_path = form_data.default_local_path.c_str(),
  };
}

IMPL_DATATRANSCEIVER_END(OptionTransfer2Form);
