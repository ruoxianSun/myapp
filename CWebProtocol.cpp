#include "CWebProtocol.h"
#include <QApplication>
CApplication*CWebProtocol::_app=0;





CWebProtocol::CWebProtocol(QObject *parent) :
    QObject(parent),
    _transport(0)
{
    CApplication*app=initApplication();
    QVariant v;
    v.setValue<CApplication*>(app);
    setSharedObject("app",v);
    registerAppProtocol(new CDrawProtocol);
    registerAppProtocol(new CMouseProtocol);
    registerAppProtocol(new CResizeProtocol);
}

CWebProtocol::~CWebProtocol()
{
    _transport->deleteLater();
    _transport=0;
}

CApplication *CWebProtocol::initApplication()
{
    if(!_app)
    {
        _app=new CDrawApplication;
    }
    return _app;
}

void CWebProtocol::setSharedObject(const QString &key, QVariant obj)
{
    _sharedObjects[key]=obj;
}

QVariant CWebProtocol::getSharedObject(const QString &key)
{
    return _sharedObjects[key];
}

void CWebProtocol::registerAppProtocol(CAppProtocol *protocol)
{
    protocol->_coreProtocol=this;
    this->_protocols.append(protocol);
}

void CWebProtocol::unregisterAppProtocol(CAppProtocol *protocol)
{
    protocol->_coreProtocol=0;
    _protocols.removeOne(protocol);
    delete protocol;
}

void CWebProtocol::setTransport(QWebSocket *transport)
{
    _transport=transport;
    connect(transport,SIGNAL(connected()),
            this,SLOT(onConnected()));
    connect(transport,SIGNAL(disconnected()),
            this,SLOT(onDisconnected()));
    connect(transport,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(onError(QAbstractSocket::SocketError)));
    connect(transport,SIGNAL(textMessageReceived(QString)),
            this,SLOT(onTextReceived(QString)));
    connect(transport,SIGNAL(binaryMessageReceived(QByteArray)),
            this,SLOT(onBinaryReceived(QByteArray)));
}

void CWebProtocol::send(const QString &data)
{
    _transport->sendTextMessage(data);
}

void CWebProtocol::send(const QByteArray &data)
{
    _transport->sendBinaryMessage(data);
}

void CWebProtocol::onTextReceived(const QString &data)
{
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
