#ifndef FFFTPGUI_UI_HOST_HOSTQUICKDIALOG_HPP_
#define FFFTPGUI_UI_HOST_HOSTQUICKDIALOG_HPP_

#include <QDialog>

class HostQuickDialog : public QDialog {
  Q_OBJECT;

 public:
  struct Data {
    QStringList history;
		QString hostname;
		QString username;
		QString password;
		bool use_firewall;
		bool use_passive;
    Data();
    Data(
      const QStringList& history,
      const QString username,
      const QString password,
      bool use_firewall,
      bool use_passive);
  };
  explicit HostQuickDialog(const Data& data, QWidget* parent = Q_NULLPTR);
  virtual ~HostQuickDialog();
  const Data& data() const;

 private:
  class Private;
  std::unique_ptr<Private> d_;
  Q_DISABLE_COPY_MOVE(HostQuickDialog);
};

#endif  // FFFTPGUI_UI_HOST_HOSTQUICKDIALOG_HPP_
