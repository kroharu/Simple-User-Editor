#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>
#include <QApplication>
#include <QListWidget>
#include <QMessageBox>
#include <QErrorMessage>
#include <QDate>
#include <QList>

#include "add_user.h"
#include "user.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QList<AddUser*>  new_user_window;                  // window for adding user
    QList<User*>     users;                            // list of users
    const QString    fileName = "Users.json";

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override
    {
        QMainWindow::closeEvent(event);
        for(auto i : new_user_window)
            i->close();
    }

private slots:
    void on_add_button_clicked();

    void on_remove_button_clicked();

    void on_widget_users_itemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;

void terminator(AddUser *ptr);

void creator(User *ptr);

void sweeper();

void update_interface();

QJsonObject to_json_array();

int fill_users_list();
};
#endif // MAINWINDOW_H
