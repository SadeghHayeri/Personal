#ifndef DOWNLOADFORM_H
#define DOWNLOADFORM_H

#include <QDialog>
#include "/home/sadegh/net/client/client.h"

namespace Ui {
class downloadForm;
}

class downloadForm : public QDialog
{
    Q_OBJECT

public:
    explicit downloadForm(Client *_client, QWidget *parent = 0);
    ~downloadForm();

private slots:
    void on_pushButton_clicked();

private:
    Ui::downloadForm *ui;
    Client* client;
};

#endif // DOWNLOADFORM_H
