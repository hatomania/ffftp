#ifndef FFFTPGUI_UI_OPTION_OPTIONOPERATIONFORM_HPP_
#define FFFTPGUI_UI_OPTION_OPTIONOPERATIONFORM_HPP_

#include <memory>

#include <QWidget>

#include "ui/base/baseform.hpp"

class OptionOperationForm : public BaseForm {
  Q_OBJECT;

 public:
  enum class Modes {
    kNoConfirm,
    kConfirm,
    kOverwrite,
    kOpen,
    kDownload,
    kDisable,
  };
  struct Data : public BaseForm::Data {
    Modes recv_mode;
    Modes send_mode;
    Modes dclick_mode;
    Modes move_mode;
    Data();
    Data(Modes recv_mode, Modes send_mode, Modes dclick_mode, Modes move_mode);
  };

  explicit OptionOperationForm(QWidget* parent = Q_NULLPTR);
  virtual ~OptionOperationForm();
  int helpID() const override;

 protected:
  void setRawData(const BaseForm::Data& data) override;
  void updateUi(const BaseForm::Data& data) override;
  void updateData(BaseForm::Data& data) const override;

 private slots:

 private:
  class Private;
  std::unique_ptr<Private> d_;
  Q_DISABLE_COPY_MOVE(OptionOperationForm);
};

#endif  // FFFTPGUI_UI_OPTION_OPTIONOPERATIONFORM_HPP_
