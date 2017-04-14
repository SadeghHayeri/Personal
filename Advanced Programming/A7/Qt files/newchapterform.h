#ifndef NEWCHAPTERFORM_H
#define NEWCHAPTERFORM_H

#include <QDialog>
#include "/home/sadegh/net/client/client.h"

namespace Ui {
class newChapterForm;
}

class newChapterForm : public QDialog
{
    Q_OBJECT

public:
    explicit newChapterForm(Client* _client, QString _bookName, QWidget *parent = 0);
    ~newChapterForm();

private slots:
    void on_btn_clicked();

private:
    Ui::newChapterForm *ui;
    string bookName;
    Client* client;
};

#endif // NEWCHAPTERFORM_H
