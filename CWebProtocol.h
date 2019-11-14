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
#include "CDrawProtocol.h"
class CWebProtocol : public QObject
{
    Q_OBJECT
public:
    explicit CWebProtocol(QObject *parent = nullptr);
    virtual ~CWebProtocol();
    virtual CApplication* initApplication();
    virtual void setSharedObject(const QString&key,QVariant obj);
    virtual QVariant getSharedObject(const QString&key);
    virtual void registerAppProtocol(CAppProtocol*protocol);
    virtual void unregisterAppProtocol(CAppProtocol*protocol);
    virtual void setTransport(QWebSocket*transport);
    virtual void send(const QString&data);
    virtual void send(const QByteArray&data);
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
