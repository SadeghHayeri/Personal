#include "firstfrom.h"
#include "ui_firstfrom.h"
#include "/home/sadegh/net/client/client.h"
#include "/home/sadegh/net/client/exception.h"
#include <string>
#include "qtools.h"
#include "mainwindow.h"

firstFrom::firstFrom(Client* _client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::firstFrom),
    client(_client)
{
    ui->setupUi(this);
}

firstFrom::~firstFrom()
{
    delete ui;
}

void firstFrom::on_loginButton_clicked()
{
    string username = ui->loginUsername->text().toStdString();
    string password = ui->loginPassword->text().toStdString();
    if( client->login(username, password) ) {
        MainWindow* w = new MainWindow( client );
        w->show();
        close();
    }
    else {
        ui->loginButton->setText("Username or Password incorect!");
        Qtools::delay(1500);
        ui->loginButton->setText("Login");
    }
}

void firstFrom::on_signupButton_clicked()
{
    if( ui->signupUsername->text() == "" || ui->signupPassword->text() == "" ) {
        ui->signupButton->setText("all filds requered!");
        Qtools::delay(1000);
        ui->signupButton->setText("Sign up");
    }
    else if( ui->signupPassword->text() != ui->signupRePassword->text() ) {
        ui->signupButton->setText("please insert password again!");
        ui->signupPassword->setText("");
        ui->signupRePassword->setText("");
        Qtools::delay(1500);
        ui->signupButton->setText("Sign up");
    }
    else {
    string username = ui->signupUsername->text().toStdString();
    string password = ui->signupPassword->text().toStdString();
        try{
            client->signUp(username, password);
            ui->signupButton->setText("signup successfuly");
            Qtools::delay(1500);
            ui->signupUsername->setText("");
            ui->signupPassword->setText("");
            ui->signupRePassword->setText("");
            ui->signupButton->setText("Sign up");
        }
        catch( UserExist ) {
            ui->signupButton->setText("this username already exist!");
            ui->signupUsername->setText("");
            ui->signupPassword->setText("");
            ui->signupRePassword->setText("");
            Qtools::delay(1500);
            ui->signupButton->setText("Sign up");
        }
    }
}
