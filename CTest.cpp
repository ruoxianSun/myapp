#include "CTest.h"
#include <qimage.h>

CTest::CTest()
{
    test();
}

void CTest::test()
{
    int step=2;
    int num=256*step;
    QImage img(num,num,QImage::Format_Grayscale8);
    for(int w=0;w<img.width();w+=step)
    {
        for(int h=0;h<img.height();h+=step)
        {
            for(int i=0;i<step;i++)
            {
                for(int j=0;j<step;j++)
                {
                    int x=w+i;
                    int y=h+j;
                    QRgb rgb=qRgb(w/step,w/step,w/step);
                    img.setPixel(x,y,rgb);
                }
            }
        }
    }
    img.save("q0.png","png",0);
    img.save("q50.png","png",50);
    img.save("q100.png","png",100);
    QImage rimg= img.convertToFormat(QImage::Format_RGB888);

    rimg.save("rq0.png","png",0);
    rimg.save("rq50.png","png",50);
    rimg.save("rq100.png","png",100);
}
