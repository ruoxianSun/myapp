#include "CKeyProtocol.h"
#include <QKeyEvent>
#include <QApplication>
#include <CApplication.h>
#include <QInputEvent>
void CKeyProtocol::Process(const QVariantMap &map)
{
    if(!map.contains("uri"))return;
    if(map["uri"].toByteArray()!=_protocolID)return;
    int key=map["code"].toInt();
    bool alt=map["alt"].toBool();
    bool ctrl=map["ctrl"].toBool();
    bool shift=map["shift"].toBool();
    Qt::KeyboardModifiers km=Qt::NoModifier;
    km|=alt?Qt::AltModifier:Qt::NoModifier;
    km|=ctrl?Qt::ControlModifier:Qt::NoModifier;
    km|=shift?Qt::ShiftModifier:Qt::NoModifier;
    QVariant v=getSharedObject("app");
    CApplication*app=v.value<CApplication*>();
    qDebug()<<"===focus obj:"<<qApp->focusObject();
    if(!qApp->focusObject())return;
    if(map["type"].toByteArray()=="down")
    {
        QKeyEvent e(QKeyEvent::KeyPress,key,km);
        QApplication::sendEvent(qApp->focusObject(),&e);
    }
    else if(map["type"].toByteArray()=="up")
    {
        QKeyEvent e(QKeyEvent::KeyRelease,key,km);
        QApplication::sendEvent(qApp->focusObject(),&e);
    }

}
