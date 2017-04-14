#include "newchapterform.h"
#include "ui_newchapterform.h"

newChapterForm::newChapterForm(Client* _client, QString _bookName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newChapterForm),
    bookName( _bookName.toStdString() ),
    client(_client)
{
    ui->setupUi(this);
    ui->bookName->setText( _bookName );
}

newChapterForm::~newChapterForm()
{
    delete ui;
}

void newChapterForm::on_btn_clicked()
{
    string chapterName = ui->lineEdit->text().toStdString();
    client->addLocalChapter( bookName, chapterName );
    client->addLocalLine( bookName, chapterName, 0, 0 );
    emit accepted();
    close();
}
