#ifndef FFFTPGUI_UI_OPTION_OPTIONTRANSFER4FORM_HPP_
#define FFFTPGUI_UI_OPTION_OPTIONTRANSFER4FORM_HPP_

#include <memory>

#include <QWidget>

#include "ui/base/baseform.hpp"

class OptionTransfer4Form : public BaseForm {
  Q_OBJECT;

 public:
  enum class Codes {
    kSJIS,
    kJIS,
    kEUC,
    kUTF8N,
    kUTF8BOM,
  };
  struct Data : public BaseForm::Data {
    Codes local_kanjicode;
    bool mark_as_internet;
    Data();
    Data(Codes local_kanjicode, bool mark_as_internet);
  };

  explicit OptionTransfer4Form(QWidget* parent = Q_NULLPTR);
  virtual ~OptionTransfer4Form();
  int helpID() const override;

 protected:
  void setRawData(const BaseForm::Data& data) override;
  void updateUi(const BaseForm::Data& data) override;
  void updateData(BaseForm::Data& data) const override;

 private Q_SLOTS:

 private:
  class Private;
  std::unique_ptr<Private> d_;
  Q_DISABLE_COPY_MOVE(OptionTransfer4Form);
};

#endif  // FFFTPGUI_UI_OPTION_OPTIONTRANSFER4FORM_HPP_
