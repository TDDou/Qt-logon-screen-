#ifndef MYSQLQUERYMODEL_H
#define MYSQLQUERYMODEL_H
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QtDebug>


class MySqlQueryModel : public QSqlQueryModel
{
public:
    MySqlQueryModel();
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    //QVariant data(const QModelIndex &item, int role=Qt::DisplayRole) const;

private:
    bool setName(int userId, const QString &passwd);
    void refresh();

};

#endif // MYSQLQUERYMODEL_H
