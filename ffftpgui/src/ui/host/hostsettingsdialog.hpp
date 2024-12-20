#pragma once

#include <QDialog>

#include "ffftp_hostdata.h"

class HostSettingsDialog : public QDialog {
  Q_OBJECT

 public:
  explicit HostSettingsDialog(const ffftp_hostdata& hdata, QWidget* parent = Q_NULLPTR);
  virtual ~HostSettingsDialog();

  void hostData(ffftp_hostdata& hdata) const;

 private slots:
  void accept() override;
  void help();

 private:
  void setHostData(const ffftp_hostdata& hdata);

 private:
  class Private;
  std::unique_ptr<Private> d_;
  Q_DISABLE_COPY(HostSettingsDialog)
};
