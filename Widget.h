#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    void resize(int w, int h)
    {
        QWidget::resize(w,h);
    }
    QImage getPicture()
    {
        return this->grab(this->rect()).toImage();
    }
protected:
    void paintEvent(QPaintEvent *event)
    {
        QPainter painter(this);
        painter.drawText(this->rect(),"hello world");
    }
private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
