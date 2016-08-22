#ifndef EDITLINE_H
#define EDITLINE_H

#include <QDialog>
#include <string>
#include "codeeditor.h"
#include "/home/sadegh/net/client/client.h"


namespace Ui {
class editline;
}

class editline : public QDialog
{
    Q_OBJECT

public:
    explicit editline( Client *_client, int lineNum, QString oldText, std::string _bookName, std::string _chapterName, int _versionNum, QWidget *parent = 0);
    ~editline();
private slots:
    void on_editButton_clicked();

private:
    Ui::editline *ui;
    std::string bookName;
    std::string chapterName;
    Client* client;
    int lineNum;
    int versionNum;
};

#endif // EDITLINE_H
