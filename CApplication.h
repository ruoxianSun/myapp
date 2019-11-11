#ifndef CAPPLICATION_H
#define CAPPLICATION_H

#include <qobject.h>
#include "Widget.h"
class CApplication:public QObject
{
    Q_OBJECT
public:
    CApplication()
    {

    }
    virtual ~CApplication()
    {

    }
    virtual QWidget*view(){return 0;}
};

class CDrawApplication:public CApplication
{
    Q_OBJECT
public:
    CDrawApplication()
    {
        _window=new Widget;
        _window->resize(100,100);
        _window->show();
    }
    virtual QWidget*view(){
        return _window;
    }
protected:
    Widget*_window;
};
#endif // CAPPLICATION_H
