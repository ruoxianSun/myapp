#include "CWebProtocol.h"
#include <QApplication>
CApplication*CWebProtocol::_app=0;





void CWebProtocol::send(const QString &data)
{
    _transport->sendTextMessage(data);
}

void CWebProtocol::onTextReceived(const QString &data)
{
    qDebug()<<"text received:"<<data;

    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(data.toLocal8Bit(), &json_error));
    if(json_error.error != QJsonParseError::NoError)
    {
        qDebug() << "json error!";
        return;
    }
    QJsonObject rootObj = jsonDoc.object();
    foreach (CAppProtocol*cap, _protocols)
    {
        cap->Process(rootObj.toVariantMap());
    }
}
