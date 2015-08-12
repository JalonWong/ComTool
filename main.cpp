#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "serialporthandler.h"
#include "listmodel.h"
#include "emap.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator myappTranslator;
    if((myappTranslator.load("comtool_" + QLocale::system().name(), ":/i18n"))) {
        app.installTranslator(&myappTranslator);
        qDebug(QObject::tr("Translator test").toUtf8());
    } else {
        qCritical(QObject::tr("failed to load i18n qm file !").toUtf8());
    }

    qmlRegisterType<SerialPortHandler>("io.jalon.SerialPort", 1, 0, "SerialPort");
    qmlRegisterType<EMap>("io.jalon", 1, 0, "EMap");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
