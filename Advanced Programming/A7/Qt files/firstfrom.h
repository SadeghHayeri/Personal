#ifndef FIRSTFROM_H
#define FIRSTFROM_H

#include <QDialog>
class Client;
namespace Ui {
class firstFrom;
}

class firstFrom : public QDialog
{
    Q_OBJECT

public:
    explicit firstFrom(Client* _myClient, QWidget *parent = 0);
    ~firstFrom();

private slots:

    void on_loginButton_clicked();

    void on_signupButton_clicked();

private:
    Ui::firstFrom *ui;
    Client* client;
};

#endif // FIRSTFROM_H
