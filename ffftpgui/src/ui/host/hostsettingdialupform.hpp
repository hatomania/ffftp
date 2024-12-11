#ifndef FFFTPGUI_UI_HOST_HOSTSETTINGDIALUPFORM_HPP_
#define FFFTPGUI_UI_HOST_HOSTSETTINGDIALUPFORM_HPP_

#include <memory>

#include <QWidget>

#include "ui/base/baseform.hpp"

class HostSettingDialupForm : public BaseForm {
  Q_OBJECT

 public:
  struct Data : public BaseForm::Data {
    bool dialup;
    std::vector<std::wstring> dial_entries;
    std::wstring dial_entry;
    bool dialup_always;
    bool dialup_notify;
    Data();
    Data(bool dialup, const std::vector<std::wstring>& dial_entries,
         const std::wstring& dial_entry, bool dialup_always,
         bool dialup_notify);
  };

  explicit HostSettingDialupForm(QWidget* parent = Q_NULLPTR);
  virtual ~HostSettingDialupForm();
  int helpID() const override;

 protected:
  void setRawData(const BaseForm::Data& data) override;
  void updateUi(const BaseForm::Data& data) override;
  void updateData(BaseForm::Data& data) const override;

 private slots:

 private:
  class Private;
  std::unique_ptr<Private> d_;
  Q_DISABLE_COPY(HostSettingDialupForm)
};

#endif  // FFFTPGUI_UI_HOST_HOSTSETTINGDIALUPFORM_HPP_
