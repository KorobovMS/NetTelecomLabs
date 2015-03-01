#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "email.h"

class POP3Client;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void connectEverything();

private slots:
    void OnConnect(QString welcome);
    void OnUser(bool ok);
    void OnPass(bool ok);
    void OnStat(int message_number, int octets);
    void OnList(bool ok, QHash<int, int> messages);
    void OnRetr(bool ok, Email email);
    void OnDele(bool ok);
    void OnNoop();
    void OnRset();
    void OnQuit();

private:
    POP3Client* pop_;
};

#endif // MAINWINDOW_H
