#include "add_user.h"
#include "ui_add_user.h"
#include "mainwindow.h"

AddUser::AddUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUser)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);   // removing [?] flag from the head of the window
    ui->box_gender->addItem("Male");
    ui->box_gender->addItem("Female");
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

AddUser::~AddUser()
{
    delete ui;
}

void AddUser::on_buttonBox_accepted()       // filling each element of the list with suitaable input information
{
    User* newUser = new User;
    if (ui->add_1name->toPlainText() != "" || ui->add_2name->toPlainText() != "" ||
            ui->add_address->toPlainText() != "" || ui->add_city->toPlainText() != "" ||
            ui->add_state->toPlainText() != "" || ui->add_postcode->toPlainText() != "" ||
            ui->add_hphone->toPlainText() != "" || ui->add_mphone->toPlainText() != "")
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    newUser->setFirstName(ui->add_1name->toPlainText());
    newUser->setLastName(ui->add_2name->toPlainText());
    newUser->setGender(ui->box_gender->currentText());
    newUser->setDateOfBirth(ui->date_birth->date());
    newUser->setAddress({
                            ui->add_city->toPlainText(),
                            ui->add_state->toPlainText(),
                            ui->add_postcode->toPlainText().toInt(),
                            ui->add_address->toPlainText()
                        });
    newUser->appendPhoneNumbers({
                                    ui->add_hphone->toPlainText().toInt(),
                                    "home"
                                });
    newUser->appendPhoneNumbers({
                                    ui->add_mphone->toPlainText().toInt(),
                                    "mobile"
                                });
    emit approved(newUser);
    QWidget::close();
}


void AddUser::on_buttonBox_rejected()
{
    QWidget::close();
}


// validation of input in add_user_window

void AddUser::on_add_1name_textChanged()
{
    add_user_validation();
}


void AddUser::on_add_2name_textChanged()
{
    add_user_validation();
}


void AddUser::on_add_address_textChanged()
{
    add_user_validation();
}


void AddUser::on_add_city_textChanged()
{
    add_user_validation();
}


void AddUser::on_add_state_textChanged()
{
    add_user_validation();
}


void AddUser::on_add_postcode_textChanged()
{
    add_user_validation();
}


void AddUser::on_add_hphone_textChanged()
{
    add_user_validation();
}


void AddUser::on_add_mphone_textChanged()
{
    add_user_validation();
}

void AddUser::add_user_validation()
{
    if (ui->add_1name->toPlainText() != "" && ui->add_2name->toPlainText() != "" &&
            ui->add_address->toPlainText() != "" && ui->add_city->toPlainText() != "" &&
            ui->add_state->toPlainText() != "" && ui->add_postcode->toPlainText() != "" &&
            ui->add_hphone->toPlainText() != "" && ui->add_mphone->toPlainText() != "" &&
            ui->add_hphone->toPlainText().toInt() && ui->add_mphone->toPlainText().toInt() &&
            ui->add_postcode->toPlainText().toInt())
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    else
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

