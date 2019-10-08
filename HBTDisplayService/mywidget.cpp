#include "mywidget.h"

#include <QHBoxLayout>

myWidget::myWidget(QWidget *parent) : QWidget(parent)
{

    cc.start();
    connect(&cc,SIGNAL(update(QByteArray &)), this, SLOT(ReqHandler(QByteArray &)));
    lbl_ = new QLabel();
}

void myWidget::ReqHandler(QByteArray &bytes)
{
    lbl_->hide();
    QJsonDocument doc = QJsonDocument::fromJson(bytes);
    QJsonObject obj = doc.object();

    if (obj["cmd"] == "RGB")
        RGBUpdate(obj);

    if (obj["cmd"] == "IMG")
        ImageUpdate(obj);
}

void myWidget::RGBUpdate(QJsonObject &obj)
{
    qDebug() << "Updating background color";

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


void myWidget::ImageUpdate(QJsonObject &obj)
{
    qDebug() << "Updating background image : " << obj["path"].toString();
    //QString ss = QString("background-image: url(%1)").arg(obj["path"].toString());


    QPixmap pix;
    /** to check wether load ok */
    if(pix.load(obj["path"].toString())){
        lbl_->setGeometry(0,0,this->width(), this->height());
        /** scale pixmap to fit in label'size and keep ratio of pixmap */
        pix = pix.scaled(lbl_->size(),Qt::KeepAspectRatio);
        lbl_->setPixmap(pix);
        qDebug() << "Label displayed";
        lbl_->show();
    }
}

