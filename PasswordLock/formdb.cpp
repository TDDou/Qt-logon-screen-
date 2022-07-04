#include "formdb.h"
#include "ui_formdb.h"
//#include "mainwindow.h"
#include "mysqlquerymodel.h"
#include "mainwindow.h"
#include <QTableView>
#include <QtDebug>

Formdb::Formdb(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Formdb)
{
    ui->setupUi(this);
       MySqlQueryModel *myModel = new MySqlQueryModel;
       QString userId = Currentname;
       QString sql=QString("select * from passwd where userId='%1'")
               .arg(userId);
       //setQuery(sql);
       myModel->setQuery(sql);
       myModel->setHeaderData(0, Qt::Horizontal, tr("id"));
       myModel->setHeaderData(1, Qt::Horizontal, tr("name"));
       myModel->setHeaderData(2, Qt::Horizontal, tr("passwd"));
       ui->tableView->setModel(myModel);




}

Formdb::~Formdb()
{
    delete ui;
}

void Formdb::sqlite_pwdInit()
{

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
        QString createsql=QString("create table if not exists passwd(id integer primary key autoincrement,"
                            "userId ntext,"
                            "passwd ntext unique)");

}

void Formdb::on_btn_add_clicked()
{
    sqlite_pwdInit();

    QString passwd = ui->lineEdit_passwd->text();
     QString sql=QString("insert into passwd(userId,passwd) values('%1','%2');")
           .arg(Currentname).arg(passwd);
     qDebug()<<Currentname<<"\n"<<passwd;
    //创建执行语句对象
    QSqlQuery query;

    if(!query.exec(sql)){
        qDebug()<<"init insert error";
    }

    ui->lineEdit_passwd->clear();
    on_btn_fre_clicked();

}

void Formdb::on_btn_del_clicked()
{
    qDebug()<<" this is de1";
    sqlite_pwdInit();
    qDebug()<<" this is de2";
   int Id = ui->lineEdit_id->text().toInt();
    QString sql=QString("delete from passwd where id='%1';")
         .arg(Id);
    QSqlQuery query;

    if(!query.exec(sql)){
        qDebug()<<" delete error";
    }
    else {
        qDebug()<<" this is de3";
    }

    ui->lineEdit_id->clear();

    on_btn_fre_clicked();

}

void Formdb::on_btn_fre_clicked()
{
    //freash
    QString userId = Currentname;
    MySqlQueryModel *myModel = new MySqlQueryModel;
    QString sql=QString("select * from passwd where userId='%1'")
            .arg(userId);
    //setQuery(sql);
    myModel->setQuery(sql);
    myModel->setHeaderData(0, Qt::Horizontal, tr("id"));
    myModel->setHeaderData(1, Qt::Horizontal, tr("name"));
    myModel->setHeaderData(2, Qt::Horizontal, tr("passwd"));
    ui->tableView->setModel(myModel);
}
