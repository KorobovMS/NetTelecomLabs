#ifndef REQTODLDIALOG_H
#define REQTODLDIALOG_H
//окно запроса на сохранение входящего файла
#include <QDialog>

namespace Ui {
class ReqToDLdialog;
}

class ReqToDLdialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReqToDLdialog(QWidget *parent = 0);
    ~ReqToDLdialog();

private:
    Ui::ReqToDLdialog *ui;

signals:
    void Accept();
    void Decline();

public slots:
    //RxDataFromMain(QString Filename, QString Ip, QString Port);

private slots:
    void on_pushButtonAccept_clicked();
    void on_pushButtonDecline_clicked();
};


#endif // REQTODLDIALOG_H
