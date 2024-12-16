#ifndef FFFTPGUI_UI_OPTION_OPTIONOTHERFORM_HPP_
#define FFFTPGUI_UI_OPTION_OPTIONOTHERFORM_HPP_

#include <memory>

#include <QWidget>

#include "ui/base/baseform.hpp"

class OptionOtherForm : public BaseForm {
  Q_OBJECT;

 public:
  struct Data : public BaseForm::Data {
    bool save_win_pos;
    bool reg_type;
    bool encrypt_all_settings;
    bool debug_console;
    Data();
    Data(
      bool save_win_pos,
      bool reg_type,
      bool encrypt_all_settings,
      bool debug_console);
  };

  explicit OptionOtherForm(QWidget* parent = Q_NULLPTR);
  virtual ~OptionOtherForm();
  int helpID() const override;

 protected:
  void setRawData(const BaseForm::Data& data) override;
  void updateUi(const BaseForm::Data& data) override;
  void updateData(BaseForm::Data& data) const override;

 private Q_SLOTS:
   void onClick_pushButton_OpenSound();

 private:
  class Private;
  std::unique_ptr<Private> d_;
  Q_DISABLE_COPY_MOVE(OptionOtherForm);
};

#endif  // FFFTPGUI_UI_OPTION_OPTIONOTHERFORM_HPP_
