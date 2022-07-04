#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QAbstractSocket>
#include <QtNetwork>

class QTcpSocket;
extern QTcpSocket *tcpSocket;

namespace Ui {
class Client;
}

class Client : public QWidget
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = nullptr);
    ~Client();

private slots:
    void on_btn_connect_clicked();
    void newConnect();
    void displayError(QAbstractSocket::SocketError);

    void on_pushButton_clicked();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);


private:
    Ui::Client *ui;
    //QTcpSocket *tcpSocket;
    QString message;
    // 用来存放数据的大小信息
    quint16 blockSize;
    QPoint last;

};

#endif // CLIENT_H
