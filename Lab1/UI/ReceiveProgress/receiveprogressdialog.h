#ifndef RECIEVEPROGRESSDIALOG_H
#define RECIEVEPROGRESSDIALOG_H

#include <QDialog>
#include <QHostAddress>
#include <QString>

namespace Ui {
class ReceiveProgressDialog;
}

class ReceiveProgressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReceiveProgressDialog(QHostAddress addr, quint16 port,
                                   QString name, QWidget* parent = 0);
    ~ReceiveProgressDialog();

public slots:
    void Progress(int r, int t);

private slots:
    void on_pushButtonCancel_clicked();

private:
    Ui::ReceiveProgressDialog* ui_;
};

#endif // RECIEVEPROGRESSDIALOG_H
