#include "CMouseProtocol.h"
#include <QMouseEvent>
#include "CApplication.h"
#include <QApplication>
#include <QJsonObject>

void CMouseProtocol::Process(const QVariantMap &map){
    if(!map.contains("uri"))return;
    if(!map["uri"].toByteArray().contains(_protocolID.toLatin1()))return;
    QByteArray type=map["type"].toByteArray();
    int x=map["x"].toInt();
    int y=map["y"].toInt();
    int button=map["button"].toInt();
    int buttons=map["buttons"].toInt();
    int modifys=map["modifys"].toInt();
    int delat=map["delat"].toInt();
    QVariant v=getSharedObject("app");
    CApplication* app=v.value<CApplication*>();
    QWidget*view=app->view();
    view->activateWindow();
    QPoint gp(x,y);
    QWidget*child=view->childAt(gp);
    if(!child)
    {
        child=view;
    }
    if(child)
        child->setFocus();
    if(type=="mousedown")
    {
        QMouseEvent *e=new QMouseEvent(QEvent::MouseButtonPress,
                      gp,
                      (Qt::MouseButton)button,
                      (Qt::MouseButtons)buttons,
                      (Qt::KeyboardModifier)modifys);
        qDebug()<<map;
        qDebug()<<gp;
        QApplication::postEvent(child,e);
    }
    else if(type=="mouseup")
    {
        QMouseEvent e(QEvent::MouseButtonRelease,
                      gp,
                      (Qt::MouseButton)button,
                      (Qt::MouseButtons)buttons,
                      (Qt::KeyboardModifier)modifys);
        QApplication::sendEvent(child,&e);
    }
    else if(type=="mousemove")
    {
        QMouseEvent e(QEvent::MouseMove,
                      gp,
                      (Qt::MouseButton)button,
                      (Qt::MouseButtons)buttons,
                      (Qt::KeyboardModifier)modifys);
        QApplication::sendEvent(child,&e);
    }
    else if(type=="mousewheel")
    {
        QWheelEvent e(QPoint(x,y),
                      delat,
                      (Qt::MouseButtons)buttons,
                      (Qt::KeyboardModifier)modifys);
        QApplication::sendEvent(child,&e);
    }
//    CAppProtocol::Process(map);
}
