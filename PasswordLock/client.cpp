#include "client.h"
#include "ui_client.h"
#include <QDebug>
#include "mainwindow.h"
#include <QMouseEvent>
#include "function.h"

QString str;
QTcpSocket *tcpSocket;
Client::Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);

    //设置窗体透明
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    //设置无边框
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    //实例阴影shadow
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    //设置阴影距离
    shadow->setOffset(-7, 5);
    //设置阴影颜色
    shadow->setColor(QColor("#888888"));
    //设置阴影圆角
    shadow->setBlurRadius(30);
    //给嵌套QWidget设置阴影
    ui->label_3->setGraphicsEffect(shadow);
    //给垂直布局器设置边距(此步很重要, 设置宽度为阴影的宽度)
    ui->label_3->setContentsMargins(1,1,1,1);



    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket,&QTcpSocket::readyRead,[=](){

        QByteArray arry = tcpSocket->readAll();
        str.append(arry);
        str.replace("\r","");
        str.replace("\n","");
        if(str.length() == 6)
        {

           passwd = str;
           str.clear();
           qDebug()<<passwd;
        }

    });
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
               this, SLOT(displayError(QAbstractSocket::SocketError)));
}

Client::~Client()
{
    delete ui;
}

void Client::on_btn_connect_clicked()
{
    newConnect();
}

void Client::newConnect()
{
    // 初始化数据大小信息为0
    blockSize = 0;

    // 取消已有的连接
    tcpSocket->abort();
    tcpSocket->connectToHost(ui->lineEdit_IP->text(),
                             ui->lineEdit_Port->text().toInt());

    if (tcpSocket->waitForConnected(2)) {
        qDebug() << "connect successfuilly!\n";
        tcpSocket->write("hello");
        ui->label_status->setText("connect");
//        Function *F = new Function;
//        F->show();
    } else {
        qDebug() << "connect failed!\n";
        QMessageBox::information(this,"网络连接","连接失败，请检查IP与Port信息");

    }


}

void Client::displayError(QAbstractSocket::SocketError)
{
    qDebug() << tcpSocket->errorString();
}







void Client::mousePressEvent(QMouseEvent *event)
{
      last = event->globalPos();  //获取按下时的坐标，全局坐标
}

void Client::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->globalX() - last.x(); //
    int dy = event->globalY() - last.y();

    last = event->globalPos();
    move(x()+dx, y()+dy);
}

void Client::mouseReleaseEvent(QMouseEvent *event)
{
    int dx = event->globalX() - last.x();
    int dy = event->globalY() - last.y();
    move(x()+dx, y()+dy);
}




void Client::on_pushButton_clicked()
{
    this->close();
}
