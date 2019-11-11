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
    QImage getPicture()
    {
        return this->grab(this->rect()).toImage();
    }
protected:
    void resizeEvent(QResizeEvent*e);
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent*e);
    void mouseMoveEvent(QMouseEvent*e);
    void wheelEvent(QWheelEvent*e);
private:
    Ui::Widget *ui;
    QString info;
};

#endif // WIDGET_H
