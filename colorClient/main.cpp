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

    parser.setApplicationDescription("A client to request services of HBTDisplayService");
    parser.addHelpOption();



    QCommandLineOption red(QStringList() << "r" << "red", QCoreApplication::translate("main", "red value [0-255]"),"0");
    parser.addOption(red);

    QCommandLineOption green(QStringList() << "g" << "green", QCoreApplication::translate("main", "green value [0-255]"), "0");
    parser.addOption(green);

    QCommandLineOption blue(QStringList() << "b" << "blue", QCoreApplication::translate("main", "blue value [0-255]"), "0");
    parser.addOption(blue);

    QCommandLineOption image(QStringList() << "i" << "image", QCoreApplication::translate("main", "absolute path to image file"), "path");

    parser.addOption(image);

    parser.process(a);

    QJsonObject j;

    if (parser.isSet(image))
    {
        QString imgOpt = parser.value(image);
        qDebug() << "ImgOpt :" << imgOpt;
        j["cmd"] = "IMG";
        j["path"] = imgOpt;
    }
    else if (parser.isSet(red) && parser.isSet(green) && parser.isSet(blue))
    {
        QString rOpt = parser.value(red);
        QString gOpt = parser.value(green);
        QString bOpt = parser.value(blue);
        j["cmd"] = "RGB";
        j["r"] = rOpt;
        j["g"] = gOpt;
        j["b"] = bOpt;
    }
    else
    {
        qDebug() << "Incoorect options passed, run with --help to see valid options";
        exit(-1);
    }


    ConnectionClient cc("127.0.0.1");

    cc.sendJSONMsg(j);

    return a.exec();
}
