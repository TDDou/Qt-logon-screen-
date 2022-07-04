#include "function.h"
#include "ui_function.h"
#include "mainwindow.h"
#include "mysqlquerymodel.h"
#include "formdb.h"
#include <QDebug>
#include <string>
#include <QTableView>


Function::Function(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Function)
{
    ui->setupUi(this);
    //设置无边框
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    ui->labe_image->setPixmap(QPixmap(":/lock.png"));

    sqlite_pwdInit();

    QTimer *timer =  new QTimer(this);
    connect(timer,&QTimer::timeout,[=](){
        int ok = judge();
        if(ok == 1 ){

            unlock();
            passwd.clear();

        }
        if (ok == 0 && passwd != ""){

            lock();
            passwd.clear();
        }
    });
    timer->start(100);
}

void sqlite_pwdInit(){

    QSqlDatabase db;

    if(QSqlDatabase::contains("qt_sql_default_connection"))
      db = QSqlDatabase::database("qt_sql_default_connection");
    else{

        db = QSqlDatabase::addDatabase("QSQLITE");
        }
        db.setDatabaseName("user.db");
        if(!db.open())
        {
            qDebug()<<"open error";
        }
        //create excle
        QSqlQuery query;
        QString createsql=QString("create table if not exists passwd(id integer primary key autoincrement,"
                            "userId ntext,"
                            "passwd ntext unique)");
        query.exec(createsql);

        QString sql=QString("insert into passwd(userId,passwd) values('%1','000000');")
                .arg(Currentname);
        //创建执行语句对象

        if(!query.exec(sql)){
            //qDebug()<<"init insert error";
        }


}

Function::~Function()
{
    delete ui;

}

void Function::mousePressEvent(QMouseEvent *event)
{
    last = event->globalPos();  //获取按下时的坐标，全局坐标
}

void Function::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->globalX() - last.x(); //
    int dy = event->globalY() - last.y();

    last = event->globalPos();
    move(x()+dx, y()+dy);
}

void Function::mouseReleaseEvent(QMouseEvent *event)
{
    int dx = event->globalX() - last.x();
    int dy = event->globalY() - last.y();
    move(x()+dx, y()+dy);
}



void Function::on_btn_lock_clicked()
{

      lock();
      passwd.clear();
}

void Function::on_btn_unlock_clicked()
{

      unlock();
      passwd.clear();
}


void Function::on_btn_exit_clicked()
{
    this->close();
}

void Function::on_btn_return_clicked()
{
    MainWindow *M = new MainWindow;
    M->show();
    this->close();
}

int Function::judge()
{
    sqlite_pwdInit();
    if(passwd != ""){
        QString userId = Currentname;
        QString pass = passwd;
        QString sql=QString("select * from passwd where userId='%1' and passwd='%2'")
                .arg(userId).arg(pass);
        //创建执行语句对象
        QSqlQuery query(sql);
        //判断执行结果
        if(!query.next())
        {
            qDebug()<<"password wrong";
            //QMessageBox::information(this,"登录认证","登录失败,账户或者密码错误");
            return 0;
        }
        else
        {
            qDebug()<<"password right";
            //QMessageBox::information(this,"登录认证","登录成功");
            return 1;

        }
    }
    return 0;
}

void Function::unlock()
{
    ui->label->setText("UnLock");
    ui->labe_image->setPixmap(QPixmap(":/unlock.png"));
    QString str1 = "1";
    std::string sendInfo = str1.toStdString();
    tcpSocket->write(sendInfo.c_str());
}

void Function:: lock()
{
    ui->label->setText("Lock");
    ui->labe_image->setPixmap(QPixmap(":/lock.png"));
    QString str2 = "0";
    std::string sendInfo = str2.toStdString();
    tcpSocket->write(sendInfo.c_str());
}

void Function::on_btn_manage_clicked()
{

       Formdb * F = new Formdb;
       F->show();
}
