#pragma once

#include <QWidget>

class HostSettingAdvancedForm : public QWidget {
  Q_OBJECT

 public:
  struct Data {
    bool is_LIST_cmd;
    bool is_MLSD_cmd;
    bool is_NLST_cmd;
    bool not_fullpath;
    QString CHMOD_cmd;
    int host;
    QString NLST;
    Data();
  };
  explicit HostSettingAdvancedForm(QWidget* parent = Q_NULLPTR);
  void setData(const Data& data) const;
  const Data& getData() const;
  void setDataAsDefault() const;

 private slots:
  void onClick_pushButton_CHMODCmd();
  void onClick_pushButton_StdNLST();
  void onClick_checkBox_LISTCmd(bool);
  void onCurrentIndexChanged_comboBox_Host(int);

 private:
  class Private;
  Private* d_;
  Q_DISABLE_COPY(HostSettingAdvancedForm)
};
