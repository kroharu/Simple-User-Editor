#ifndef ADD_USER_H
#define ADD_USER_H

#include <QDialog>
#include <QPushButton>
#include "user.h"

namespace Ui {
class AddUser;
}

class AddUser : public QDialog
{
    Q_OBJECT

public:
    explicit AddUser(QWidget *parent = nullptr);
    ~AddUser();

protected:
    void closeEvent(QCloseEvent *event) override
    {
        QDialog::closeEvent(event);
        emit closed(this);
    }

signals:
    void closed(AddUser *ptr);
    void approved(User *ptr);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_add_1name_textChanged();

    void on_add_2name_textChanged();

    void on_add_address_textChanged();

    void on_add_city_textChanged();

    void on_add_state_textChanged();

    void on_add_postcode_textChanged();

    void on_add_hphone_textChanged();

    void on_add_mphone_textChanged();

private:
    Ui::AddUser *ui;

void add_user_validation();
};

#endif // ADD_USER_H
