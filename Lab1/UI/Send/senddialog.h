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
    explicit SendDialog(QWidget* parent = 0);
    ~SendDialog();

private slots:
    void on_toolButtonFile_clicked();
    void on_pushButtonOk_clicked();
    void on_pushButtonCancel_clicked();
    void TransmissionCancelled();

private:
    Ui::SendDialog *ui_;
};

#endif // SENDDIALOG_H
