#ifndef CDRAWPROTOCOL_H
#define CDRAWPROTOCOL_H

#include <QObject>
#include "CAppProtocol.h"
class CDrawProtocol : public CAppProtocol
{
    Q_OBJECT
public:
    CDrawProtocol(){_protocolID="app.protocol.draw";}
    virtual void Process(const QVariantMap&map);
signals:

public slots:
};

#endif // CDRAWPROTOCOL_H
