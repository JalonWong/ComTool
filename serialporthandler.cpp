#include <QMessageBox>
#include <QSerialPortInfo>
#include "serialporthandler.h"
#include <QDebug>

static const char blankString[] = "N/A";

SerialPortHandler::SerialPortHandler(QObject *parent)
    : QSerialPort(parent)
    , portsMap(new EMap)
{
//    connect(this, SIGNAL(readyRead()), this, SLOT(readData()));
//    portsName << "COM21" << "COM22";
//    portsDesc << "dd21" << "dd22";
//    listModel = new MyListModel;
//
//    m_map.insert("text", "tt1");
//    qDebug() << "text" << m_map.values("text").count();
}

SerialPortHandler::~SerialPortHandler()
{
    closeSerial();
}

//QList<QVariantMap> SerialPortHandler::getTest1()
//{
//    QList<QVariantMap> list;
//    QVariantMap map;
//    map.insert("text","t1");
//    map.insert("data","d1");
//    list.append(map);
//    map.clear();
//    map.insert("text","t2");
//    map.insert("data","d2");
//    list.append(map);
//    return list;
//}

bool SerialPortHandler::openSerial()
{
    if(settingsMap) {
        setPortName(settingsMap->value("COM").toString());
        setBaudRate(settingsMap->value("BaudRate").toInt());
        setDataBits((DataBits)settingsMap->value("DataBits").toInt());
        setParity((Parity)settingsMap->value("Parity").toInt());
        setStopBits((StopBits)settingsMap->value("StopBits").toInt());
        setFlowControl((FlowControl)settingsMap->value("FlowControl").toInt());
    }
    return open(QIODevice::ReadWrite);
}

void SerialPortHandler::closeSerial()
{
    if (isOpen()) close();
}

void SerialPortHandler::writeData(const QString &data)
{
    write(data.toUtf8());
}

QByteArray SerialPortHandler::readAll()
{
    return QSerialPort::readAll();
}

void SerialPortHandler::getPortsInfo()
{
    qDebug() << "Get ports info";
//    QList<QVariantMap> list;
//    QString manufacturer;
//    QString serialNumber;
    QString description;

    portsName.clear();
    portsDesc.clear();
    portsMap->clear();

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
//        QStringList list;
//        portsName.append(info.portName());
        description = info.description();
        qDebug() << info.portName() << ":" << description;
        portsMap->insert(info.portName(),
                         !description.isEmpty() ? description : blankString);
//        portsDesc.append(!description.isEmpty() ? description : blankString);
//        map.insert(info.portName(), (!description.isEmpty() ? description : blankString));
//        manufacturer = info.manufacturer();
//        serialNumber = info.serialNumber();
//        list << info.portName()
//             << (!description.isEmpty() ? description : blankString);
//             << (!manufacturer.isEmpty() ? manufacturer : blankString)
//             << (!serialNumber.isEmpty() ? serialNumber : blankString)
//             << info.systemLocation()
//             << (info.vendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : blankString)
//             << (info.productIdentifier() ? QString::number(info.productIdentifier(), 16) : blankString);
//        list.append(map);
//        ui->serialPortInfoListBox->addItem(list.first(), list);
    }

//    ui->serialPortInfoListBox->addItem(tr("Custom"));
//    emit portsNameChanged();
    emit portsMapChanged();
}

void SerialPortHandler::loadSettings(EMap *pMap)
{
    pMap->insert("BaudRate", Baud115200);
    pMap->insert("DataBits", Data8);
    pMap->insert("Parity", NoParity);
    pMap->insert("StopBits", OneStop);
    pMap->insert("FlowControl", NoFlowControl);
    settingsMap = pMap;
}

void SerialPortHandler::test()
{
    qDebug() << settingsMap->keys();
    qDebug() << settingsMap->values();
}

//QVariant SerialPortHandler::getTest()
//{
//    QList<QVariantMap> list;
//    QVariantMap map;
//    map.insert("text","tt1");
//    list.append(map);
//    map.clear();
//    map.insert("text","tt2");
//    list.append(map);
//    return QVariant::fromValue(list);
//}
