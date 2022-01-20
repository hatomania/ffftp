#pragma once

#include <QtWidgets/QWidget>

class DirsAndTaskMsgForm : public QWidget
{
    Q_OBJECT

public:
    explicit DirsAndTaskMsgForm(QWidget *parent = Q_NULLPTR);
    void setTaskMessage(const QString& msg) const;
    void addTaskMessage(const QString& msg) const;
    void setDotFileShown(bool isshown);

private slots:

private:
    class Private;
    Private* d_;
    Q_DISABLE_COPY(DirsAndTaskMsgForm)
};
