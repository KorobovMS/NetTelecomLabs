#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QHostAddress>

namespace Ui {
class ConfigDialog;
}

class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigDialog(QWidget *parent = 0);
    ~ConfigDialog();

private slots:
    void on_pushButtonOk_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::ConfigDialog *ui;

signals:
    void DataIsValid(QHostAddress Ip, quint16 Port);
};

#endif // CONFIGDIALOG_H
