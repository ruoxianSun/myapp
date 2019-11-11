#ifndef CWEBSERVER_H
#define CWEBSERVER_H

#include <QObject>
#include <QWebSocketServer>
#include "CWebProtocol.h"
#include <QDebug>

class CWebServer : public QObject
{
    Q_OBJECT
public:
    explicit CWebServer(QObject *parent = nullptr) :
        QObject(parent),
        _server(0)
    {

    }
    void startServer(QHostAddress add,qint16 port)
    {
        _server=new QWebSocketServer("qt websocket server",QWebSocketServer::NonSecureMode,this);
        connect(_server,SIGNAL(newConnection()),this,SLOT(onNewConnection()));
        _server->listen(QHostAddress::Any,port);
        qDebug()<<"web server started";
    }
signals:

public slots:
    void onNewConnection()
    {
        qDebug()<<"new connection";
        QWebSocket*ws= _server->nextPendingConnection();
        CWebProtocol*protocol=new CWebProtocol;
        protocol->setTransport(ws);
    }
protected:
    QList<CWebProtocol*> _protocols;
    QWebSocketServer*_server;
};

#endif // CWEBSERVER_H
