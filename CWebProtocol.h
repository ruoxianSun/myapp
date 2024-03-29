#ifndef CWEBPROTOCOL_H
#define CWEBPROTOCOL_H

#include <QObject>
#include <QWebSocket>
#include <QSharedPointer>
#include "CApplication.h"
#include <QMouseEvent>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include "CMouseProtocol.h"
#include "CResizeProtocol.h"
class CWebProtocol : public QObject
{
    Q_OBJECT
public:
    explicit CWebProtocol(QObject *parent = nullptr) :
        QObject(parent),
        _transport(0)
    {
        CApplication*app=initApplication();
        QVariant v;
        v.setValue<CApplication*>(app);
        setSharedObject("app",v);
        registerAppProtocol(new CMouseProtocol);
        registerAppProtocol(new CResizeProtocol);
    }
    virtual ~CWebProtocol()
    {
        _transport->deleteLater();
        _transport=0;
    }
    virtual CApplication* initApplication()
    {
        if(!_app)
        {
            _app=new CDrawApplication;
        }
        return _app;
    }
    virtual void setSharedObject(const QString&key,QVariant obj)
    {
        _sharedObjects[key]=obj;
    }
    virtual QVariant getSharedObject(const QString&key)
    {
        return _sharedObjects[key];
    }
    virtual void registerAppProtocol(CAppProtocol*protocol)
    {
        protocol->_coreProtocol=this;
        this->_protocols.append(protocol);
    }
    virtual void unregisterAppProtocol(CAppProtocol*protocol)
    {
        protocol->_coreProtocol=0;
        _protocols.removeOne(protocol);
        delete protocol;
    }
    virtual void setTransport(QWebSocket*transport)
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
    virtual void send(const QString&data);
signals:

public slots:
    void onConnected(){
        qDebug()<<"connected";
    }
    void onDisconnected(){
        qDebug()<<"disconnected";
    }
    void onError(QAbstractSocket::SocketError err)
    {
        qDebug()<<"error:"<<err;
    }
    void onBinaryReceived(const QByteArray&data)
    {
        qDebug()<<"binary received:"<<data;
    }
    void onTextReceived(const QString&data);
protected:
    QVariantMap _sharedObjects;
    QList<CAppProtocol*> _protocols;
    QWebSocket* _transport;
    static CApplication*_app;

};

#endif // CWEBPROTOCOL_H
