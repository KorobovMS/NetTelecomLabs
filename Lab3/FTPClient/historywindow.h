#ifndef HISTORYWINDOW_H
#define HISTORYWINDOW_H

#include <QDialog>

namespace Ui {
class HistoryWindow;
}

class HistoryWindow : public QDialog
{
    Q_OBJECT

public:
    explicit HistoryWindow(QWidget *parent = 0);
    ~HistoryWindow();

private:
    Ui::HistoryWindow *ui;
};

#endif // HISTORYWINDOW_H
