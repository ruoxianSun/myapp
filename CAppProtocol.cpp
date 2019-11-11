#include "CAppProtocol.h"

#include "CWebProtocol.h"

void CAppProtocol::Process(const QVariantMap &map)
{
    QByteArray uri=map["uri"].toByteArray();
    QJsonObject obj;
    obj.insert("uri",QJsonValue(uri.data()));
    QVariant v=getSharedObject("app");
    CApplication*app=v.value<CApplication*>();
    obj.insert("format","png");
    QPixmap pixmap=app->view()->grab();
    pixmap.save("test.png");
    obj.insert("data",jsonFromPixmap(pixmap));
    send(QJsonDocument(obj));
}

QVariant CAppProtocol::getSharedObject(const QString &key)
{
    return _coreProtocol->getSharedObject(key);
}

void CAppProtocol::send(const QJsonDocument &doc)
{
    _coreProtocol->send(QString(doc.toJson()));
}
