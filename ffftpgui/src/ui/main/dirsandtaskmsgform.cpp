#include "dirsandtaskmsgform.hpp"
#include "ui_dirsandtaskmsgform.h"
#include "myfilesystemmodellocal.hpp"
#include "stdafx.h"

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class DirsAndTaskMsgForm::Private {
public:
    Private(QWidget* parent) : mymodellocal(nullptr), mymodelremote(nullptr), parent_(parent) {}
    ~Private() {}
    void resetModelLocal(const QString& path, bool isshowndot);
    void resetModelRemote(const QString& path, bool isshowndot);
    void saveColumnsWidthLocal();
    void saveColumnsWidthRemote();
    void restoreColumnsWidthLocal();
    void restoreColumnsWidthRemote();
    Ui::DirsAndTaskMsgForm ui;
    QString taskmsg;
    MyFileSystemModel* mymodellocal;
    MyFileSystemModel* mymodelremote;
    QVector<int> columnswidthlocal;
    QVector<int> columnswidthremote;
    QString currentpathlocal;
    QString currentpathremote;
private:
    QWidget* parent_;
};

void DirsAndTaskMsgForm::Private::resetModelLocal(const QString& path, bool isshowndot) {
    saveColumnsWidthLocal();
    ui.treeView_LocalDir->setModel(nullptr);
    delete mymodellocal;
    mymodellocal = new MyFileSystemModelLocal(parent_, path, isshowndot);
    ui.treeView_LocalDir->setModel(mymodellocal);
    currentpathlocal = QDir::cleanPath(path);
    restoreColumnsWidthLocal();
}

void DirsAndTaskMsgForm::Private::resetModelRemote(const QString& path, bool isshowndot) {
    saveColumnsWidthRemote();
    ui.treeView_RemoteDir->setModel(nullptr);
    delete mymodelremote;
    //mymodelremote = new MyFileSystemModelRemote(parent_, path, isshowndot); // TODO: MyFileSystemModelRemoteクラスができたら
    ui.treeView_RemoteDir->setModel(mymodelremote);
    currentpathremote = QDir::cleanPath(path);
    restoreColumnsWidthRemote();
}

void DirsAndTaskMsgForm::Private::saveColumnsWidthLocal() {
    if (!mymodellocal) return;
    columnswidthlocal.clear();
    columnswidthlocal.reserve(mymodellocal->columnCount());
    for (int i = 0; i < mymodellocal->columnCount(); ++i) {
        columnswidthlocal.push_back(ui.treeView_LocalDir->columnWidth(i));
    }
}

void DirsAndTaskMsgForm::Private::saveColumnsWidthRemote() {
    if (!mymodelremote) return;
    columnswidthremote.clear();
    columnswidthremote.reserve(mymodelremote->columnCount());
    for (int i = 0; i < mymodelremote->columnCount(); ++i) {
        columnswidthremote.push_back(ui.treeView_RemoteDir->columnWidth(i));
    }
}

void DirsAndTaskMsgForm::Private::restoreColumnsWidthLocal() {
    for (int i = 0; int w : columnswidthlocal) {
        ui.treeView_LocalDir->setColumnWidth(i++, w);
    }
}

void DirsAndTaskMsgForm::Private::restoreColumnsWidthRemote() {
    for (int i = 0; int w : columnswidthremote) {
        ui.treeView_RemoteDir->setColumnWidth(i++, w);
    }
}

DirsAndTaskMsgForm::DirsAndTaskMsgForm(QWidget* parent, bool isshowndot)
    : QWidget(parent), d_(new DirsAndTaskMsgForm::Private(parent))
{
    d_->ui.setupUi(this);
    d_->ui.treeView_LocalDir->setSortingEnabled(true);
    d_->ui.treeView_RemoteDir->setSortingEnabled(true);
    d_->resetModelLocal(QDir::homePath(), isshowndot); // TODO: QDir::homePath()
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
    d_->resetModelLocal(QDir::homePath(), isshown); // TODO: QDir::homePath()
}

void DirsAndTaskMsgForm::setPathLocal(const QString& path) {
}

void DirsAndTaskMsgForm::setPathRemote(const QString& path) {
}

void DirsAndTaskMsgForm::onClicked_toolButton_LocalUp() {
    qDebug() << __FUNCTION__ << "called.";
    d_->resetModelLocal(reinterpret_cast<MyFileSystemModelLocal*>(d_->mymodellocal)->oneUpPath(), d_->mymodellocal->showDot());
}

void DirsAndTaskMsgForm::onClicked_toolButton_LocalOpen() {
    qDebug() << __FUNCTION__ << "called.";
}

void DirsAndTaskMsgForm::onCurrentIndexChanged_comboBox_LocalDir(int index) {
    qDebug() << __FUNCTION__ << "called. index=" << index << ", text=" << d_->ui.comboBox_LocalDir->itemText(index);
}

void DirsAndTaskMsgForm::onDoubleClicked_treeView_LocalDir(const QModelIndex& index) {
    qDebug() << __FUNCTION__ << "called. fullpath=" << d_->mymodellocal->fullPath(index) << "isdir=" << d_->mymodellocal->isDir(index);
    if (d_->mymodellocal->isDir(index)) {
        d_->resetModelLocal(d_->mymodellocal->fullPath(index), d_->mymodellocal->showDot());
    }
}

void DirsAndTaskMsgForm::onClicked_toolButton_RemoteUp() {
    qDebug() << __FUNCTION__ << "called.";
}

void DirsAndTaskMsgForm::onClicked_toolButton_RemoteOpen() {
    qDebug() << __FUNCTION__ << "called.";
}

void DirsAndTaskMsgForm::onCurrentIndexChanged_comboBox_RemoteDir(int index) {
    qDebug() << __FUNCTION__ << "called. index=" << index << ", text=" << d_->ui.comboBox_LocalDir->itemText(index);
}

void DirsAndTaskMsgForm::onDoubleClicked_treeView_RemoteDir(const QModelIndex& index) {
    qDebug() << __FUNCTION__ << "called. QModelIndex=" << index;
}
