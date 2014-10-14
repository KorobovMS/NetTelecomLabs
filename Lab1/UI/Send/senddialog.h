#ifndef SENDDIALOG_H
#define SENDDIALOG_H

#include <QDialog>
#include <QHostAddress>

namespace Ui {
class SendDialog;
}

class SendDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SendDialog(QWidget *parent = 0);
    ~SendDialog();

private:
    Ui::SendDialog *ui;

private slots:
    void on_toolButtonFile_clicked();
    void on_pushButtonOk_clicked();
    void on_pushButtonCancel_clicked();

signals:
    void TxDataToProgrDialog(QHostAddress DestIp, quint16 DestPort, QString DestFile);
};

#endif // SENDDIALOG_H
