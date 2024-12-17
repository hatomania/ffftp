#ifndef FFFTPGUI_UI_MAIN_DIRSANDTASKMSGFORM_HPP_
#define FFFTPGUI_UI_MAIN_DIRSANDTASKMSGFORM_HPP_

#include <QWidget>

class DirsAndTaskMsgForm : public QWidget {
  Q_OBJECT;

 public:
  explicit DirsAndTaskMsgForm(QWidget* parent = Q_NULLPTR);
  virtual ~DirsAndTaskMsgForm();
  void setTaskMessage(const QString& msg) const;
  void addTaskMessage(const QString& msg) const;
  void setDotFileShown(bool isshown);
  void setLocalPath(const QString& path);
  void setRemotePath(const QString& path);

 private:
  class Private;
  std::unique_ptr<Private> d_;
  Q_DISABLE_COPY_MOVE(DirsAndTaskMsgForm);
};

#endif  // FFFTPGUI_UI_MAIN_DIRSANDTASKMSGFORM_HPP_
