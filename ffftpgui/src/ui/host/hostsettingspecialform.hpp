#ifndef FFFTPGUI_UI_HOST_HOSTSETTINGSPECIALFORM_HPP_
#define FFFTPGUI_UI_HOST_HOSTSETTINGSPECIALFORM_HPP_

#include <memory>

#include <QWidget>

#include "ui/base/baseform.hpp"

class HostSettingSpecialForm : public BaseForm {
  Q_OBJECT

 public:
  struct Data : public BaseForm::Data {
    Data();
  };

  explicit HostSettingSpecialForm(QWidget* parent = Q_NULLPTR);
  virtual ~HostSettingSpecialForm();

 protected:
  void setRawData(const BaseForm::Data& data);
  void updateUi(const BaseForm::Data& data);
  void updateData(BaseForm::Data& data) const;

 private slots:

 private:
  class Private;
  Private* d_;
  Q_DISABLE_COPY(HostSettingSpecialForm)
};

#endif  // FFFTPGUI_UI_HOST_HOSTSETTINGSPECIALFORM_HPP_
