#include "inputdialog.hpp"

#include <QDialogButtonBox>

#include "ffftp.h"

class InputDialog::Private {
 public:
  Private() = delete;
  Private(int helpid);
  ~Private();
  int helpid;
};
InputDialog::Private::Private(int helpid) : helpid(helpid) {}
InputDialog::Private::~Private() {}

InputDialog::InputDialog(int helpid, QWidget* parent, Qt::WindowFlags flags)
    : QInputDialog(parent, flags), d_(new Private(helpid)) {
  Q_UNUSED(labelText());
  QDialogButtonBox* buttonbox = findChild<QDialogButtonBox*>();
  QPushButton* help_button = buttonbox->addButton(QDialogButtonBox::StandardButton::Help);
  QObject::connect(buttonbox, SIGNAL(helpRequested()), this, SLOT(help()));
}
InputDialog::~InputDialog() {}

QString InputDialog::getText(
    QWidget *parent,
    const QString &title,
    const QString &label,
    QLineEdit::EchoMode echo,
    const QString &text,
    bool *ok,
    int helpid,
    Qt::WindowFlags flags,
    Qt::InputMethodHints inputMethodHints) {
  std::unique_ptr<InputDialog> dialog(new InputDialog(helpid, parent, flags));
  dialog->setWindowTitle(title);
  dialog->setLabelText(label);
  dialog->setTextValue(text);
  dialog->setTextEchoMode(echo);
  dialog->setInputMethodHints(inputMethodHints);

  QString ret{};
  const int isok = dialog->exec();
  if (ok)
      *ok = !!isok;
  if (isok) {
      ret = dialog->textValue();
  }
  return ret;
}

void InputDialog::help() {
  ffftp_showhelp(d_->helpid);
}
