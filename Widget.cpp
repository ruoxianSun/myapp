#include "Widget.h"
#include "ui_Widget.h"
#include <QMouseEvent>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    info="hello world";
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.drawText(this->rect(),info);
}

void Widget::mousePressEvent(QMouseEvent *e)
{
    info=QString("x: %1, y: %2").arg(e->pos().x()).arg(e->pos().y());
    update();
}
