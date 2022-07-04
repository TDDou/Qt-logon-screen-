#include "dbform.h"
#include "ui_dbform.h"

DBform::DBform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DBform)
{
    ui->setupUi(this);
}

DBform::~DBform()
{
    delete ui;
}
