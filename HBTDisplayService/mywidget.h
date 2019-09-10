#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include "tcpconnectionservice.h"

class myWidget : public QWidget
{
    Q_OBJECT
public:
    explicit myWidget(QWidget *parent = nullptr);

signals:

public slots:
    void bgRGBUpdate(QByteArray &bytes);

private:
    TCPConnectionService cc;
};

#endif // MYWIDGET_H
