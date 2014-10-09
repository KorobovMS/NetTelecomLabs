#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H
//Окно для задания ип и порта
#include <QDialog>


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
    void DataIsValid(QString Ip, QString Port);
};

#endif // CONFIGDIALOG_H
