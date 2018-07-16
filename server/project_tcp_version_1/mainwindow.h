#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void sendMessage();

    void on_begin_listen_clicked();

private:
    QTcpServer *tcpServer;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
