#include "downloadform.h"
#include "ui_downloadform.h"
#include <QFileDialog>

downloadForm::downloadForm(Client* _client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::downloadForm),
    client(_client)
{
    ui->setupUi(this);

    std::vector<std::string> list = client->getPublishedList();

    for( size_t i = 0; i < list.size(); i++ ) {
        ui->listWidget->addItem( QString::fromStdString(list[i]) );
    }
}

downloadForm::~downloadForm()
{
    delete ui;
}

void downloadForm::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "/home/" + ui->listWidget->currentItem()->text() + ".html");

    client->download( ui->listWidget->currentItem()->text().toStdString(), fileName.toStdString() );

    close();
}
