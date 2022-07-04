#ifndef FUNCTION_H
#define FUNCTION_H

#include <QWidget>
#include <QTimer>
#include<QTcpSocket>
#include "client.h"
#include <QMouseEvent>
#include <QSqlDatabase> //数据驱动
#include <QSqlQuery> //数据库执行语句

void sqlite_pwdInit();



namespace Ui {
class Function;
class QTcpSocket;
}

class Function : public QWidget
{
    Q_OBJECT

public:
    explicit Function(QWidget *parent = nullptr);
    ~Function();
    void unlock();
    void lock();
    int judge();

private:
    Ui::Function *ui;
      QPoint last;
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:

    void on_btn_lock_clicked();
    void on_btn_unlock_clicked();
    void on_btn_exit_clicked();
    void on_btn_return_clicked();
    void on_btn_manage_clicked();
};

#endif // FUNCTION_H
