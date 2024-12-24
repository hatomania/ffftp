﻿#ifndef FFFTPGUI_UI_OPTION_OPTIONVIEW1FORM_HPP_
#define FFFTPGUI_UI_OPTION_OPTIONVIEW1FORM_HPP_

#include <memory>

#include <QWidget>

#include "ui/base/baseform.hpp"

class OptionView1Form : public BaseForm {
  Q_OBJECT;

 public:
  struct Data : public BaseForm::Data {
    int font;
    bool disp_ignore_hide;
    bool disp_drives;
    bool disp_file_icon;
    bool disp_time_seconds;
    Data();
    Data(
      int font,
      bool disp_ignore_hide,
      bool disp_drives,
      bool disp_file_icon,
      bool disp_time_seconds);
  };

  explicit OptionView1Form(QWidget* parent = Q_NULLPTR);
  virtual ~OptionView1Form();
  int helpID() const override;

 protected:
  void setRawData(const BaseForm::Data& data) override;
  void updateUi(const BaseForm::Data& data) override;
  void updateData(BaseForm::Data& data) const override;

 private slots:
  void onClick_pushButton_ChangeFont();

 private:
  class Private;
  std::unique_ptr<Private> d_;
  Q_DISABLE_COPY_MOVE(OptionView1Form);
};

#endif  // FFFTPGUI_UI_OPTION_OPTIONVIEW1FORM_HPP_