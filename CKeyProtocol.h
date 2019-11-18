#ifndef CKEYPROTOCOL_H
#define CKEYPROTOCOL_H

#include <QObject>
#include "CAppProtocol.h"
class CKeyProtocol : public CAppProtocol
{
    Q_OBJECT
public:
    explicit CKeyProtocol(QObject *parent = nullptr) : CAppProtocol(parent)
    {
        _protocolID="app.protocol.key";
    }
    virtual void Process(const QVariantMap&map);
signals:

public slots:
};

#endif // CKEYPROTOCOL_H
