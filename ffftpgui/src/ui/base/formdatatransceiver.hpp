#ifndef FFFTPGUI_UI_BASE_FORMDATATRANSCEIVER_HPP_
#define FFFTPGUI_UI_BASE_FORMDATATRANSCEIVER_HPP_

#include "ui/base/datatransceiver.hpp"

template <typename F>
class FormDataTransceiver : public DataTransceiver {};

#define DATATRANSCEIVER_BEGIN(FORM)                                     \
  template <>                                                           \
  class FormDataTransceiver<FORM> : public DataTransceiver {            \
   public:                                                              \
    using ThisData = FORM::Data;                                        \
    FormDataTransceiver() = delete;                                     \
    explicit FormDataTransceiver(FORM& form) : DataTransceiver(form) {} \
    virtual ~FormDataTransceiver() {}
#define DATATRANSCEIVER_SEND(DATA) void send(const void* DATA)
#define DATATRANSCEIVER_RECEIVE(DATA) void receive(void* DATA) const
#define DATATRANSCEIVER_END() \
  }                           \
  ;

#endif  // FFFTPGUI_UI_BASE_FORMDATATRANSCEIVER_HPP_
