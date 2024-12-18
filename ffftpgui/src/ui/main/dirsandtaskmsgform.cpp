#include "dirsandtaskmsgform.hpp"

#include <QScrollBar>

#include "ui_dirsandtaskmsgform.h"

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class DirsAndTaskMsgForm::Private {
 public:
  Private();
  ~Private();
  Ui::DirsAndTaskMsgForm ui;
  QString taskmsg;
};
DirsAndTaskMsgForm::Private::Private() : ui{}, taskmsg{} {}
DirsAndTaskMsgForm::Private::~Private() {}

DirsAndTaskMsgForm::DirsAndTaskMsgForm(QWidget* parent)
    : QWidget{parent}, d_{new Private{}} {
  d_->ui.setupUi(this);
}
DirsAndTaskMsgForm::~DirsAndTaskMsgForm() {}

static void _msg(QTextEdit& e, const QString& m) {
  e.setText(m);
  e.verticalScrollBar()->setValue(e.verticalScrollBar()->maximum());
}
void DirsAndTaskMsgForm::setTaskMessage(const QString& msg) const {
  d_->taskmsg = msg;
  _msg(*d_->ui.textEdit_TaskMsg, d_->taskmsg);
}

void DirsAndTaskMsgForm::addTaskMessage(const QString& msg) const {
  d_->taskmsg += msg;
  _msg(*d_->ui.textEdit_TaskMsg, d_->taskmsg);
}

void DirsAndTaskMsgForm::setDotFileShown(bool isshown) {}
void DirsAndTaskMsgForm::setLocalPath(const QString& path) {
  d_->ui.widget_FileListLocal->setPath(path);
}
void DirsAndTaskMsgForm::setRemotePath(const QString& path) {}

void DirsAndTaskMsgForm::showDetail(bool is_detail) const {
  d_->ui.widget_FileListLocal->showDetail(is_detail);
//  d_->ui.widget_FileListRemote->showDetail(is_detail);
}
