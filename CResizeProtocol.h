#ifndef CRESIZEPROTOCOL_H
#define CRESIZEPROTOCOL_H

#include <QObject>
#include "CAppProtocol.h"

class CResizeProtocol : public CAppProtocol
{
    Q_OBJECT
public:
    virtual void Process(const QVariantMap&map);
signals:

public slots:
};

#endif // CRESIZEPROTOCOL_H
