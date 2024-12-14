#ifndef FFFTPGUI_UI_COMMON_ADDABLELISTWIDGET_HPP_
#define FFFTPGUI_UI_COMMON_ADDABLELISTWIDGET_HPP_

#include <QWidget>

class AddableListWidget : public QWidget {
  Q_OBJECT;

 public:
  explicit AddableListWidget(QWidget* parent = Q_NULLPTR);
  virtual ~AddableListWidget();

  void setup(const QString& title, QChar accel,
             const QString& description = QString{});
  void setData(const QStringList& data);
  const QStringList& data() const;
  void setData(const std::vector<std::wstring>& data);
  const std::vector<std::wstring>& toVectorStdWString() const;

 private:
  void updateEnabled();
  bool askData(QString& fname);
  void addData(const QString& fname);

 private Q_SLOTS:
  void onClick_pushButton_Add();
  void onClick_pushButton_Del();
  void onClick_listView();

 private:
  class Private;
  std::unique_ptr<Private> d_;
  Q_DISABLE_COPY_MOVE(AddableListWidget);
};

#endif  // FFFTPGUI_UI_COMMON_ADDABLELISTWIDGET_HPP_
