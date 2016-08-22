#include "changeroleform.h"
#include "ui_changeroleform.h"

changeRoleForm::changeRoleForm(Client *_client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changeRoleForm),
    client(_client)
{
    ui->setupUi(this);
}

changeRoleForm::~changeRoleForm()
{
    delete ui;
}

void changeRoleForm::on_pushButton_clicked()
{
    string userName = ui->username->text().toStdString();
    if( ui->adminradio->isChecked() )
        client->setAccess( userName, _Admin_ );
    if( ui->userradio->isChecked() )
        client->setAccess( userName, _User_ );
    close();
}
