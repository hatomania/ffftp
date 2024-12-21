#ifndef FFFTPGUI_UI_COMMON_INPUTDIALOG_HPP_
#define FFFTPGUI_UI_COMMON_INPUTDIALOG_HPP_

#include <QInputDialog>

class InputDialog : public QInputDialog {
  Q_OBJECT;

 public:
  explicit InputDialog(int helpid, QWidget* parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());
  virtual ~InputDialog();
    static QString getText(
        QWidget *parent,
        const QString &title,
        const QString &label,
        QLineEdit::EchoMode echo = QLineEdit::Normal,
        const QString &text = QString(),
        bool *ok = nullptr,
        int helpid = 0,
        Qt::WindowFlags flags = Qt::WindowFlags(),
        Qt::InputMethodHints inputMethodHints = Qt::ImhNone);

 private Q_SLOTS:
  void help();

 private:
  class Private;
  std::unique_ptr<Private> d_;
  Q_DISABLE_COPY_MOVE(InputDialog);
};

#endif  // FFFTPGUI_UI_COMMON_INPUTDIALOG_HPP_
