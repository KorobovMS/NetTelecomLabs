#ifndef SENDPROGRESSDIALOG_H
#define SENDPROGRESSDIALOG_H

#include <QDialog>
#include <QHostAddress>
#include <QString>

namespace Ui {
class SendProgressDialog;
}

class SendProgressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SendProgressDialog(QHostAddress ip, quint16 port,
                                QString filename, QWidget* parent = 0);
    ~SendProgressDialog();

private slots:
    void on_pushButtonCancel_clicked();

public slots:
    void Progress(int bytes_sent, int bytes_total);

signals:

private:
    Ui::SendProgressDialog *ui_;
};

#endif // SENDPROGRESSDIALOG_H
