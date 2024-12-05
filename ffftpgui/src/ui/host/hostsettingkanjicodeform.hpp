#ifndef FFFTPGUI_UI_HOST_HOSTSETTINGKANJICODEFORM_HPP_
#define FFFTPGUI_UI_HOST_HOSTSETTINGKANJICODEFORM_HPP_

#include <memory>

#include <QWidget>

#include "ui/base/baseform.hpp"

class HostSettingKanjiCodeForm : public BaseForm {
  Q_OBJECT

 public:
  struct Data : public BaseForm::Data {
    Data();
  };

  explicit HostSettingKanjiCodeForm(QWidget* parent = Q_NULLPTR);
  virtual ~HostSettingKanjiCodeForm();

 protected:
  void setRawData(const BaseForm::Data& data);
  void updateUi(const BaseForm::Data& data);
  void updateData(BaseForm::Data& data) const;

 private slots:

 private:
  class Private;
  Private* d_;
  Q_DISABLE_COPY(HostSettingKanjiCodeForm)
};

#endif  // FFFTPGUI_UI_HOST_HOSTSETTINGKANJICODEFORM_HPP_
