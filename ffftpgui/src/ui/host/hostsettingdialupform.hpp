#pragma once

#include <QtWidgets/QWidget>

class HostSettingDialupForm : public QWidget
{
    Q_OBJECT

public:
    struct Data {
        bool use_dialup;
        int dial_entry;
        bool redial;
        bool confirm_redial;
        Data();
    };
    explicit HostSettingDialupForm(QWidget *parent = Q_NULLPTR);
    void setData(const Data& data) const;
    const Data& getData() const;
    void setDataAsDefault() const;

private slots:

private:
    class Private;
    Private* d_;
    Q_DISABLE_COPY(HostSettingDialupForm)
};
