#ifndef USER_H
#define USER_H

#include <QString>
#include <QDate>
#include <QJsonObject>
#include <QJsonArray>
#include <QMetaType>

typedef struct s_address
{
     QString city;
     QString state;
     int     postalCode;
     QString streetAddress;
}   t_address;

typedef struct s_phone
{
     long long  number;
     QString    type;
}   t_phone;

class User
{
private:
    QString         firstName;
    QString         lastName;
    QDate           dateOfBirth;
    QString         gender;
    t_address       address;
    QList<t_phone>  phoneNumbers;

public:
    User();
    User(QJsonObject obj);
    QJsonObject to_json_object();
    void setFirstName(const QString &newFirstName);
    const QString &getFirstName() const;
    const QString &getLastName() const;
    void setLastName(const QString &newLastName);
    const QDate &getDateOfBirth() const;
    void setDateOfBirth(const QDate &newDateOfBirth);
    const QString &getGender() const;
    void setGender(const QString &newGender);
    const t_address &getAddress() const;
    void setAddress(const t_address &newAddress);
    const QList<t_phone> &getPhoneNumbers() const;
    void appendPhoneNumbers(const t_phone &newPhoneNumbers);
};

#endif // USER_H
