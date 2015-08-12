#include "portsdata.h"

PortsData::PortsData(QObject *parent) : QObject(parent)
{
}

PortsData::PortsData(const QString &text, const QString &description, QObject *parent)
    : QObject(parent)
    , text(text)
    , description(description)
{

}

QString PortsData::value(const QString &key)
{
    return "hahahah";
}

