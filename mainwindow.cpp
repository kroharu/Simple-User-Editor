#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "add_user.h"
#include "user.h"

int selectedUserRow;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fill_users_list();
    update_interface();
}

MainWindow::~MainWindow()
{
    delete ui;
    for (User* i:users)
        delete i;
}

void MainWindow::on_add_button_clicked() // adding user
{
    new_user_window.append(new AddUser);
    connect(new_user_window.last(), &AddUser::approved, this, &MainWindow::creator);  // making connection with window add_user with potentially pressed "yes" button
    connect(new_user_window.last(), &AddUser::closed, this, &MainWindow::terminator); // making connection with window add_user with potentially pressed "cancel" button
    new_user_window.last()->show();
}


void MainWindow::on_remove_button_clicked() // deleting user
{
    QMessageBox del_user_window;
    del_user_window.setText("Are you sure you want to delete '" + users.at(selectedUserRow)->getFirstName() +
                     " " + users.at(selectedUserRow)->getLastName() + "'?");
    QAbstractButton *yes = del_user_window.addButton("Yes",QMessageBox::YesRole);
    QAbstractButton *no = del_user_window.addButton("No",QMessageBox::NoRole);
    del_user_window.setWindowTitle("Delete user");
    del_user_window.exec();
    if(del_user_window.clickedButton() == yes)
        sweeper();
}


void MainWindow::on_widget_users_itemClicked(QListWidgetItem *item) // choosing user in widgetList
{
    int i = ui->widget_users->currentRow();

    selectedUserRow = i;
    ui->remove_button->setEnabled(true);
    ui->widget_phones->clear();
    ui->label_1name->setText(users.at(i)->getFirstName());
    ui->label_2name->setText(users.at(i)->getLastName());
    ui->label_gender->setText(users.at(i)->getGender());
    ui->label_birth->setText(users.at(i)->getDateOfBirth().toString());
    ui->label_address->setText(users.at(i)->getAddress().streetAddress);
    ui->label_city->setText(users.at(i)->getAddress().city);
    ui->label_state->setText(users.at(i)->getAddress().state);
    ui->label_postcode->setText(QString::number(users.at(i)->getAddress().postalCode));
    ui->widget_phones->addItem("home: " + QString::number(users.at(i)->getPhoneNumbers()[0].number));
    ui->widget_phones->addItem("mobile: " + QString::number(users.at(i)->getPhoneNumbers()[1].number));
}

void MainWindow::terminator(AddUser *ptr)  // helps to close add_user window correctly if the cancel button was pressed
{
    ptr->disconnect(this);
    new_user_window.removeOne(ptr);
    delete ptr;
}

void MainWindow::creator(User *ptr) // helps to add user to the file and to the list of users
{
    users.append(ptr);
    QFile file;
    file.setFileName(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    QJsonDocument doc(to_json_array());
    out << doc.toJson();
    file.close();
    update_interface();
}

void MainWindow::sweeper()  // helps to delete user from the file and from the list of users
{
    users.takeAt(selectedUserRow);
    QFile file;
    file.setFileName(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    QJsonDocument doc(to_json_array());
    out << doc.toJson();
    file.close();
    update_interface();
}

void MainWindow::update_interface() // updates interface of the main window
{
    ui->widget_users->clear();
    for (User* i:users)
        ui->widget_users->addItem(i->getFirstName() + " " + i->getLastName());
    ui->remove_button->setEnabled(false);
    ui->widget_phones->clear();
    ui->label_1name->clear();
    ui->label_2name->clear();
    ui->label_gender->clear();
    ui->label_birth->clear();
    ui->label_address->clear();
    ui->label_city->clear();
    ui->label_state->clear();
    ui->label_postcode->clear();
}

QJsonObject MainWindow::to_json_array()   // makes the basic array "users" in the file
{
    QJsonObject usersObject;
    QJsonArray  usersArray;
    for (User* i:users)
        usersArray.append(i->to_json_object());
    usersObject.insert("users", usersArray);
    return (usersObject);
}

int MainWindow::fill_users_list()    // filles the list of users
{
    QString jsonInString;
    QFile file;

    file.setFileName(fileName);
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    jsonInString = file.readAll();
    file.close();

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(jsonInString.toUtf8(), &error);

    if (doc.isObject())
    {
        QJsonObject json = doc.object();                    // turning the whole document into the one jsonObject
        QJsonArray jsonArray = json["users"].toArray();     // extracting the array named "users" from the whole jsonObject
        foreach (const QJsonValue &value, jsonArray)
        {
            if (value.isObject())                           // working with each jsonObjects which are the elements of "users" jsonArray
            {
                QJsonObject obj = value.toObject();
                users.append(new User(obj));
            }
        }
    }
    return (1);
}

