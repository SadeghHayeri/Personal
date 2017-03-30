#include "editline.h"
#include "ui_editline.h"
#include "mainwindow.h"
#include <QTextBlock>

editline::editline( Client* _client, int _lineNum, QString oldText, std::string _bookName, std::string _chapterName,int _versionNum, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editline),
    bookName( _bookName ),
    chapterName( _chapterName ),
    client(_client),
    lineNum(_lineNum),
    versionNum(_versionNum)
{
    ui->setupUi(this);
    ui->lineNum->setText( QString::number( lineNum+1 ) );
    ui->input->setPlaceholderText( oldText );
}

editline::~editline()
{
    delete ui;
}

void editline::on_editButton_clicked()
{
    int versionNum = client->getLocalLastVersionNum(bookName, chapterName);
    client->editLocalLine( bookName, chapterName, versionNum, lineNum - 1, ui->input->text().toStdString() );
    emit accept();
}
