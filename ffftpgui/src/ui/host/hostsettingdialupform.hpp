#ifndef FFFTPGUI_UI_HOST_HOSTSETTINGDIALUPFORM_HPP_
#define FFFTPGUI_UI_HOST_HOSTSETTINGDIALUPFORM_HPP_

#include <memory>

#include <QWidget>

#include "ui/base/baseform.hpp"

class HostSettingDialupForm : public BaseForm {
  Q_OBJECT

 public:
  struct Data : public BaseForm::Data {
    Data();
  };

  explicit HostSettingDialupForm(QWidget* parent = Q_NULLPTR);
  virtual ~HostSettingDialupForm();

 protected:
  void setRawData(const BaseForm::Data& data);
  void updateUi(const BaseForm::Data& data);
  void updateData(BaseForm::Data& data) const;

 private slots:

 private:
  class Private;
  Private* d_;
  Q_DISABLE_COPY(HostSettingDialupForm)
};

#endif  // FFFTPGUI_UI_HOST_HOSTSETTINGDIALUPFORM_HPP_
