#ifndef NEWBOOKFORM_H
#define NEWBOOKFORM_H

#include <QDialog>
#include "/home/sadegh/net/client/client.h"
#include <QLineEdit>

namespace Ui {
class newBookForm;
}

class newBookForm : public QDialog
{
    Q_OBJECT

public:
    explicit newBookForm( Client* _client, QWidget *parent = 0);
    ~newBookForm();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::newBookForm *ui;
    QList< QLineEdit* > list;
    Client* client;
};

#endif // NEWBOOKFORM_H
