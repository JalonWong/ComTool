#ifndef PORTSDATA_H
#define PORTSDATA_H

#include <QObject>

class PortsData : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString text READ getText NOTIFY textChanged)
    Q_PROPERTY(QString description READ getDescription NOTIFY descriptionChanged)

public:
    explicit PortsData(QObject *parent = 0);
    explicit PortsData(const QString &text, const QString &description, QObject *parent = 0);

    Q_INVOKABLE QString value(const QString &key);

    QString getText() const {return text;}
    QString getDescription() const {return description;}

signals:
    void textChanged();
    void descriptionChanged();

public slots:

private:
    QString text;
    QString description;
};

#endif // PORTSDATA_H
