#ifndef MYWIDGET_H
#define MYWIDGET_H
#include <QWidget>
#include <QPixmap>
#include <QLabel>

#include "tcpconnectionservice.h"

class myWidget : public QWidget
{
    Q_OBJECT
public:
    explicit myWidget(QWidget *parent = nullptr);

signals:

public slots:
    void ReqHandler(QByteArray &bytes);

private:
    TCPConnectionService cc;
    void RGBUpdate(QJsonObject &obj);
    void ImageUpdate(QJsonObject &ob);
    QLabel *lbl_;
};

#endif // MYWIDGET_H
