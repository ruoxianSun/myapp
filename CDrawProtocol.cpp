#include "CDrawProtocol.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "CApplication.h"
#include "CWebProtocol.h"


void CDrawProtocol::Process(const QVariantMap &map)
{
    if(!map.contains("uri"))return;
    if(!map["uri"].toByteArray().contains(_protocolID.toLatin1()))return;
//    qDebug()<<map;
    CAppProtocol::Process(map);
}
