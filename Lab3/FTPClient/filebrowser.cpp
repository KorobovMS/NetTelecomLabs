#include "filebrowser.h"
#include "loginwindow.h"
#include "historywindow.h"
#include "ui_filebrowser.h"
#include "QListWidgetItem"
#include <QFileDialog>
#include <QThread>
#include "ftp.h"
#include "filetransfer.h"
#include <QProgressBar>

FileBrowser::FileBrowser(QSharedPointer<FTP> ftp, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileBrowser),
    ftp_(ftp)
{
    ui->setupUi(this);
    UpdateAll();
}

FileBrowser::~FileBrowser()
{
    delete ui;
}

void FileBrowser::on_pushButtonLogOut_clicked()
{
    disconnect(ftp_.data(), 0, 0, 0);
    ftp_->Quit();
    this->close();
    LogInWindow* L = new LogInWindow;
    L->show();
}

void FileBrowser::on_pushButtonhistory_clicked()
{
    HistoryWindow* H = new HistoryWindow;
    H->show();
}

///////////////////////////////////////////////////////////
void FileBrowser::on_listWidgetFolders_doubleClicked(const QModelIndex &index)
{
    QString folder = ui->listWidgetFolders->item(index.row())->text();
    disconnect(ftp_.data(), 0, 0, 0);
    connect(ftp_.data(), SIGNAL(Done(int,QString)),
            this, SLOT(OnDirChanged(int,QString)));
    ftp_->Cwd(folder);
}

void FileBrowser::OnDirChanged(int code, QString response)
{
    qDebug() << "CWD" << code << response;
    UpdateAll();
}

///////////////////////////////////////////////////////////
void FileBrowser::UpdateAll()
{
    disconnect(ftp_.data(), 0, 0, 0);
    connect(ftp_.data(), SIGNAL(Done(int,QString)),
            this, SLOT(UpdateCurrentDir(int,QString)));
    ftp_->Pwd();
}

void FileBrowser::UpdateCurrentDir(int code, QString response)
{
    qDebug() << "PWD" << code << response;
    int first = response.indexOf("\"") + 1;
    int last = response.indexOf("\"", first);
    QString dir = response.mid(first, last - first);
    ui->lineEditCurrentFolder->setText(dir);
    disconnect(ftp_.data(), 0, 0, 0);
    connect(ftp_.data(), SIGNAL(Done(int,QString)),
            this, SLOT(PreUpdateFoldersAndFiles(int,QString)));
    ftp_->Pasv();
}

void FileBrowser::PreUpdateFoldersAndFiles(int code, QString response)
{
    qDebug() << "PASV" << code << response;
    disconnect(ftp_.data(), 0, 0, 0);
    connect(ftp_.data(), SIGNAL(Done(int,QString)),
            this, SLOT(UpdateFoldersAndFiles(int,QString)));
    ftp_->Mlsd();
}

void FileBrowser::UpdateFoldersAndFiles(int code, QString response)
{
    static const QString kSpace = " ";
    static const QString kType = "type=";
    qDebug() << "MLSD" << code << response;

    ui->listWidgetFiles->clear();
    ui->listWidgetFolders->clear();

    QTextStream stream(&response, QIODevice::ReadOnly);
    if (ui->lineEditCurrentFolder->text() != "/")
    {
        ui->listWidgetFolders->addItem("..");
    }
    while (!stream.atEnd())
    {
        QString line = stream.readLine();
        QString name = line.mid(line.indexOf(kSpace) + 1);
        QChar entity = line[line.indexOf(kType) + kType.length()];
        if (entity == 'd')
        {
            ui->listWidgetFolders->addItem(name);
        }
        else if (entity == 'f')
        {
            ui->listWidgetFiles->addItem(name);
        }
    }
}

///////////////////////////////////////////////////////////
void FileBrowser::on_listWidgetFiles_doubleClicked(const QModelIndex &index)
{
    filename_ = ui->listWidgetFiles->item(index.row())->text();
    path_ = QFileDialog::getSaveFileName(this, "Where to save");
    disconnect(ftp_.data(), 0, 0, 0);
    connect(ftp_.data(), SIGNAL(Done(int,QString)),
            this, SLOT(PreUpload(int,QString)));
    ftp_->Pasv();
}

void FileBrowser::PreUpload(int code, QString response)
{
    disconnect(ftp_.data(), 0, 0, 0);
    connect(ftp_.data(), SIGNAL(NewFile(QSharedPointer<QTcpSocket>)),
            this, SLOT(OnNewFile(QSharedPointer<QTcpSocket>)));
    ftp_->Retrieve(filename_, path_);
}

void FileBrowser::OnNewFile(QSharedPointer<QTcpSocket> sock)
{
    QThread* thread = new QThread;
    QProgressBar* progress = new QProgressBar;
    FileTransfer* ft = new FileTransfer(sock, path_, 100);
    progress->setMaximum(100);

    connect(thread, SIGNAL(started()),
            ft, SLOT(Start()));

    connect(ft, SIGNAL(StartReceiving()),
            progress, SLOT(show()));
    connect(ft, SIGNAL(Percent(int)),
            progress, SLOT(setValue(int)));

    connect(ft, SIGNAL(EndReceiving()),
            thread, SLOT(quit()));
    connect(thread, SIGNAL(finished()),
            ft, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()),
            thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()),
            progress, SLOT(close()));
    connect(thread, SIGNAL(finished()),
            progress, SLOT(deleteLater()));

    thread->start();
}
