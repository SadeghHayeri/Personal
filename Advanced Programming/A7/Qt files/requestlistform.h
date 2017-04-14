#ifndef REQUESTLISTFORM_H
#define REQUESTLISTFORM_H

#include <QDialog>
#include "/home/sadegh/net/client/client.h"
#include <QPushButton>

namespace Ui {
class requestListForm;
}

class requestListForm : public QDialog
{
    Q_OBJECT

public:
    explicit requestListForm( Client* _client,QWidget *parent = 0);
    ~requestListForm();

private slots:

    void buttonClicked( QAbstractButton* btn );

private:
    Ui::requestListForm *ui;
    Client* client;
};

#endif // REQUESTLISTFORM_H
