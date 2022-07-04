#include "mysqlquerymodel.h"

#include "mainwindow.h"
#include <QSqlQuery>
#include <QColor>

MySqlQueryModel::MySqlQueryModel()
{

}

Qt::ItemFlags MySqlQueryModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
        if (index.column() == 2) //第二个属性可更改
           flags |= Qt::ItemIsEditable;
        return flags;


}

bool MySqlQueryModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.column() < 1 || index.column() > 2)
           return false;
       QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);
        int id = data(primaryKeyIndex).toInt(); //获取id号
        clear();
        bool ok;
        if (index.column() == 2) //第二个属性可更改
           ok = setName(id, value.toString());
        refresh();
        return ok;

}



bool MySqlQueryModel::setName(int userId, const QString &passwd)
{
        QSqlQuery query;
        query.prepare("update passwd set passwd = ? where id = ?");
        query.addBindValue(passwd);
        query.addBindValue(userId);
        return query.exec();


}

void MySqlQueryModel::refresh()
{

        QString userId = Currentname;
        QString sql=QString("select * from passwd where userId='%1'")
                .arg(userId);
        setQuery(sql);
        setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
        setHeaderData(1, Qt::Horizontal, QObject::tr("userId"));
        setHeaderData(2, Qt::Horizontal, QObject::tr("passwd"));

}
