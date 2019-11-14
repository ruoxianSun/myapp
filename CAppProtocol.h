#ifndef CAPPPROTOCOL_H
#define CAPPPROTOCOL_H

#include <QObject>
#include <QVariant>
#include <QJsonDocument>
#include <qpixmap.h>
#include <qbuffer.h>
#include <QJsonValue>
#include <QDebug>
class CWebProtocol;
class CAppProtocol:public QObject
{
    Q_OBJECT
public:
    CAppProtocol(){_protocolID="app.protocol.base";}
    virtual void Process(const QVariantMap&map);
    virtual QVariant getSharedObject(const QString&key);
protected:
    virtual void send(const QJsonDocument&doc);
    virtual void send(const QString&data){}
    virtual void send(const QByteArray&data);
    QJsonValue jsonFromPixmap(const QPixmap &p) {
        QBuffer buffer;
        buffer.open(QIODevice::WriteOnly);
        p.save(&buffer, "PNG");
        QByteArray encoded = buffer.data().toBase64();
        return QJsonValue(QLatin1String(encoded));
    }
    QByteArray toBinary(const QPixmap&p);

    QPixmap pixmapFromJson(const QJsonValue &val) {
        auto const encoded = val.toString().toLatin1();
        QPixmap p;
        p.loadFromData(QByteArray::fromBase64(encoded), "PNG");
        return p;
    }
public:
    CWebProtocol*_coreProtocol;
    QString _protocolID;
};
#endif // CAPPPROTOCOL_H
