#ifndef CDRAWPROTOCOL_H
#define CDRAWPROTOCOL_H

#include <QObject>
#include "CAppProtocol.h"
class CDrawProtocol : public CAppProtocol
{
    Q_OBJECT
public:
    virtual void Proccess(const QVariantMap&map);
signals:

public slots:
};

#endif // CDRAWPROTOCOL_H
