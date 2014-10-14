#ifndef REQTODLDIALOG_H
#define REQTODLDIALOG_H

#include <QDialog>
#include <QHostAddress>

namespace Ui {
class RequestToDownloadDialog;
}

class RequestToDownloadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RequestToDownloadDialog(QWidget *parent = 0);
    ~RequestToDownloadDialog();

private:
    Ui::RequestToDownloadDialog *ui;
    QHostAddress host_addr_;
    QHostAddress addr_;
    quint16 port_;
    QString filename_;
    quint64 filesize_;
    quint32 id_;

signals:
    void Accept(QHostAddress host_addr, QHostAddress addr, quint16 port, QString filename,
                quint64 filesize, quint32 id);
    void Decline();

public slots:
    void RxDataFromMain(QHostAddress host_addr, QHostAddress addr, quint16 port, QString filename,
                   quint64 filesize, quint32 id);

private slots:
    void on_pushButtonAccept_clicked();
    void on_pushButtonDecline_clicked();
};


#endif // REQTODLDIALOG_H
