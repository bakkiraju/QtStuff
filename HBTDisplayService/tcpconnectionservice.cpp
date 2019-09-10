#include "tcpconnectionservice.h"

#include "tcpconnectionservice.h"

TCPConnectionService::TCPConnectionService(QObject *parent)
{
     _server = new QTcpServer(this);
     connect(_server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

void TCPConnectionService::start()
{
    if (not _server->listen(QHostAddress::Any, 64242))
    {
        qDebug() << "Failed to launch the server";
        exit(EXIT_FAILURE);
    }
    qDebug() << "TCP Server started" << endl;
}

TCPConnectionService::~TCPConnectionService()
{
}

void TCPConnectionService::onNewConnection()
{
   QTcpSocket *clientSocket = _server->nextPendingConnection();
   connect(clientSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
   connect(clientSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onSocketStateChanged(QAbstractSocket::SocketState)));

   qDebug() << "Accepted new connection" << endl;

    _sockets.push_back(clientSocket);
    for (QTcpSocket* socket : _sockets) {
        socket->write(QByteArray::fromStdString(clientSocket->peerAddress().toString().toStdString() + " connected to server !\n"));
    }
}

void TCPConnectionService::onSocketStateChanged(QAbstractSocket::SocketState socketState)
{
    if (socketState == QAbstractSocket::UnconnectedState)
    {
        QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
        qDebug() << "Removing a client peer that got disconnected" << endl;
        _sockets.removeOne(sender);
    }
}

void TCPConnectionService::onReadyRead()
{
    QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
    QByteArray datas = sender->readAll();

    update(datas);

    for (QTcpSocket* socket : _sockets) {
        if (socket != sender)
            socket->write(QByteArray::fromStdString(sender->peerAddress().toString().toStdString() + ": " + datas.toStdString()));
    }
}
