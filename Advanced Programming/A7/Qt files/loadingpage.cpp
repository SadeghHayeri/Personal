#include "loadingpage.h"
#include "ui_loadingpage.h"
#include <QMovie>

loadingPage::loadingPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loadingPage)
{
    ui->setupUi(this);

    QMovie *movie = new QMovie("/home/sadegh/net/client/8-1.gif");
    ui->label->setMovie(movie);
    movie->start();

}

loadingPage::~loadingPage()
{
    delete ui;
}
