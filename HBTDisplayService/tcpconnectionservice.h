#ifndef TCPCONNECTIONSERVICE_H
#define TCPCONNECTIONSERVICE_H

#include <QObject>

#include <QObject>
#include <QAbstractSocket>
#include <QTcpSocket>
#include <QTcpServer>
#include <QtNetwork>

class TCPConnectionService : public QObject
{
    Q_OBJECT

public:
    explicit TCPConnectionService(QObject *parent = nullptr);
    ~TCPConnectionService();

signals:
    void update(QByteArray &j);

public slots:
    void onNewConnection();
    void onSocketStateChanged(QAbstractSocket::SocketState socketState);
    void onReadyRead();
    void start();
private:
    QTcpServer  *_server = nullptr;
    QList<QTcpSocket*>  _sockets;
};


#endif // TCPCONNECTIONSERVICE_H
