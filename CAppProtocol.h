#ifndef CAPPPROTOCOL_H
#define CAPPPROTOCOL_H

#include <QObject>
#include <QVariant>
#include <QJsonDocument>
#include <qpixmap.h>
#include <qbuffer.h>
#include <QJsonValue>
class CWebProtocol;
class CAppProtocol:public QObject
{
    Q_OBJECT
public:
    virtual void Process(const QVariantMap&map);
    virtual QVariant getSharedObject(const QString&key);
protected:
    virtual void send(const QJsonDocument&doc);
    QJsonValue jsonFromPixmap(const QPixmap &p) {
        QBuffer buffer;
        buffer.open(QIODevice::WriteOnly);
        p.save(&buffer, "PNG");
        QByteArray encoded = buffer.data().toBase64();
        return QJsonValue(QLatin1String(encoded));
    }

    QPixmap pixmapFromJson(const QJsonValue &val) {
        auto const encoded = val.toString().toLatin1();
        QPixmap p;
        p.loadFromData(QByteArray::fromBase64(encoded), "PNG");
        return p;
    }
public:
    CWebProtocol*_coreProtocol;
};
#endif // CAPPPROTOCOL_H
