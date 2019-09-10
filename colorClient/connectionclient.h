#ifndef CONNECTIONCLIENT_H
#define CONNECTIONCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>

class ConnectionClient : public QObject
{
    Q_OBJECT

public:
    explicit ConnectionClient(QString ip_addr);
    ~ConnectionClient();
    void close();


public slots:
    void onReadyRead();
    void onConnect();
    void onSocketStateChanged(QAbstractSocket::SocketState socketState);
    void onError(QAbstractSocket::SocketError socketerror);
    void sendJSONMsg(QJsonObject &obj);
    void OnWritingDone(qint64 bytes);
private:
    QTcpSocket  *_socket;
    bool connected;
};

#endif // CONNECTIONCLIENT_H
