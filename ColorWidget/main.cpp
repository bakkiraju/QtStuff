#include "widget.h"
#include <QApplication>
#include <iostream>

void usage()
{
    std::cout << "Usage: colorWindow red green blue" << std::endl;
    exit(1);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    if (argc !=4)
    {
        usage();
    }

    int r = atoi(argv[1]);
    int g = atoi(argv[2]);
    int b = atoi(argv[3]);

    std::cout << "r:" << r << std::endl;
    std::cout << "g:" << g << std::endl;
    std::cout << "b:" << b << std::endl;

    w.setWindowFlags( Qt::SplashScreen );
    //w.setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
    QString style = QString("background-color: rgb(%1,%2,%3)").arg(r).arg(g).arg(b);
    std::cout << "style:" << style.toStdString() << std::endl;
    w.setStyleSheet(style);
    w.showFullScreen();
    return a.exec();
}
