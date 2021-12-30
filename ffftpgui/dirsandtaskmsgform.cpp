#include "dirsandtaskmsgform.hpp"
#include "ui_dirsandtaskmsgform.h"
#include "stdafx.h"

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class DirsAndTaskMsgForm::Private {
public:
    Private() {}
    ~Private() {}
    Ui::DirsAndTaskMsgForm ui;
    QString taskmsg;
};

DirsAndTaskMsgForm::DirsAndTaskMsgForm(QWidget* parent)
    : QWidget(parent), d_(new DirsAndTaskMsgForm::Private())
{
    d_->ui.setupUi(this);
}

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
