#include "FormTest.h"
#include "ui_FormTest.h"
#include "qpainter.h"
FormTest::FormTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormTest)
{
    ui->setupUi(this);
}

FormTest::~FormTest()
{
    delete ui;
}

void FormTest::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::black,1));
    painter.drawRect(this->rect().adjusted(0,0,-1,-1));
}

void FormTest::mousePressEvent(QMouseEvent *e)
{
    if(e->buttons()&Qt::LeftButton)
    {
        _pressPos=e->globalPos()-frameGeometry().topLeft();
    }
}

void FormTest::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons()&Qt::LeftButton)
    {
        move((e->globalPos()-_pressPos));
    }
}
