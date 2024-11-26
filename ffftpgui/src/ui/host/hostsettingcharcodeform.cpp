#include "hostsettingcharcodeform.hpp"
#include "ui_hostsettingcharcodeform.h"
#include "stdafx.h"

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class HostSettingCharCodeForm::Private {
public:
    Private() {}
    ~Private() {}
    Ui::HostSettingCharCodeForm ui;
    HostSettingCharCodeForm::Data data;
};

HostSettingCharCodeForm::Data::Data() {}

HostSettingCharCodeForm::HostSettingCharCodeForm(QWidget* parent)
    : QWidget(parent), d_(new HostSettingCharCodeForm::Private())
{
    d_->ui.setupUi(this);
}

void HostSettingCharCodeForm::setData(const Data& data) const {
}

const HostSettingCharCodeForm::Data& HostSettingCharCodeForm::getData() const {
//    static Data data;
    return d_->data;
}

void HostSettingCharCodeForm::setDataAsDefault() const {
    this->setData(Data());
}
