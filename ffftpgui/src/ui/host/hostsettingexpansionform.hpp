#pragma once

#include <QWidget>

class HostSettingExpansionForm : public QWidget {
  Q_OBJECT

 public:
  struct Data {
    bool use_firewall;
    bool use_pasv_mode;
    bool use_folder_samemove;
    int port;
    QString account;
    int timezone;
    int security;
    QString cmd_when_connect;
    Data();
  };
  explicit HostSettingExpansionForm(QWidget* parent = Q_NULLPTR);
  void setData(const Data& data) const;
  const Data& getData() const;
  void setDataAsDefault() const;

 private slots:
  void onClick_pushButton_StdPort();

 private:
  class Private;
  Private* d_;
  Q_DISABLE_COPY(HostSettingExpansionForm)
};
