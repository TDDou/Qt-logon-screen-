#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QSqlDatabase> //数据驱动
#include <QSqlQuery> //数据库执行语句
#include <QCryptographicHash> //加密
#include <QMessageBox>//消息盒子
#include <QDebug>
#include <QDir>
#include <QGraphicsDropShadowEffect>
#include <QLabel>
#include <QMouseEvent>


extern QString passwd;
extern QString Currentname;
void sqlite_Init();


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_btn_new_clicked();
    void on_btn_login_clicked();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);


private:
    Ui::MainWindow *ui;
     QPoint last;

};

#endif // MAINWINDOW_H
