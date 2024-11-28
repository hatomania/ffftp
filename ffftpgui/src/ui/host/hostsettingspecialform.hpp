#pragma once

#include <QtWidgets/QWidget>

class HostSettingSpecialForm : public QWidget
{
    Q_OBJECT

public:
    struct Data {
        int max_connection;
        bool reuse_main_socket;
        bool ignore_PASV_addr;
        int keep_connection_freq;
        int proc_when_error;
        bool reconnect_after_error;
        Data();
    };
    explicit HostSettingSpecialForm(QWidget *parent = Q_NULLPTR);
    void setData(const Data& data) const;
    const Data& getData() const;
    void setDataAsDefault() const;

private slots:

private:
    class Private;
    Private* d_;
    Q_DISABLE_COPY(HostSettingSpecialForm)
};
