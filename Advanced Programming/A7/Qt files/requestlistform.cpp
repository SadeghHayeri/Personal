#include "requestlistform.h"
#include "ui_requestlistform.h"
#include <QPushButton>

requestListForm::requestListForm(Client *_client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::requestListForm),
    client(_client)
{
    ui->setupUi(this);

    vector<string> requestList = client->getRequests();
    QButtonGroup* list = new QButtonGroup;

    for( size_t i = 0; i < requestList.size(); i++ ) {

        QLabel* label = new QLabel( QString::fromStdString( requestList[i] ) );
        QPushButton* btn = new QPushButton("Accept");
        btn->setStatusTip( QString::fromStdString( requestList[i] ) );
        btn->setMaximumWidth( 75 );
        list->addButton( btn );
        ui->form->addRow( label, btn );

    }

    connect( list, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(buttonClicked(QAbstractButton*)) );

}

void requestListForm::buttonClicked( QAbstractButton* btn ) {

    QPushButton* button = dynamic_cast<QPushButton*> (btn);
    client->giveAddBookAccess( button->statusTip().toStdString() );
    button->setText( "Accepted" );
    button->setEnabled(false);

}

requestListForm::~requestListForm()
{
    delete ui;
}
