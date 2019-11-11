#include "CWebServer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CWebServer server;
    server.startServer(QHostAddress::LocalHost,8888);
    return a.exec();
}
