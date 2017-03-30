#include "editbookForm.h"
#include "ui_editbook.h"
#include <QLineEdit>
#include <QLabel>
#include "/home/sadegh/net/client/exception.h"

editBook::editBook(Client *_client, QString _BookName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editBook),
    bookName(_BookName.toStdString()),
    client(_client)
{
    ui->setupUi(this);
    ui->bookName->setText( _BookName );
    ui->name->setText( _BookName );
}

editBook::~editBook()
{
    delete ui;
}

void editBook::on_pushButton_3_clicked()
{

    vector<string> authorList;
    authorList.push_back( ui->author1->text().toStdString() );
    for( size_t i = 0; i < list.size(); i++ ) {
        authorList.push_back( list[i]->text().toStdString() );
    }

    client->editBookName( bookName, ui->name->text().toStdString() );

    try{
    client->editLocalBookName( bookName, ui->name->text().toStdString() );
    }
    catch( BookNotExist ) {
        // ok do nothing
    }

    client->editAuthors( ui->name->text().toStdString(), authorList );


    emit accepted();
    close();
}

void editBook::on_pushButton_2_clicked()
{
    QLabel* label = new QLabel( "Author" );
    QLineEdit* lineEdit = new QLineEdit();
    list.push_back( lineEdit );

    ui->form->addRow( label, lineEdit );
}
