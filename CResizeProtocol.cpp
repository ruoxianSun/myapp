#include "CResizeProtocol.h"
#include <QResizeEvent>
#include <QApplication>
#include "CApplication.h"
void CResizeProtocol::Process(const QVariantMap &map)
{
    if(!map.contains("uri"))return;
    if(!map["uri"].toByteArray().contains(_protocolID.toLatin1()))return;

    qDebug()<<map;
    int w=map["width"].toInt();
    int h=map["height"].toInt();
    QVariant v=getSharedObject("app");
    CApplication*app=v.value<CApplication*>();

    QResizeEvent e(QSize(w,h),app->view()->size());
    QApplication::sendEvent(app->view(),&e);
//    CAppProtocol::Process(map);
}
