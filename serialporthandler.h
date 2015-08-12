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
//    Q_PROPERTY(QStringList portsName READ getPortsName NOTIFY portsNameChanged)
//    Q_PROPERTY(QStringList portsDesc READ getPortsDesc)
//    Q_PROPERTY(QVariantMap map MEMBER m_map)
    Q_PROPERTY(EMap* portsMap READ getPortsMap NOTIFY portsMapChanged)
//    Q_PROPERTY(QMap<QString, QVariant> test READ getTest)
//    Q_PROPERTY(PortsData* map2 READ getTest)
//    Q_PROPERTY(QStringList baudRate READ getBaudRate CONSTANT)
//    Q_PROPERTY(QVariant test READ getTest)
//    Q_PROPERTY(MyListModel* portsName READ getListModel NOTIFY portsNameChanged)
public:
    explicit SerialPortHandler(QObject *parent = 0);
    ~SerialPortHandler();

    EMap* getPortsMap() {return portsMap;}
    QStringList getPortsName() {return portsMap->keys();}
    QStringList getPortsDesc() {return portsDesc;}
//    QStringList getBaudRate();
//    MyListModel* getListModel() {return listModel;}

    Q_INVOKABLE QByteArray readAll();
    Q_INVOKABLE void getPortsInfo();
    Q_INVOKABLE void loadSettings(EMap *pMap);
    Q_INVOKABLE void test();
//    Q_INVOKABLE QVariant getTest();
//    QMap<QString, QVariant> getTest();

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
    QStringList portsName;
    QStringList portsDesc;
//    MyListModel* listModel;
};

#endif // SERIALPORTHANDLER_H
