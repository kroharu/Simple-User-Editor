#include "user.h"

void User::setFirstName(const QString &newFirstName)
{
    firstName = newFirstName;
}

const QString &User::getFirstName() const
{
    return firstName;
}

const QString &User::getLastName() const
{
    return lastName;
}

void User::setLastName(const QString &newLastName)
{
    lastName = newLastName;
}

const QDate &User::getDateOfBirth() const
{
    return dateOfBirth;
}

void User::setDateOfBirth(const QDate &newDateOfBirth)
{
    dateOfBirth = newDateOfBirth;
}

const QString &User::getGender() const
{
    return gender;
}

void User::setGender(const QString &newGender)
{
    gender = newGender;
}

const t_address &User::getAddress() const
{
    return address;
}

void User::setAddress(const t_address &newAddress)
{
    address = newAddress;
}

const QList<t_phone> &User::getPhoneNumbers() const
{
    return phoneNumbers;
}

void User::appendPhoneNumbers(const t_phone &newPhoneNumbers)
{
    phoneNumbers.append(newPhoneNumbers);
}

User::User()
{

}

User::User(QJsonObject obj)     // filling one user in the list with the whole information
{
    setFirstName(obj["firstName"].toString());
    setLastName(obj["lastName"].toString());
    setDateOfBirth(QDate::fromString(obj.value("dateOfBirth").toString(), "yyyy/MM/dd"));
    setGender(obj["gender"].toString());
    setAddress(t_address{
                            obj.value("address").toObject().value("city").toString(),
                            obj.value("address").toObject().value("state").toString(),
                            obj.value("address").toObject().value("postalCode").toInt(),
                            obj.value("address").toObject().value("streetAddress").toString()
                        });
    appendPhoneNumbers({
                           obj.value("phoneNumbers").toArray()[0].toObject().value("number").toInt(),
                           obj.value("phoneNumbers").toArray()[0].toObject().value("type").toString()
                       });
    appendPhoneNumbers({
                           obj.value("phoneNumbers").toArray()[1].toObject().value("number").toInt(),
                           obj.value("phoneNumbers").toArray()[1].toObject().value("type").toString()
                       });
}

QJsonObject User::to_json_object()      // converts list element to the jsonObject
{
    QJsonObject json;
    json.insert("firstName", QJsonValue(getFirstName()));
    json.insert("lastName", QJsonValue(getLastName()));
    json.insert("dateOfBirth", QJsonValue(getDateOfBirth().toString("yyyy/MM/dd")));
    json.insert("gender", QJsonValue(getGender()));
    QJsonObject address;
    address.insert("city", QJsonValue(getAddress().city));
    address.insert("state", QJsonValue(getAddress().state));
    address.insert("postalCode", QJsonValue(getAddress().postalCode));
    address.insert("streetAddress", QJsonValue(getAddress().streetAddress));
    json.insert("address", QJsonValue(address));
    QJsonArray  phoneNumberArray;
    QJsonObject phoneNumberObject;
    phoneNumberObject.insert("number", QJsonValue(getPhoneNumbers()[0].number));
    phoneNumberObject.insert("type", QJsonValue(getPhoneNumbers()[0].type));
    phoneNumberArray.append(QJsonValue(phoneNumberObject));
    phoneNumberObject.insert("number", QJsonValue(getPhoneNumbers()[1].number));
    phoneNumberObject.insert("type", QJsonValue(getPhoneNumbers()[1].type));
    phoneNumberArray.append(QJsonValue(phoneNumberObject));
    json.insert("phoneNumbers", QJsonValue(phoneNumberArray));
    return (json);
}
