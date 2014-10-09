#ifndef SENDDIALOG_H
#define SENDDIALOG_H
//окно выбора пути и адреса отправляемого файла
#include <QDialog>

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
    /*
    QString dest_file;
    QString dest_ip;
    QString dest_port;
    QString dest_progr;
    */

private slots:
    void on_toolButtonFile_clicked();
    void on_pushButtonOk_clicked();
    void on_pushButtonCancel_clicked();

signals:
    void TxDataToProgrDialog(QString DestIp, QString DestPort, QString DestFile); //отправляем данные в главное окно

};



#endif // SENDDIALOG_H
