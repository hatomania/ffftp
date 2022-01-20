#include "dirsandtaskmsgform.hpp"
#include "ui_dirsandtaskmsgform.h"
#include "myfilesystemmodellocal.hpp"
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
    MyFileSystemModel* mymodellocal;
};

DirsAndTaskMsgForm::DirsAndTaskMsgForm(QWidget* parent)
    : QWidget(parent), d_(new DirsAndTaskMsgForm::Private())
{
    d_->ui.setupUi(this);
    d_->ui.treeView_LocalDir->setSortingEnabled(true);
    //d_->dirmodel = new QFileSystemModel(this);
    //d_->dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::Dirs);
    //d_->dirmodel->setRootPath("C:\\");
    d_->mymodellocal = new MyFileSystemModelLocal(this, QDir::homePath()); // TODO: QDir::homePath()
    d_->ui.treeView_LocalDir->setModel(d_->mymodellocal);
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

void DirsAndTaskMsgForm::setDotFileShown(bool isshown) {
    // d_->mymodellocal->setShowDot(isshown); // 動的に切り替えようとすると落ちるのでモデル自体を作り直す↓
    d_->ui.treeView_LocalDir->setModel(nullptr);
    delete d_->mymodellocal;
    d_->mymodellocal = new MyFileSystemModelLocal(this, QDir::homePath(), isshown); // TODO: QDir::homePath()
    d_->ui.treeView_LocalDir->setModel(d_->mymodellocal);
}
