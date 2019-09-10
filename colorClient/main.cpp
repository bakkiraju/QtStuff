#include <QCoreApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QtCore/QObject>
#include <QJsonObject>

#include <QtNetwork/QTcpSocket>
#include <QUrl>

#include <QDebug>
#include <QHostAddress>
#include <QAbstractSocket>

#include <connectionclient.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QCommandLineParser parser;

    parser.setApplicationDescription("ColorWidget : A fullscreen solid color window server");
    parser.addHelpOption();

    QCommandLineOption red(QStringList() << "r" << "red", QCoreApplication::translate("main", "red value [0-255]"),"0");
    parser.addOption(red);


    QCommandLineOption green(QStringList() << "g" << "green", QCoreApplication::translate("main", "green value [0-255]"), "0");
    parser.addOption(green);


    QCommandLineOption blue(QStringList() << "b" << "blue", QCoreApplication::translate("main", "blue value [0-255]"), "0");
    parser.addOption(blue);

    parser.process(a);

    QString rOpt = parser.value(red);
    QString gOpt = parser.value(green);
    QString bOpt = parser.value(blue);

    //qDebug() << rOpt << " " << gOpt << " " << bOpt << endl;

    ConnectionClient cc("127.0.0.1");

    QJsonObject j;

    j["r"] = rOpt;
    j["g"] = gOpt;
    j["b"] = bOpt;

    cc.sendJSONMsg(j);

    return a.exec();
}
