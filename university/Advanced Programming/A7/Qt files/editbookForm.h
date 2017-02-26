#ifndef EDITBOOK_H
#define EDITBOOK_H

#include <QDialog>
#include "/home/sadegh/net/client/client.h"
#include <QLineEdit>

namespace Ui {
class editBook;
}

class editBook : public QDialog
{
    Q_OBJECT

public:
    explicit editBook( Client* _client, QString _BookName, QWidget *parent = 0);
    ~editBook();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::editBook *ui;
    std::string bookName;
    Client* client;
    QList< QLineEdit* > list;
};

#endif // EDITBOOK_H
