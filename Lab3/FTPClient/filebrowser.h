#ifndef FILEBROWSER_H
#define FILEBROWSER_H

#include <QWidget>
#include <QSharedPointer>
#include <QTcpSocket>

class FileTransfer;
class FTP;

namespace Ui {
class FileBrowser;
}

class FileBrowser : public QWidget
{
    Q_OBJECT

public:
    explicit FileBrowser(QSharedPointer<FTP> ftp, QWidget *parent = 0);
    ~FileBrowser();

private slots:
    void on_pushButtonLogOut_clicked();

    void on_pushButtonhistory_clicked();

    void on_listWidgetFolders_doubleClicked(const QModelIndex &index);

    void on_listWidgetFiles_doubleClicked(const QModelIndex &index);

    void UpdateFoldersAndFiles(int code, QString response);
    void UpdateCurrentDir(int code, QString response);
    void PreUpdateFoldersAndFiles(int code, QString response);
    void OnDirChanged(int code, QString response);
    void PreUpload(int code, QString response);
    void OnNewFile(QSharedPointer<QTcpSocket>);

private:
    void UpdateAll();

private:
    Ui::FileBrowser *ui;
    QSharedPointer<FTP> ftp_;
    QString path_;
    QString filename_;
};

#endif // FILEBROWSER_H
