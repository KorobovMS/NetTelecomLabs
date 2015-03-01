#include "historywindow.h"
#include "ui_historywindow.h"

HistoryWindow::HistoryWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HistoryWindow)
{
    ui->setupUi(this);
    ui->textBrowser->append("ololo");
    ui->textBrowser->append("ne ololo");
}

HistoryWindow::~HistoryWindow()
{
    delete ui;
}
