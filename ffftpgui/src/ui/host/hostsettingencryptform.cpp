#include "hostsettingencryptform.hpp"
#include "ui_hostsettingencryptform.h"
#include "stdafx.h"

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class HostSettingEncryptForm::Private {
public:
    Private() {}
    ~Private() {}
    Ui::HostSettingEncryptForm ui;
    HostSettingEncryptForm::Data data;
};

HostSettingEncryptForm::Data::Data() {}

HostSettingEncryptForm::HostSettingEncryptForm(QWidget* parent)
    : QWidget(parent), d_(new HostSettingEncryptForm::Private())
{
    d_->ui.setupUi(this);
}

void HostSettingEncryptForm::setData(const Data& data) const {
}

const HostSettingEncryptForm::Data& HostSettingEncryptForm::getData() const {
//    static Data data;
    return d_->data;
}

void HostSettingEncryptForm::setDataAsDefault() const {
    this->setData(Data());
}
