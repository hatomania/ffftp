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

#endif  // FFFTPGUI_UI_BASE_FORMDATATRANSCEIVER_HPP_
