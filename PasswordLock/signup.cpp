#include "signup.h"
#include "ui_signup.h"
#include "mainwindow.h"

Signup::Signup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Signup)
{
    ui->setupUi(this);
    //设置无边框
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
}

Signup::~Signup()
{
    delete ui;
}
//注册
void Signup::on_btn_sureadd_clicked()
{
    sqlite_Init();
    username = ui->lineEdit_newname->text();
    password = ui->lineEdit_newpass->text();
    surepass = ui->lineEdit_surepass->text();
    //判断密码是否一致
    if(password == surepass)
    {
        QString sql=QString("insert into user(username,password) values('%1','%2');")
                .arg(username).arg(password);
        //创建执行语句对象
        QSqlQuery query;
        //判断执行结果
        if(!query.exec(sql))
        {
            qDebug()<<"insert into error";
            QMessageBox::information(this,"注册认证","插入失败！");
        }
        else
        {
            qDebug()<<"insert into success";
            QMessageBox::information(this,"注册认证","插入成功！");
            MainWindow *w = new MainWindow;
            w->show();
            this->close();
        }

    }else{
        QMessageBox::information(this,"注册认证","两次密码输入不一致");
    }
}
//返回登录
void Signup::on_btn_return_clicked()
{
    MainWindow *w = new MainWindow;
    w->show();
    this->close();
}
