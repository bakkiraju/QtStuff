#include <QApplication>
#include "mywidget.h"
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    myWidget w;
    QList<QScreen *> sList = QApplication::screens();

    for (QScreen *s : sList)
    {
        qDebug() << "Size: " << s->availableSize();
        qDebug() << "Depth: " << s->depth();
        qDebug() << "Geomtry: " << s->geometry();
    }

    w.showFullScreen();
    return a.exec();
}
