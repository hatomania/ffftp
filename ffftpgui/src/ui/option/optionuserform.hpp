﻿#ifndef FFFTPGUI_UI_OPTION_OPTIONUSERFORM_HPP_
#define FFFTPGUI_UI_OPTION_OPTIONUSERFORM_HPP_

#include <memory>

#include <QWidget>

#include "ui/base/baseform.hpp"

class OptionUserForm : public BaseForm {
  Q_OBJECT;

 public:
  struct Data : public BaseForm::Data {
    std::wstring user_mail_adrs;
    Data();
    Data(const std::wstring& user_mail_adrs);
  };

  explicit OptionUserForm(QWidget* parent = Q_NULLPTR);
  virtual ~OptionUserForm();
  void firstFocus() const;
  int helpID() const override;

 protected:
  void setRawData(const BaseForm::Data& data) override;
  void updateUi(const BaseForm::Data& data) override;
  void updateData(BaseForm::Data& data) const override;

 private slots:

 private:
  class Private;
  std::unique_ptr<Private> d_;
  Q_DISABLE_COPY_MOVE(OptionUserForm);
};

#endif  // FFFTPGUI_UI_OPTION_OPTIONUSERFORM_HPP_