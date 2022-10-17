#include "delete_user.h"
#include "ui_delete_user.h"
#include "mainwindow.h"

delete_user::delete_user(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::delete_user)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint); //removing [?] flag from the head of the window
}

delete_user::~delete_user()
{
    delete ui;
}

void delete_user::on_buttonBox_accepted()
{
    QWidget::close();
}


void delete_user::on_buttonBox_rejected()
{
    QWidget::close();
}

