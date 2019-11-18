#include "Widget.h"
#include "ui_Widget.h"
#include <QMouseEvent>
#include <QDebug>
#include "FormTest.h"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setMouseTracking(true);
    infos["mouse"]="hello world";
}

Widget::~Widget()
{
    delete ui;
}

void Widget::resizeEvent(QResizeEvent *e)
{
    qDebug()<<"resize event:"<<e->size();
    resize(e->size());
}

void Widget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.drawText(10,10,infos["mouse"].toString());
    painter.drawText(10,30,infos["key"].toString());
}

void Widget::mousePressEvent(QMouseEvent *e)
{
    infos["mouse"]=QString("x: %1, y: %2").arg(e->pos().x()).arg(e->pos().y());
    QWidget::mousePressEvent(e);
    update();
}

void Widget::mouseReleaseEvent(QMouseEvent *e)
{
    infos["mouse"]=QString("x: %1, y: %2").arg(e->pos().x()).arg(e->pos().y());
    QWidget::mouseReleaseEvent(e);
    update();
}

void Widget::mouseMoveEvent(QMouseEvent *e)
{
    infos["mouse"]=QString("x: %1, y: %2").arg(e->pos().x()).arg(e->pos().y());
    QWidget::mouseMoveEvent(e);
    update();
}

void Widget::wheelEvent(QWheelEvent *e)
{
    infos["mouse"]=QString("wheel: %1").arg(e->delta());
    QWidget::wheelEvent(e);
    update();
}

void Widget::keyPressEvent(QKeyEvent *e)
{
    infos["key"]=QString("key press:%1").arg(e->key());
    if(e->key()==Qt::Key_P)
    {
        static FormTest ft(this);
        ft.setWindowFlags(Qt::CustomizeWindowHint);
        ft.show();
    }
    QWidget::keyPressEvent(e);
    update();
}

void Widget::keyReleaseEvent(QKeyEvent *e)
{
    infos["key"]=QString("key release:%1").arg(e->key());
    QWidget::keyReleaseEvent(e);
    update();
}
