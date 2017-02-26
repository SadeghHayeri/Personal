#include "error.h"
#include "ui_error.h"
#include <QBitmap>

error::error(QString title, QString text,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::error)
{
    ui->setupUi(this);
    ui->title->setText( title );
    ui->text->setText( text );

    QPixmap pixmap("/home/sadegh/net/client/png/warning.png");
    ui->image->setPixmap(pixmap);
    ui->image->setMask(pixmap.mask());

}

error::~error()
{
    delete ui;
}
