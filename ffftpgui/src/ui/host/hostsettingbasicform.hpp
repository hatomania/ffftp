#pragma once

#include <QtWidgets/QWidget>

class HostSettingBasicForm : public QWidget {
  Q_OBJECT

 public:
  struct Data {
    QString settingname;
    QString hostaddr;
    QString username;
    QString password;
    bool is_anonymous;
    QString initdir_local;
    QString initdir_remote;
    bool is_lastdir_as_initdir;
    Data();
  };
  explicit HostSettingBasicForm(QWidget* parent = Q_NULLPTR);
  void setData(const Data& data) const;
  const Data& getData() const;
  void setDataAsDefault() const;

 private slots:
  void onClick_toolButton_SelectLocalDir();
  void onClick_pushButton_NowDir();
  void onClick_checkBox_Anonymous(bool);

 private:
  class Private;
  Private* d_;
  Q_DISABLE_COPY(HostSettingBasicForm)
};
