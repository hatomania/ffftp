#ifndef FFFTPGUI_UI_HOST_HOSTTREEVIEW_HPP_
#define FFFTPGUI_UI_HOST_HOSTTREEVIEW_HPP_

#include <QTreeView>

#include "ffftp.h"

class HostTreeView : public QTreeView {
  Q_OBJECT;

 public:
  explicit HostTreeView(QWidget* parent = Q_NULLPTR);
  virtual ~HostTreeView();

  void update() const;
  const hostcontext_t currentHostContext() const;
  void setCurrentIndex(const hostcontext_t hc);

 private:
  Q_DISABLE_COPY_MOVE(HostTreeView);
};

#endif  // FFFTPGUI_UI_HOST_HOSTTREEVIEW_HPP_
