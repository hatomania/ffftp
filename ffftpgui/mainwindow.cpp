#include "mainwindow.hpp"
#include "hostslistdialog.hpp"
#include "ffftpthread.hpp"
#include "ui_mainwindow.h"
#include "stdafx.h"

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class MainWindow::Private {
public:
    Private() {}
    ~Private() {}
    Ui::MainWindowClass ui;
    FFFTPThread* ffftpt;
};

static MainWindow* _mainwindow = nullptr;
static bool _AskSaveCryptFunc() {
    bool _r = false;
    // Qt::BlockingQueuedConnectionは、他のスレッドからinvokeMethodする場合に必要
    // see https://stackoverflow.com/questions/18725727/how-to-get-a-return-value-from-qmetaobjectinvokemethod
    QMetaObject::invokeMethod(_mainwindow, "askSaveCryptFunc", Qt::BlockingQueuedConnection, Q_RETURN_ARG(bool, _r));
    return _r;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), d_(new MainWindow::Private())
{
    d_->ui.setupUi(this);
    startTimer(500);
    emit timerEvent(nullptr);

    d_->ffftpt = new FFFTPThread(); // スレッド化するためにはコンストラクタにparentを渡してはいけない
    d_->ffftpt->moveToThread(d_->ffftpt);
    //d_->ffftpt = new FFFTPThread(this); // これはNG
    d_->ffftpt->start();

    _mainwindow = this;
    ffftp_setcallback_asksavecrypt(_AskSaveCryptFunc);
}

MainWindow::~MainWindow() {
    d_->ffftpt->terminate();
    delete d_->ffftpt;
}

void MainWindow::timerEvent(QTimerEvent* event) {
    //qDebug() << __FUNCTION__ << " called.";
    QString msg = QString::fromWCharArray(ffftp_gettaskmessage());
    if (!msg.isEmpty()) {
        d_->ui.widget->addTaskMessage(msg);
    }
    QString title = QString::fromWCharArray(ffftp_getwindowtitle());
    if (this->windowTitle() != title) {
        this->setWindowTitle(title);
    }
}

void MainWindow::connect() {
    qDebug() << __FUNCTION__ << " called.";
    HostsListDialog* d = new HostsListDialog(this);
    if (d->exec() == QDialog::Accepted) {
        qDebug() << "Accepted.";
        // このffftp_connect()は接続が成功（または失敗）するまでブロッキングする
        // GUIイベントループの中でブロッキングするのは応答なしになるのでよくないと思ったが
        // 応答なしにならない。その証拠に上のclose()でダイアログが閉じるし、
        // メインウィンドウも生きている。下記のSleep()ではちゃんと応答なしになる。不思議。
        // libffftpの中で何かしているのだろうがWindows固有なのかもしれない
        // 将来クロスプラットフォーム化を考えるとちゃんとスレッド化したほうがいいと思う
        //     →一応スレッド化した
        //qDebug() << __FUNCTION__ << "QThread::sleep(10) start.";
        //QThread::sleep(10);
        //qDebug() << __FUNCTION__ << "returned.";
        if (int idx = d->connectingHostIndex(); idx >= 0) {
            qDebug() << __FUNCTION__ << "ffftp_connect() started. index=" << idx;
            //ffftp_connect(idx);
            QMetaObject::invokeMethod(d_->ffftpt, "connect", Qt::QueuedConnection, Q_ARG(int, idx));
            qDebug() << __FUNCTION__ << "returned.";
        }
    }
    delete d;
}

bool MainWindow::askSaveCryptFunc() {
    if (QMessageBox::question(this, kAskSaveCryptTitle, kAskSaveCryptBody) == QMessageBox::Yes)
        return true;
    return false;
}
