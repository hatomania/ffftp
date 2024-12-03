#pragma once

#include <QtWidgets/QWidget>

class HostSettingEncryptForm : public QWidget {
  Q_OBJECT

 public:
  struct Data {
    bool allow_without_encrypt;
    bool is_ftps_explicit;
    bool is_ftps_implicit;
    Data();
  };
  explicit HostSettingEncryptForm(QWidget* parent = Q_NULLPTR);
  void setData(const Data& data) const;
  const Data& getData() const;
  void setDataAsDefault() const;

 private slots:

 private:
  class Private;
  Private* d_;
  Q_DISABLE_COPY(HostSettingEncryptForm)
};
