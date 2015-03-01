#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QSharedPointer>

class FTP;

namespace Ui {
class LogInWindow;
}

class LogInWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LogInWindow(QWidget *parent = 0);
    ~LogInWindow();

private:
    Ui::LogInWindow *ui;
    QSharedPointer<FTP> ftp_;

private slots:
    void on_pushButton_clicked();
    void log_in_accept_slot();
    void log_in_decline_slot();
    void OnConnect(int code, QString response);
    void OnUser(int code, QString response);
    void OnPass(int code, QString response);

signals:
    void log_in_success();
    void log_in_decline();
    void log_in_reqest(QString adress, QString username, QString password);

};

#endif // LOGINWINDOW_H
