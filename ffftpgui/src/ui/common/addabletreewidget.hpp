#ifndef FFFTPGUI_UI_COMMON_ADDABLETREEWIDGET_HPP_
#define FFFTPGUI_UI_COMMON_ADDABLETREEWIDGET_HPP_

#include <QWidget>

class AddableTreeWidget : public QWidget {
  Q_OBJECT;

 public:
  explicit AddableTreeWidget(QWidget* parent = Q_NULLPTR);
  virtual ~AddableTreeWidget();

  void setup(const QString& title,
             QChar accel,
             const QStringList& headers = QStringList(),
             const QString& description = QString{});
  void setData(const std::vector<std::vector<std::wstring>>& data);
  void addData(const std::vector<std::wstring>& data);
  const std::vector<std::vector<std::wstring>>& data() const;

 protected:
  virtual bool askRowData(std::vector<std::wstring>& row_data) const = 0;

 private:
  void updateEnabled();

 private Q_SLOTS:
  void onClick_pushButton_Add();
  void onClick_pushButton_Del();
  void onClick_treeView();

 private:
  class Private;
  std::unique_ptr<Private> d_;
  Q_DISABLE_COPY_MOVE(AddableTreeWidget);
};

#endif  // FFFTPGUI_UI_COMMON_ADDABLETREEWIDGET_HPP_
