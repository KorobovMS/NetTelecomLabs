#include <QApplication>
#include "loginwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LogInWindow wnd;
    wnd.show();
    return a.exec();
}
