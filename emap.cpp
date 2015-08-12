#include "emap.h"
#include <QDebug>

EMap::EMap(QObject *parent) : QObject(parent)
{

}

QVariant EMap::value(const QString &key) const
{
    qDebug() << "EMap: value:" << key;
    return map.value(key);
}

void EMap::insert(const QString &key, const QVariant &value)
{
    map.insert(key, value);
}

QStringList EMap::keys() const
{
    qDebug("EMap: keys");
    return map.keys();
}

QVariantList EMap::values() const
{
    return map.values();
}

int EMap::count() const
{
    return map.count();
}

void EMap::clear()
{
    map.clear();
}

