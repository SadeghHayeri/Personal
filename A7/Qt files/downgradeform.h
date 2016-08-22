#ifndef DOWNGRADEFORM_H
#define DOWNGRADEFORM_H

#include <QDialog>
#include <codeeditor.h>
#include <string>

class CodeEditor;
class Client;
namespace Ui {
class downgradeForm;
}

class downgradeForm : public QDialog
{
    Q_OBJECT

public:
    explicit downgradeForm( QString _bookName, QString _chapterName, Client* _client, QWidget *parent = 0);
    ~downgradeForm();

private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_downgradButton_clicked();

private:
    Ui::downgradeForm *ui;
    Client* client;
    CodeEditor* editor;
    std::string bookName;
    std::string chapterName;
};

#endif // DOWNGRADEFORM_H
