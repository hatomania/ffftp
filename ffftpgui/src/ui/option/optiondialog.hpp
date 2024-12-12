#ifndef FFFTPGUI_UI_OPTION_OPTIONDIALOG_HPP_
#define FFFTPGUI_UI_OPTION_OPTIONDIALOG_HPP_

#include <QDialog>

#include "ffftp_option.h"

class OptionDialog : public QDialog {
  Q_OBJECT;

 public:
  explicit OptionDialog(const ffftp_option& option,
                        QWidget* parent = Q_NULLPTR);
  virtual ~OptionDialog();

  void option(ffftp_option& option) const;

 private slots:
  void accept() override;
  void help();

 private:
  void setOption(const ffftp_option& option);

 private:
  class Private;
  std::unique_ptr<Private> d_;
  Q_DISABLE_COPY_MOVE(OptionDialog);
};

#endif  // FFFTPGUI_UI_OPTION_OPTIONDIALOG_HPP_
