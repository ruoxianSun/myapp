#ifndef FORMTEST_H
#define FORMTEST_H

#include <QWidget>
#include <QMouseEvent>
namespace Ui {
class FormTest;
}

class FormTest : public QWidget
{
    Q_OBJECT

public:
    explicit FormTest(QWidget *parent = nullptr);
    ~FormTest();
    void paintEvent(QPaintEvent*e);
    void mousePressEvent(QMouseEvent*e);
    void mouseMoveEvent(QMouseEvent*e);
    void mouseReleaseEvent(QMouseEvent*e){}
private:
    Ui::FormTest *ui;
    QPoint _pressPos;
};

#endif // FORMTEST_H
