#include "CWebProtocol.h"
#include <QApplication>
CApplication*CWebProtocol::_app=0;

QVariant CAppProtocol::getSharedObject(const QString &key)
{
    return _coreProtocol->getSharedObject(key);
}

void CMouseProtocol::Process(const QVariantMap &map){
    if(!map.contains("uri"))return;
    if(!map["uri"].toByteArray().contains("app.protocol.mouseevent"))return;
    if(!map.contains("type"))return;
    QByteArray type=map["type"].toByteArray();
    int x=map["x"].toInt();
    int y=map["y"].toInt();
    int button=map["button"].toInt();
    int buttons=map["buttons"].toInt();
    int modifys=map["modifys"].toInt();

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
}
