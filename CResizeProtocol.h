#ifndef CRESIZEPROTOCOL_H
#define CRESIZEPROTOCOL_H

#include <QObject>
#include "CAppProtocol.h"

class CResizeProtocol : public CAppProtocol
{
    Q_OBJECT
public:
    CResizeProtocol(){_protocolID="app.protocol.resize";}
    virtual void Process(const QVariantMap&map);
signals:

public slots:
};

#endif // CRESIZEPROTOCOL_H
