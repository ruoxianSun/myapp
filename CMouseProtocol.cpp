#include "CMouseProtocol.h"
#include <QMouseEvent>
#include "CApplication.h"
#include <QApplication>
#include <QJsonObject>

void CMouseProtocol::Process(const QVariantMap &map){
    if(!map.contains("uri"))return;
    if(!map["uri"].toByteArray().contains(_protocolID.toLatin1()))return;
    qDebug()<<map;
    QByteArray type=map["type"].toByteArray();
    int x=map["x"].toInt();
    int y=map["y"].toInt();
    int button=map["button"].toInt();
    int buttons=map["buttons"].toInt();
    int modifys=map["modifys"].toInt();
    int delat=map["delat"].toInt();
    if(type=="mousedown")
    {
        QMouseEvent e(QEvent::MouseButtonPress,
                      QPoint(x,y),
                      (Qt::MouseButton)button,
                      (Qt::MouseButtons)buttons,
                      (Qt::KeyboardModifier)modifys);
        QVariant v=getSharedObject("app");
        CApplication* app=v.value<CApplication*>();
        QApplication::sendEvent(app->view(),&e);
    }
    else if(type=="mouseup")
    {

        QMouseEvent e(QEvent::MouseButtonRelease,
                      QPoint(x,y),
                      (Qt::MouseButton)button,
                      (Qt::MouseButtons)buttons,
                      (Qt::KeyboardModifier)modifys);
        QVariant v=getSharedObject("app");
        CApplication* app=v.value<CApplication*>();
        QApplication::sendEvent(app->view(),&e);
    }
    else if(type=="mousemove")
    {

        QMouseEvent e(QEvent::MouseMove,
                      QPoint(x,y),
                      (Qt::MouseButton)button,
                      (Qt::MouseButtons)buttons,
                      (Qt::KeyboardModifier)modifys);
        QVariant v=getSharedObject("app");
        CApplication* app=v.value<CApplication*>();
        QApplication::sendEvent(app->view(),&e);
    }
    else if(type=="mousewheel")
    {
        QWheelEvent e(QPoint(x,y),
                      delat,
                      (Qt::MouseButtons)buttons,
                      (Qt::KeyboardModifier)modifys);
        QVariant v=getSharedObject("app");
        CApplication*app=v.value<CApplication*>();
        QApplication::sendEvent(app->view(),&e);
    }
//    CAppProtocol::Process(map);
}
