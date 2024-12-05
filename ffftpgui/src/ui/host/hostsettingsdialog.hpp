#pragma once

#include <QDialog>

#include "ffftp_hostdata.h"

class HostSettingsDialog : public QDialog {
  Q_OBJECT

 public:
  explicit HostSettingsDialog(const hostdata& hdata, QWidget* parent = Q_NULLPTR);

  void hostData(hostdata& hdata) const;

 private slots:
  void accept() override;
  void help();

 private:
  void setHostData(const hostdata& hdata);

 private:
  class Private;
  Private* d_;
  Q_DISABLE_COPY(HostSettingsDialog)
};
