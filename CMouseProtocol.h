#ifndef CMOUSEPROTOCOL_H
#define CMOUSEPROTOCOL_H

#include <QObject>
#include "CAppProtocol.h"
class CMouseProtocol:public CAppProtocol
{
    Q_OBJECT
public:
    virtual void Process(const QVariantMap&map);
};

#endif // CMOUSEPROTOCOL_H
