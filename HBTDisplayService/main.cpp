#include <QApplication>
#include "mywidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    myWidget w;
    w.showFullScreen();
    return a.exec();
}
