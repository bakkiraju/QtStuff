#include "connectionclient.h"

#include <QDebug>
#include <QHostAddress>
#include <QJsonDocument>
#include <QThread>

ConnectionClient::ConnectionClient(QString ip_addr)
{
    _socket = new QTcpSocket(this);
    qDebug() << "Connecting to the server" <<endl;
    _socket->connectToHost(QHostAddress(ip_addr), 64242);

    connect(_socket, SIGNAL(connected()), this, SLOT(onConnect()));
    connect(_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(_socket, SIGNAL(bytesWritten(qint64)), this, SLOT(OnWritingDone(qint64)));
}

void ConnectionClient :: sendJSONMsg(QJsonObject &j)
{
    while(!connected) {
        qDebug() << "Waiting to connect to server" << endl; QThread::msleep(1000);
    }
    // serialize to byte array
    QJsonDocument doc(j);
    QByteArray bytes = doc.toJson();
    _socket->write(bytes);
}

void ConnectionClient :: OnWritingDone(qint64 bytes)
{
   qDebug() << "Writing done" << endl;
   exit(0);
}

ConnectionClient::~ConnectionClient()
{
}

void ConnectionClient :: onError(QAbstractSocket::SocketError error)
{
    qDebug() << "Socket Error : " << error << endl;
}

void ConnectionClient::close()
{
    qDebug() << "Closing the client" << endl;
    _socket->close();
}

void ConnectionClient::onReadyRead()
{
    QByteArray datas = _socket->readAll();
    qDebug() << "Read back: " << datas;
 //   _socket->write(QByteArray("ok !\n"));
}

void ConnectionClient :: onSocketStateChanged(QAbstractSocket::SocketState socketState)
{
    qDebug() << "state changed :" << socketState;
}

void ConnectionClient::onConnect()
{
    qDebug() << "Successfully connected" << endl;
    connected = true;
}
