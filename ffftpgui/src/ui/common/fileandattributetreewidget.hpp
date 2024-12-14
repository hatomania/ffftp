#ifndef FFFTPGUI_UI_COMMON_FILEANDATTRIBUTETREEWIDGET_HPP_
#define FFFTPGUI_UI_COMMON_FILEANDATTRIBUTETREEWIDGET_HPP_

#include "addabletreewidget.hpp"

class FileAndAttributeTreeWidget : public AddableTreeWidget {
  Q_OBJECT;

 public:
  explicit FileAndAttributeTreeWidget(QWidget* parent = Q_NULLPTR);
  virtual ~FileAndAttributeTreeWidget();

 protected:
  bool askRowData(std::vector<std::wstring>& row_data) const override;

 private:
  class Private;
  std::unique_ptr<Private> d_;
  Q_DISABLE_COPY_MOVE(FileAndAttributeTreeWidget);
};

#endif  // FFFTPGUI_UI_COMMON_FILEANDATTRIBUTETREEWIDGET_HPP_
