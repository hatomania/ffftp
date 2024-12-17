#include "transfer3datatransceiver.hpp"

#include "ffftp_option.h"

IMPL_DATATRANSCEIVER_BEGIN(OptionTransfer3Form);

IMPL_DATATRANSCEIVER_SEND(option_in) {
  const ffftp_option& opt = *static_cast<const ffftp_option*>(option_in);
  ThisData form_data{
      [&opt]() {
        std::vector<std::pair<std::wstring, int>> ret{};
        ret.reserve(opt.transfer3.attrlist_cnt);
        for (int i = 0; i < opt.transfer3.attrlist_cnt; ++i) {
          ret.push_back(std::make_pair(
              opt.transfer3.attrlist_fname[i],
              opt.transfer3.attrlist_attr[i]));
        }
        return ret;
      }(),
      opt.transfer3.use_folder_attr,
      opt.transfer3.folder_attr,
  };
  form().setData(form_data);
}

IMPL_DATATRANSCEIVER_RECEIVE(option_out) {
  static ThisData form_data;
  form_data = static_cast<const ThisData&>(form().data());
  ffftp_option& opt = *static_cast<ffftp_option*>(option_out);
  delete[] opt.transfer3.attrlist_fname;
  delete[] opt.transfer3.attrlist_attr;
  opt.transfer3.attrlist_fname = nullptr;
  opt.transfer3.attrlist_attr = nullptr;
  opt.transfer3.attrlist_cnt = 0;
  if (!form_data.attr_list.empty()) {
    size_t list_cnt = form_data.attr_list.size();
    opt.transfer3.attrlist_fname = new const wchar_t*[list_cnt];
    opt.transfer3.attrlist_attr = new int[list_cnt];
    for (int i = 0; const auto& [fname, attr] : form_data.attr_list) {
      opt.transfer3.attrlist_fname[i] = fname.c_str();
      opt.transfer3.attrlist_attr[i] = attr;
      ++i;
    }
    opt.transfer3.attrlist_cnt = list_cnt;
  }
  opt.transfer3.use_folder_attr = form_data.use_folder_attr;
  opt.transfer3.folder_attr = form_data.folder_attr;
}

IMPL_DATATRANSCEIVER_END(OptionTransfer3Form);
