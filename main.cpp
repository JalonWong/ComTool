#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "serialporthandler.h"
#include "listmodel.h"
#include "emap.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

//    QTranslator qtTranslator;
//    qtTranslator.load("qt_" + QLocale::system().name(),
//                QLibraryInfo::location(QLibraryInfo::TranslationsPath));
//    app.installTranslator(&qtTranslator);

    QTranslator myappTranslator;
    if((myappTranslator.load("comtool_" + QLocale::system().name(),
                             ":/i18n"))) {
        app.installTranslator(&myappTranslator);
//        qDebug(QObject::tr("test").toUtf8());
    } else {
        qCritical("failed to load i18n qm file !");
    }

    qmlRegisterType<SerialPortHandler>("io.jalon.SerialPort", 1, 0, "SerialPort");
//    qmlRegisterType<MyListModel>("io.jalon.SerialPort", 1, 0, "MyListModel");
//    qmlRegisterType<PortsData>("io.jalon.SerialPort", 1, 0, "PortsData");
    qmlRegisterType<EMap>("io.jalon", 1, 0, "EMap");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

//    QQuickWindow

    return app.exec();
}
