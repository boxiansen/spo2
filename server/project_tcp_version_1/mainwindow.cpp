#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);




    /*
    tcpServer = new QTcpServer(this);
    if(!tcpServer->listen(QHostAddress::LocalHost,6666))  //监听本地的6666端口，如果出错就关闭
    {
        qDebug() << tcpServer->errorString();
        close();
    }
    else
    {}

    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(sendMessage()));//连接信号以及槽函数
    */
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendMessage()
{
    QByteArray block;//暂存所需要发送的数据  QByteArray类提供一个字节数组

    QDataStream out(&block,QIODevice::WriteOnly);//用数据流写入程序  QDataStream类为我们的程序提供了读写二进制数据的能力
    //QIODevice代表了一个可以从中读取数据或向其写入数据的输入输出设备。我们最常常见的QFile文件类就是一种QIODevice

    out.setVersion(QDataStream::Qt_4_6);//设置数据流的版本，客户端和服务器端使用的版本要相同


    /*为了保证在客户端能接收到完整的文件，我们都在数据流的最开始写入完整文件的大小信息，
     * 这样客户端就可以根据大小信息来判断是否接受到了完整的文件。
      而在服务器端，在发送数据时就要首先发送实际文件的大小信息.*/

    out <<(quint16)0;//在block的开始添加了一个quint16大小的空间

    QString str = ui->EditMessage->toPlainText();
    out << str;
    out.device()->seek(0);//返回block的开头
    out <<(quint16)(block.size()-sizeof(quint16));//它是实际文件的大小

    //我们获取已经建立的连接的子套接字
    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();

    connect(clientConnection,SIGNAL(disconnected()),clientConnection,SLOT(deleteLater()));

    //当发送完成时就会断开连接，这时就会发出disconnected()信号，
    //而最后调用deleteLater()函数保证在关闭连接后删除该套接字clientConnection。
    clientConnection ->write(block);
    clientConnection ->disconnectFromHost();

    //发送数据成功后，显示提示
    ui->showIfConnected->setText("connect sucessful");

    ui->statuslabel->setText("send message successful");
}

void MainWindow::on_begin_listen_clicked()
{
    tcpServer = new QTcpServer(this);
    if(!tcpServer->listen(QHostAddress::LocalHost,6666))  //监听本地的6666端口，如果出错就关闭dasdas
    {
        qDebug() << tcpServer->errorString();
        close();
    }
    else
    {}

    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(sendMessage()));//连接信号以及槽函数


}
