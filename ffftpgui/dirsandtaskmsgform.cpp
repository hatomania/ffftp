#include "dirsandtaskmsgform.hpp"
#include "ui_dirsandtaskmsgform.h"
#include "myfilesystemmodel.hpp"
#include "stdafx.h"

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class DirsAndTaskMsgForm::Private {
public:
    Private() {}
    ~Private() {}
    Ui::DirsAndTaskMsgForm ui;
    QString taskmsg;
    QFileSystemModel* dirmodel;
    QFileSystemModel* filemodel;
    MyFileSystemModel* mymodel;
};

DirsAndTaskMsgForm::DirsAndTaskMsgForm(QWidget* parent)
    : QWidget(parent), d_(new DirsAndTaskMsgForm::Private())
{
    d_->ui.setupUi(this);
    //d_->dirmodel = new QFileSystemModel(this);
    //d_->dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::Dirs);
    //d_->dirmodel->setRootPath("C:\\");
    d_->mymodel = new MyFileSystemModel(this);
    d_->ui.treeView_LocalDir->setModel(d_->mymodel);
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
