#pragma once

#include <QtWidgets/QDialog>

class HostSettingsDialog : public QDialog {
  Q_OBJECT

 public:
  explicit HostSettingsDialog(QWidget *parent = Q_NULLPTR);

 private slots:
  void accept() override;
  void help();

 private:
  class Private;
  Private *d_;
  Q_DISABLE_COPY(HostSettingsDialog)
};
