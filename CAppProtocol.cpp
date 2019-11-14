#include "CAppProtocol.h"

#include "CWebProtocol.h"

void CAppProtocol::Process(const QVariantMap &map)
{
    QByteArray uri=map["uri"].toByteArray();
    QVariant v=getSharedObject("app");
    CApplication*app=v.value<CApplication*>();
    QPixmap pixmap=app->view()->grab();
#if 1
    send(toBinary(pixmap));
#else
    QJsonObject obj;
    obj.insert("uri",QJsonValue(uri.data()));
    obj.insert("format","png");
    obj.insert("data",jsonFromPixmap(pixmap));
    send(QJsonDocument(obj));
#endif
}

QVariant CAppProtocol::getSharedObject(const QString &key)
{
    return _coreProtocol->getSharedObject(key);
}

void CAppProtocol::send(const QJsonDocument &doc)
{
    _coreProtocol->send(QString(doc.toJson()));
}

void CAppProtocol::send(const QByteArray &data)
{
    _coreProtocol->send(data);
}

QByteArray CAppProtocol::toBinary(const QPixmap &p)
{
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    p.save(&buffer, "PNG");
    return buffer.data();
}
