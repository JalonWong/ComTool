#include <QMessageBox>
#include <QSerialPortInfo>
#include "serialporthandler.h"
#include <QDebug>

static const char blankString[] = "N/A";

SerialPortHandler::SerialPortHandler(QObject *parent)
    : QSerialPort(parent)
    , portsMap(new EMap)
{
}

SerialPortHandler::~SerialPortHandler()
{
    closeSerial();
}

bool SerialPortHandler::openSerial()
{
    if(settingsMap) {
        setPortName(settingsMap->value("COM").toString());
        setBaudRate((BaudRate)settingsMap->value("BaudRate").toInt());
        setDataBits((DataBits)settingsMap->value("DataBits").toInt());
        setParity((Parity)settingsMap->value("Parity").toInt());
        setStopBits((StopBits)settingsMap->value("StopBits").toInt());
        setFlowControl((FlowControl)settingsMap->value("FlowControl").toInt());
        return open(QIODevice::ReadWrite);
    }
    setErrorString(tr("Settings Map not init."));
    return false;
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
    QString description;

    portsMap->clear();

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        description = info.description();
        qDebug() << info.portName() << ":" << description;
        portsMap->insert(info.portName(),
                         !description.isEmpty() ? description : blankString);
    }

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
