#ifndef DBFORM_H
#define DBFORM_H

#include <QWidget>

namespace Ui {
class DBform;
}

class DBform : public QWidget
{
    Q_OBJECT

public:
    explicit DBform(QWidget *parent = nullptr);
    ~DBform();

private:
    Ui::DBform *ui;
};

#endif // DBFORM_H
