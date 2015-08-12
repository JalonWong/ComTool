#ifndef EMAP_H
#define EMAP_H

#include <QObject>
#include <QVariant>

class EMap : public QObject
{
    Q_OBJECT
public:
    explicit EMap(QObject *parent = 0);

    Q_INVOKABLE QVariant value(const QString &key) const;
    Q_INVOKABLE void insert(const QString &key, const QVariant &value);
    Q_INVOKABLE int count() const;
    Q_INVOKABLE void clear();

    Q_INVOKABLE QStringList keys() const;
    Q_INVOKABLE QVariantList values() const;

signals:

public slots:

private:
    QVariantMap map;
};

#endif // EMAP_H
