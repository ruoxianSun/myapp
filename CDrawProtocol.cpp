#include "CDrawProtocol.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "CApplication.h"
#include "CWebProtocol.h"
void CDrawProtocol::Proccess(const QVariantMap &map)
{
    CAppProtocol::Process(map);
}
