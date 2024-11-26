#include "hostsettingdialupform.hpp"
#include "ui_hostsettingdialupform.h"
#include "stdafx.h"

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class HostSettingDialupForm::Private {
public:
    Private() {}
    ~Private() {}
    Ui::HostSettingDialupForm ui;
    HostSettingDialupForm::Data data;
};

HostSettingDialupForm::Data::Data() {}

HostSettingDialupForm::HostSettingDialupForm(QWidget* parent)
    : QWidget(parent), d_(new HostSettingDialupForm::Private())
{
    d_->ui.setupUi(this);
}

void HostSettingDialupForm::setData(const Data& data) const {
}

const HostSettingDialupForm::Data& HostSettingDialupForm::getData() const {
//    static Data data;
    return d_->data;
}

void HostSettingDialupForm::setDataAsDefault() const {
    this->setData(Data());
}
