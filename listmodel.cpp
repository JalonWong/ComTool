#include "listmodel.h"

MyListModel::MyListModel(QObject *parent)
    : QAbstractListModel(parent)
    , itemData2("text", "ddd")
{
    itemData.insert("text", "COM31");
    itemData.insert("description", "dd31");
}

int MyListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    qDebug("listmode rowCount()");
//    return list.count();
    return 1;
}

QVariant MyListModel::data(const QModelIndex &index, int role) const
{
    qDebug("listmode data()");
    return QVariant(QString("abc"));
}

QVariant MyListModel::get(const int row) const
{
    qDebug("listmode get(%d)", row);
    QStringList slist;
    slist.append("text");
    slist.append("ttt");
    return itemData;
}

void MyListModel::append(const QString &text, const QVariant &data)
{
    QVariantMap map;
    map.insert("text", text);
    map.insert("data", data);
    list.append(map);
}

QModelIndex MyListModel::index(int row, int column, const QModelIndex &parent) const
{
    qDebug("listmode index(%d)", row);
    return QAbstractListModel::index(row, column, parent);
}
