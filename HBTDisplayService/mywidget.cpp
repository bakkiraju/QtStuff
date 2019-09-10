#include "mywidget.h"

myWidget::myWidget(QWidget *parent) : QWidget(parent)
{
    cc.start();
    connect(&cc,SIGNAL(update(QByteArray &)), this, SLOT(bgRGBUpdate(QByteArray &)));
}

void myWidget::bgRGBUpdate(QByteArray &bytes)
{
    qDebug() << "Updating background color";
    QJsonDocument doc = QJsonDocument::fromJson(bytes);
    QJsonObject obj = doc.object();

    qDebug() << obj["r"].toString() << endl;
    qDebug() << obj["g"].toString() << endl;
    qDebug() << obj["b"].toString() << endl;

    int r = obj["r"].toString().toInt();
    int g = obj["g"].toString().toInt();
    int b = obj["b"].toString().toInt();

    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(r,g,b));
    setPalette(pal);
}
