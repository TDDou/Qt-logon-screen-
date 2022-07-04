#ifndef SIGNUP_H
#define SIGNUP_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class Signup;
}

class Signup : public QWidget
{
    Q_OBJECT

public:
    explicit Signup(QWidget *parent = nullptr);
    ~Signup();

private slots:
    void on_btn_sureadd_clicked();

    void on_btn_return_clicked();

private:
    Ui::Signup *ui;
    QString username;
    QString password;
    QString surepass;
};

#endif // SIGNUP_H
