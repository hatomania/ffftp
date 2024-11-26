#include "hostsettingspecialform.hpp"
#include "ui_hostsettingspecialform.h"
#include "stdafx.h"

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class HostSettingSpecialForm::Private {
public:
    Private() {}
    ~Private() {}
    Ui::HostSettingSpecialForm ui;
    HostSettingSpecialForm::Data data;
};

HostSettingSpecialForm::Data::Data() {}

HostSettingSpecialForm::HostSettingSpecialForm(QWidget* parent)
    : QWidget(parent), d_(new HostSettingSpecialForm::Private())
{
    d_->ui.setupUi(this);
}

void HostSettingSpecialForm::setData(const Data& data) const {
}

const HostSettingSpecialForm::Data& HostSettingSpecialForm::getData() const {
//    static Data data;
    return d_->data;
}

void HostSettingSpecialForm::setDataAsDefault() const {
    this->setData(Data());
}
