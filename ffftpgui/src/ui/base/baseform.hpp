#ifndef FFFTPGUI_UI_BASE_BASEFORM_HPP_
#define FFFTPGUI_UI_BASE_BASEFORM_HPP_

#include <memory>

#include <QWidget>

class BaseForm : public QWidget {
  Q_OBJECT

 public:
  struct Data {
    Data();
  };

  BaseForm() = delete;
  BaseForm(Data* data, QWidget* parent = Q_NULLPTR);
  virtual ~BaseForm();

  void setData(const Data& data);
  const Data& data() const;
  virtual int helpID() const = 0;

 protected:
  std::unique_ptr<BaseForm::Data> data_;

  virtual void setRawData(const Data& data) = 0;
  const Data& rawData() const;
  virtual void updateUi(const Data& data) = 0;
  virtual void updateData(Data& data) const = 0;

 private:
  Q_DISABLE_COPY(BaseForm)
};

#endif  // FFFTPGUI_UI_BASE_BASEFORM_HPP_
