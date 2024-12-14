#ifndef FFFTPGUI_UI_BASE_FORMDATATRANSCEIVER_HPP_
#define FFFTPGUI_UI_BASE_FORMDATATRANSCEIVER_HPP_

#include "ui/base/datatransceiver.hpp"

template <typename>
class FormDataTransceiver : public DataTransceiver {};

#define DECL_DATATRANSCEIVER(FORM)                           \
  template <>                                                \
  class FormDataTransceiver<FORM> : public DataTransceiver { \
   public:                                                   \
    using ThisData = FORM::Data;                             \
    FormDataTransceiver() = delete;                          \
    explicit FormDataTransceiver(FORM& form);                \
    virtual ~FormDataTransceiver();                          \
                                                             \
    void send(const void*) override;                         \
    void receive(void*) const override;                      \
  };                                                         \
  using FORM##DataTransceiver = FormDataTransceiver<FORM>;

#define IMPL_DATATRANSCEIVER_BEGIN(FORM)                     \
  namespace {                                                \
  using Form = FORM;                                         \
  }                                                          \
  FormDataTransceiver<Form>::FormDataTransceiver(Form& form) \
      : DataTransceiver(form) {}                             \
  FormDataTransceiver<Form>::~FormDataTransceiver() {}

#define IMPL_DATATRANSCEIVER_SEND(DATA) \
  void FormDataTransceiver<Form>::send(const void* DATA)

#define IMPL_DATATRANSCEIVER_RECEIVE(DATA) \
  void FormDataTransceiver<Form>::receive(void* DATA) const

#define IMPL_DATATRANSCEIVER_END(FORM)

inline std::vector<std::wstring> wchar2VectorWstr(const wchar_t** in_str, size_t in_cnt) {
  std::vector<std::wstring> out_str;
  out_str.clear();
  out_str.reserve(in_cnt);
  for (int i = 0; i < in_cnt; ++i) {
    out_str.push_back(in_str[i]);
  }
  return out_str;
};

inline void vectorWstr2Wchar(const wchar_t**& out_str, size_t& out_cnt,
                             const std::vector<std::wstring>& in_str) {
  delete[] out_str;
  out_str = nullptr;
  out_cnt = in_str.size();
  if (!in_str.empty()) {
    out_str = new const wchar_t*[out_cnt];
    for (int i = 0; const auto& str : in_str) {
      out_str[i++] = str.c_str();
    }
  }
};

#endif  // FFFTPGUI_UI_BASE_FORMDATATRANSCEIVER_HPP_
