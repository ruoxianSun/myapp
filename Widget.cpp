#include "Widget.h"
#include "ui_Widget.h"
#include <QMouseEvent>
#include <QDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setMouseTracking(true);
    info="hello world";
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
    painter.drawText(this->rect(),info);
}

void Widget::mousePressEvent(QMouseEvent *e)
{
    info=QString("x: %1, y: %2").arg(e->pos().x()).arg(e->pos().y());
    QWidget::mousePressEvent(e);
    update();
}

void Widget::mouseReleaseEvent(QMouseEvent *e)
{
    info=QString("x: %1, y: %2").arg(e->pos().x()).arg(e->pos().y());
    QWidget::mouseReleaseEvent(e);
    update();
}

void Widget::mouseMoveEvent(QMouseEvent *e)
{
    info=QString("x: %1, y: %2").arg(e->pos().x()).arg(e->pos().y());
    QWidget::mouseMoveEvent(e);
    update();
}

void Widget::wheelEvent(QWheelEvent *e)
{
    info=QString("wheel: %1").arg(e->delta());
    QWidget::wheelEvent(e);
    update();
}
