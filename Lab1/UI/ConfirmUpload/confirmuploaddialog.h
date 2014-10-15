#ifndef REQTODLDIALOG_H
#define REQTODLDIALOG_H

#include <QDialog>
#include <QHostAddress>

namespace Ui {
class ConfirmUploadDialog;
}

class ConfirmUploadDialog : public QDialog
{
    Q_OBJECT

public:
    ConfirmUploadDialog(QHostAddress ip, quint16 port,
                        QString filename, quint64 filesize, quint32 id,
                        QWidget* parent = 0);
    ~ConfirmUploadDialog();

signals:
    void Accept(quint32 id);
    void Decline(quint32 id);

private:
    Ui::ConfirmUploadDialog* ui_;
    quint32 id_;

private slots:
    void on_pushButtonAccept_clicked();
    void on_pushButtonDecline_clicked();
};


#endif // REQTODLDIALOG_H
