#ifndef FFFTPGUI_UI_OPTION_OPTIONCONNECTINGFORM_HPP_
#define FFFTPGUI_UI_OPTION_OPTIONCONNECTINGFORM_HPP_

#include <memory>

#include <QWidget>

#include "ui/base/baseform.hpp"

class OptionConnectingForm : public BaseForm {
  Q_OBJECT;

 public:
  struct Data : public BaseForm::Data {
    bool connect_on_start;
    bool connect_and_set;
    bool ras_close;
    bool ras_close_notify;
    int file_hist;
    bool pass_to_hist;
    bool quick_anonymous;
    bool send_quit;
    bool no_ras_control;
    bool upnp_enabled;
    Data();
    Data(
      bool connect_on_start,
      bool connect_and_set,
      bool ras_close,
      bool ras_close_notify,
      int file_hist,
      bool pass_to_hist,
      bool quick_anonymous,
      bool send_quit,
      bool no_ras_control,
      bool upnp_enabled);
  };

  explicit OptionConnectingForm(QWidget* parent = Q_NULLPTR);
  virtual ~OptionConnectingForm();
  int helpID() const override;

 protected:
  void setRawData(const BaseForm::Data& data) override;
  void updateUi(const BaseForm::Data& data) override;
  void updateData(BaseForm::Data& data) const override;

 private slots:

 private:
  class Private;
  std::unique_ptr<Private> d_;
  Q_DISABLE_COPY_MOVE(OptionConnectingForm);
};

#endif  // FFFTPGUI_UI_OPTION_OPTIONCONNECTINGFORM_HPP_
