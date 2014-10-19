#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QHostAddress>

#include "settings.h"

namespace Ui {
class ConfigDialog;
}

class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigDialog(QWidget* parent = 0);
    ~ConfigDialog();

signals:
    void DataIsValid(QHostAddress ip, quint16 port);

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::ConfigDialog* ui_;
    Settings s_;
};

#endif // CONFIGDIALOG_H
