#pragma once

#include <QWidget>

class HostSettingBasicForm : public QWidget {
  Q_OBJECT

 public:
  struct Data {
    std::wstring host_name;
    std::wstring host_adrs;
    std::wstring username;
    std::wstring password;
    bool anonymous;
    std::wstring initdir_local;
    std::wstring initdir_remote;
    std::wstring initdir_remote_now;
    bool enabled_curdir;
    bool last_dir;
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
