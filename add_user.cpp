#include "add_user.h"
#include "ui_add_user.h"

#define FIRSTNAME_RX "^[A-Z]{1}[a-z]*$"
#define LASTNAME_RX  "^[A-Z]{1}[a-zA-Z '.,-]*$"
#define ADDRESS_RX   "^[A-Z]{1}[a-zA-Z0-9 '.,-/]*$"
#define POSTCODE_RX  "^[0-9]*$"
#define PHONE_RX     "^[+]{1}[0-9]*"

AddUser::AddUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUser)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);   // removing [?] flag from the head of the window
    ui->box_gender->addItem("Male");
    ui->box_gender->addItem("Female");
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    QRegExp rx1Name(FIRSTNAME_RX);
    QRegExp rx2Name(LASTNAME_RX);
    QRegExp rxAddress(ADDRESS_RX);
    QRegExp rxPostCode(POSTCODE_RX);
    QRegExp rxPhone(PHONE_RX);
    QRegExpValidator *vali1Name = new QRegExpValidator(rx1Name, this);
    QRegExpValidator *vali2Name = new QRegExpValidator(rx2Name, this);
    QRegExpValidator *valiAddress = new QRegExpValidator(rxAddress, this);
    QRegExpValidator *valiPostCode = new QRegExpValidator(rxPostCode, this);
    QRegExpValidator *valiPhone = new QRegExpValidator(rxPhone, this);
    ui->add_1name->setValidator(vali1Name);
    ui->add_2name->setValidator(vali2Name);
    ui->add_address->setValidator(valiAddress);
    ui->add_city->setValidator(valiAddress);
    ui->add_state->setValidator(valiAddress);
    ui->add_postcode->setValidator(valiPostCode);
    ui->add_hphone->setValidator(valiPhone);
    ui->add_mphone->setValidator(valiPhone);
}

AddUser::~AddUser()
{
    delete ui;
}

void AddUser::on_buttonBox_accepted()       // filling each element of the list with suitaable input information
{
    User* newUser = new User;
    newUser->setFirstName(ui->add_1name->text());
    newUser->setLastName(ui->add_2name->text());
    newUser->setGender(ui->box_gender->currentText());
    newUser->setDateOfBirth(ui->date_birth->date());
    newUser->setAddress({
                            ui->add_city->text(),
                            ui->add_state->text(),
                            ui->add_postcode->text().toInt(),
                            ui->add_address->text()
                        });
    newUser->appendPhoneNumbers({
                                    ui->add_hphone->text(),
                                    "home"
                                });
    newUser->appendPhoneNumbers({
                                    ui->add_mphone->text(),
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
    if (ui->add_1name->text().isEmpty() || ui->add_2name->text().isEmpty() ||
            ui->add_address->text().isEmpty() || ui->add_city->text().isEmpty() ||
            ui->add_state->text().isEmpty() || ui->add_postcode->text().isEmpty() ||
            ui->add_hphone->text().isEmpty() || ui->add_mphone->text().isEmpty())
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    else
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}

