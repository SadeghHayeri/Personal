#include "downgradeform.h"
#include "ui_downgradeform.h"
#include "codeeditor.h"
#include "/home/sadegh/net/client/client.h"

downgradeForm::downgradeForm( QString _bookName, QString _chapterName, Client* _client,  QWidget *parent) :
    QDialog(parent),
    ui(new Ui::downgradeForm),
    client( _client ),
    editor( new CodeEditor ),
    bookName( _bookName.toStdString() ),
    chapterName( _chapterName.toStdString() )
{

    client->downloadLastVersion( bookName, chapterName );

    ui->setupUi(this);
    editor->setReadOnly(true);
    ui->stackedWidget->addWidget( editor );
    ui->stackedWidget->setCurrentIndex(2);

    ui->bookName->setText( _bookName );
    ui->chapterName->setText( _chapterName );


    int lastVersion = client->getLastVersionNum( bookName, chapterName );
    cout << lastVersion << endl;
    ui->spinBox->setValue( lastVersion );
    ui->spinBox->setMaximum( lastVersion );
    ui->spinBox->setMinimum(0);

    std::list<string> chapter = client->build( bookName, chapterName, lastVersion );
    std::list<string>::iterator it = chapter.begin();
    for (size_t i = 0; i < chapter.size(); i++) {
        editor->appendPlainText( QString::fromStdString( *it ) );
        ++it;
    }

}

downgradeForm::~downgradeForm()
{
    delete ui;
}

void downgradeForm::on_spinBox_valueChanged(int arg1)
{
    editor->clear();
    std::list<string> chapter = client->build( bookName, chapterName, arg1 );
    std::list<string>::iterator it = chapter.begin();
    for (size_t i = 0; i < chapter.size(); i++) {
        editor->appendPlainText( QString::fromStdString( *it ) );
        ++it;
    }
}

void downgradeForm::on_downgradButton_clicked()
{
    int version = ui->spinBox->value();
    client->downgrade( bookName, chapterName, version );
    client->LocalDowngrade( bookName, chapterName, version );
    close();
}
