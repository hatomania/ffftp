#ifndef FFFTPGUI_UI_OPTION_OPTIONTRANSFER2FORM_HPP_
#define FFFTPGUI_UI_OPTION_OPTIONTRANSFER2FORM_HPP_

#include <memory>

#include <QWidget>

#include "ui/base/baseform.hpp"

class OptionTransfer2Form : public BaseForm {
  Q_OBJECT;

 public:
  enum class Modes {
    kLower,
    kUpper,
    kNoCnv,
  };
  struct Data : public BaseForm::Data {
    Modes fname_cnv;
    int timeout;
    std::wstring default_local_path;
    Data();
    Data(Modes fname_cnv, int timeout, const std::wstring& default_local_path);
  };

  explicit OptionTransfer2Form(QWidget* parent = Q_NULLPTR);
  virtual ~OptionTransfer2Form();
  int helpID() const override;

 protected:
  void setRawData(const BaseForm::Data& data) override;
  void updateUi(const BaseForm::Data& data) override;
  void updateData(BaseForm::Data& data) const override;

 private slots:
  void onClick_toolButton_DefaultLocalPath();

 private:
  class Private;
  std::unique_ptr<Private> d_;
  Q_DISABLE_COPY_MOVE(OptionTransfer2Form);
};

#endif  // FFFTPGUI_UI_OPTION_OPTIONTRANSFER2FORM_HPP_
