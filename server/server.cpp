#include "server.h"
#include <qdebug.h>

server::server()
{
    qDebug() << "start";//打印
    qServer = new QTcpServer();
    qServer->listen(QHostAddress::Any, 7777);
    connect(qServer, SIGNAL(newConnection()), this, SLOT(acceptConn()));
}

void server::acceptConn()
{
    qDebug() << "accept";
    client = qServer->nextPendingConnection();
    connect(client, SIGNAL(readyRead()), this, SLOT(printMessage()));
}

void server::printMessage()
{
    qDebug() << "print";
    QByteArray read = client->readAll();
    qDebug() << read;
    client->write("hello world");
}



