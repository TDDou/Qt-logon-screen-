#ifndef FORMDB_H
#define FORMDB_H

#include <QWidget>




namespace Ui {
class Formdb;
}

class Formdb : public QWidget
{
    Q_OBJECT

public:
    explicit Formdb(QWidget *parent = nullptr);
    ~Formdb();
    void sqlite_pwdInit();


private slots:
    void on_btn_add_clicked();

    void on_btn_del_clicked();

    void on_btn_fre_clicked();

private:
    Ui::Formdb *ui;
};

#endif // FORMDB_H
