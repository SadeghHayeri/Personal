#ifndef CHANGEROLEFORM_H
#define CHANGEROLEFORM_H

#include <QDialog>
#include "/home/sadegh/net/client/client.h"

namespace Ui {
class changeRoleForm;
}

class changeRoleForm : public QDialog
{
    Q_OBJECT

public:
    explicit changeRoleForm( Client* _client, QWidget *parent = 0);
    ~changeRoleForm();

private slots:
    void on_pushButton_clicked();

private:
    Ui::changeRoleForm *ui;
    Client* client;
};

#endif // CHANGEROLEFORM_H
