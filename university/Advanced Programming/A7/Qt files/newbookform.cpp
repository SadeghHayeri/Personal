#include "newbookform.h"
#include "ui_newbookform.h"

newBookForm::newBookForm(Client *_client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newBookForm),
    client(_client)
{
    ui->setupUi(this);
}

newBookForm::~newBookForm()
{
    delete ui;
}

void newBookForm::on_pushButton_clicked()
{
    QLabel* label = new QLabel( "Author" );
    QLineEdit* lineEdit = new QLineEdit();
    list.push_back( lineEdit );

    ui->form->addRow( label, lineEdit );
}

void newBookForm::on_pushButton_2_clicked()
{
    std::vector<std::string> authors;
    authors.push_back( ui->Author1->text().toStdString() );

    for( int i = 0; i < list.size(); i++ ) {
        authors.push_back( list[i]->text().toStdString() );
    }

    client->addLocalBook( ui->bookName->text().toStdString(), authors );
    emit accepted();
    close();
}
