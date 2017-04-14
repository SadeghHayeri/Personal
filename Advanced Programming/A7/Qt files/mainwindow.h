#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "/home/sadegh/net/client/client.h"
#include "/home/sadegh/net/client/exception.h"
#include <QTreeWidgetItem>
#include <QString>
#include "codeeditor.h"

class MyTree;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Client* _client, QWidget *parent = 0);

    QTreeWidgetItem* addBook( string bookName, bool haveRightClick = true );
    QTreeWidgetItem* addChapter( QTreeWidgetItem* book, string chapterName, bool haveRightClick = true );
    void addVersion( QTreeWidgetItem* chapter, int versionNum, bool local = false );
    void showBook(string BookName, string chapterName, int versionNum );

    void showServerTreeBooks();
    void downloadBook( QString bookName );
    void editBook( QString bookName );
    void publishBook( QString bookName );

    void downloadChapter( QString bookName, QString chaptername );
    void downgradeChapter( QString bookName, QString chaptername );

    void newVersion( QString bookName, QString chaptername );
    void newChapter( QString bookName );
    ~MainWindow();

private:
    bool canEdit(string bookName, string chapterName, size_t versionNum );

public slots:
    void enableWindow();
    void synedMode();
    void disableMode();
    void editMode();
    void showLocalTreeBooks();
    void addBookWindow();
    void showDownloadBookForm();
    void showRequestWindow();
    void showChangeRoleWindow();
    void sendRequestToAdmin();

private slots:
    void on_serverRadio_clicked();
    void on_clientRadio_clicked();
    void itemClicked(QTreeWidgetItem* item);
    void on_addlineButton_clicked();
    void on_editlineButton_clicked();
    void on_deleteLineButton_clicked();
    void on_syncButton_clicked();
    void changeLineNum();
    void on_fileButton_clicked();

private:
    Ui::MainWindow *ui;
    Client* client;
    MyTree* tree;
    CodeEditor* editor;

    string currBookName;
    string currChapterName;
    int currVersionNum;

};

#endif // MAINWINDOW_H
