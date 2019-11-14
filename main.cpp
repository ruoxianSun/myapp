#include "CWebServer.h"
#include <QApplication>
#include "CTest.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#if 1
    CWebServer server;
    server.startServer(QHostAddress::LocalHost,8888);
#else
    CTest();
#endif
    return a.exec();
}
