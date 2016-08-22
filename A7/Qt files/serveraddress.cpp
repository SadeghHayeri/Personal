#include "serveraddress.h"
#include "ui_serveraddress.h"
#include "firstfrom.h"
#include "/home/sadegh/net/client/client_socket.h"
#include "/home/sadegh/net/client/client.h"
#include <QString>
#include "qtools.h"

serverAddress::serverAddress(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::serverAddress)
{
    ui->setupUi(this);
}

serverAddress::~serverAddress()
{
    delete ui;
}

void serverAddress::on_pushButton_clicked()
{
    try {
        ui->pushButton->setText("Connecting...");
        string address = ui->serverAdd->text().toStdString();
        int port = stoi( ui->portNum->text().toStdString() );
        firstFrom* fForm = new firstFrom( new Client( new ClientSocket(address, port) ) );
        fForm->show();
        close();
        Qtools::delay(4000);

    }
    catch(...) {
        Qtools::delay(400);
        ui->pushButton->setText("Connect");
    }


}
