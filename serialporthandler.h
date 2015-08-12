#ifndef SERIALPORTHANDLER_H
#define SERIALPORTHANDLER_H

#include <QObject>
#include <QSerialPort>
#include <QVariant>
//#include "portsdata.h"
#include "emap.h"


class SerialPortHandler : public QSerialPort
{
    Q_OBJECT
    Q_PROPERTY(QString errorString READ errorString)
    Q_PROPERTY(EMap* portsMap READ getPortsMap NOTIFY portsMapChanged)

public:
    explicit SerialPortHandler(QObject *parent = 0);
    ~SerialPortHandler();

    EMap* getPortsMap() {return portsMap;}

    Q_INVOKABLE QByteArray readAll();
    Q_INVOKABLE void getPortsInfo();
    Q_INVOKABLE void loadSettings(EMap *pMap);
    Q_INVOKABLE void test();

signals:
    void portsNameChanged();
    void portsMapChanged();

public slots:
    bool openSerial();
    void closeSerial();
    void writeData(const QString &data);

private:
    EMap* portsMap;
    EMap* settingsMap;
    QVariantMap m_map;
};

#endif // SERIALPORTHANDLER_H
