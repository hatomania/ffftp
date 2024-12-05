#include "baseform.hpp"

#include <memory>

BaseForm::Data::Data() {}

BaseForm::BaseForm(Data* data, QWidget* parent)
    : QWidget(parent), data_(data) {}
BaseForm::~BaseForm() {}

void BaseForm::setData(const Data& data) {
  setRawData(data);
  updateUi(*data_);
}
const BaseForm::Data& BaseForm::data() const {
  updateData(*data_);
  return *data_;
}
const BaseForm::Data& BaseForm::rawData() const { return *data_; }
