#ifndef SERVERADDRESS_H
#define SERVERADDRESS_H

#include <QDialog>

namespace Ui {
class serverAddress;
}

class serverAddress : public QDialog
{
    Q_OBJECT

public:
    explicit serverAddress(QWidget *parent = 0);
    ~serverAddress();

private slots:
    void on_pushButton_clicked();

private:
    Ui::serverAddress *ui;
};

#endif // SERVERADDRESS_H
