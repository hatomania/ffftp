#pragma once

#include <QWidget>

class DirsAndTaskMsgForm : public QWidget {
  Q_OBJECT

 public:
  explicit DirsAndTaskMsgForm(QWidget* parent = Q_NULLPTR,
                              bool isshowndot = false);
  void setTaskMessage(const QString& msg) const;
  void addTaskMessage(const QString& msg) const;
  void setDotFileShown(bool isshown);
  void setPathLocal(const QString& path);
  void setPathRemote(const QString& path);

 private slots:
  // for Local
  void onClicked_toolButton_LocalUp();
  void onClicked_toolButton_LocalOpen();
  void onCurrentIndexChanged_comboBox_LocalDir(int index);
  void onDoubleClicked_treeView_LocalDir(const QModelIndex& index);
  // for Remote
  void onClicked_toolButton_RemoteUp();
  void onClicked_toolButton_RemoteOpen();
  void onCurrentIndexChanged_comboBox_RemoteDir(int index);
  void onDoubleClicked_treeView_RemoteDir(const QModelIndex& index);

 private:
  class Private;
  Private* d_;
  Q_DISABLE_COPY(DirsAndTaskMsgForm)
};
