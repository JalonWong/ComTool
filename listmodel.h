#ifndef LISTMODEL_H
#define LISTMODEL_H

#include <QObject>
#include <QAbstractItemModel>
#include <portsdata.h>

class MyListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit MyListModel(QObject *parent = 0);

    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Q_INVOKABLE QVariant get(const int row) const;

    void append(const QString &text, const QVariant &data);

    QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
private:
    PortsData itemData2;
    QVariantMap itemData;
    QList<QVariantMap> list;
};

#endif // LISTMODEL_H
