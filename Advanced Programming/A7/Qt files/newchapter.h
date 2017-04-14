#ifndef NEWCHAPTER_H
#define NEWCHAPTER_H

#include <QDialog>
#include "/home/sadegh/net/client/client.h"

namespace Ui {
class newChapterForm;
}

class newChapterForm : public QDialog
{
    Q_OBJECT

public:
    explicit newChapterForm( Client* _client, QString _BookName, QWidget *parent = 0);
    ~newChapterForm();

private slots:
    void on_btn_clicked();

private:
    Ui::newChapterForm *ui;
    Client* client;
    QString bookName;
};

#endif // NEWCHAPTER_H
