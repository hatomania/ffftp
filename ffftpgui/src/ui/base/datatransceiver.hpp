#ifndef FFFTPGUI_UI_BASE_DATATRANSCEIVER_HPP_
#define FFFTPGUI_UI_BASE_DATATRANSCEIVER_HPP_

#include "ui/base/baseform.hpp"

class DataTransceiver {
 public:
  DataTransceiver() = delete;
  explicit DataTransceiver(BaseForm& form);
  virtual ~DataTransceiver();

  virtual void send(const void* something_data_in) = 0;
  virtual void receive(void* something_data_out) const = 0;

 protected:
  inline const BaseForm& form() const { return form_; }
  inline BaseForm& form() { return form_; }

 private:
  BaseForm& form_;
};

#endif  // FFFTPGUI_UI_BASE_DATATRANSCEIVER_HPP_
