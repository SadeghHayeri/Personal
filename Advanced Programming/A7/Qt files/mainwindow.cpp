#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "codeeditor.h"
#include <QContextMenuEvent>
#include "mytree.h"
#include "loadingpage.h"
#include "error.h"
#include "downgradeform.h"
#include "editline.h"
#include "newbookform.h"
#include <QTreeWidget>
#include <QString>
#include <QTextBlock>
#include <QFileDialog>
#include <fstream>
#include "newchapterform.h"
#include "downloadform.h"
#include "editbookForm.h"
#include "requestlistform.h"
#include "changeroleform.h"

MainWindow::MainWindow(Client* _client, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    client(_client),
    tree( new MyTree(this) ),
    editor( new CodeEditor )
{
    // setup ui
    ui->setupUi(this);

    // delete this ///////////////................................
//    client->login("admin","password");
//    client->login("sadegh","123");

    // make treeview
    ui->tree->addWidget( tree );
    ui->tree->setCurrentIndex(2);

    // make editor
    ui->stackedWidget->addWidget( editor );
    ui->stackedWidget->setCurrentIndex(2);
    disableMode();

    // show server books
    showServerTreeBooks();

    // if admin or superadmin, enable admin actions
    role UserRole = client->getRole();

    switch (UserRole) {

    case _SuperAdmin_:
        ui->actionChange_Rools->setEnabled(true);
        ui->actionRequestList->setEnabled(true);
        ui->actionSend_Request->setEnabled(false);
        break;
    case _Admin_:
        ui->actionChange_Rools->setEnabled(false);
        ui->actionRequestList->setEnabled(true);
        ui->actionSend_Request->setEnabled(false);
    case _User_:
        ui->actionChange_Rools->setEnabled(false);
        ui->actionRequestList->setEnabled(false);
        ui->actionSend_Request->setEnabled(true);
    }


    //    connect( editor, SIGNAL(cursorPositionChanged()), this, SLOT(cursorChanged() ) );
    //    connect( editor, SIGNAL(textChanged()), this, SLOT( cursorChanged()) );
    connect( tree, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(itemClicked(QTreeWidgetItem*)) );
    connect( editor, SIGNAL(cursorPositionChanged()), this, SLOT(changeLineNum()) );
    connect( ui->actionAdd_book, SIGNAL(triggered(bool)), this, SLOT(addBookWindow()) );
    connect( ui->actionDownload_Book, SIGNAL(triggered(bool)), this, SLOT(showDownloadBookForm()) );
    connect( ui->actionRequestList, SIGNAL(triggered(bool)), this, SLOT(showRequestWindow()) );
    connect( ui->actionSend_Request,SIGNAL(triggered(bool)), this, SLOT(sendRequestToAdmin()) );
    connect( ui->actionChange_Rools, SIGNAL(triggered(bool)), this, SLOT(showChangeRoleWindow()) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showBook( string bookName, string chapterName, int versionNum ) {

    try {
        editor->clear();
        editor->appendPlainText( " " );

        std::list<string> chapter = client->build( bookName, chapterName, versionNum );
        std::list<string>::iterator it = chapter.begin();
        for (size_t i = 0; i < chapter.size(); i++) {
            editor->appendPlainText( QString::fromStdString( *it ) );
            ++it;
        }
    }
    catch(...) {
        (new error("Error",""))->show();
    }

}

bool MainWindow::canEdit( string bookName, string chapterName, size_t versionNum ) {

    try {
        vector<int> versionList = client->getLocalVersionList( bookName, chapterName );

        if( versionNum != versionList.size() - 1 )
            return false;

        if( versionList[versionList.size()-1] != 0 )
            return false;

        if( versionList.size() == 0 )
            return false;

        if( versionNum == 0 )
            return false;

        return true;
    }
    catch(...) {
        (new error("Error",""))->show();
        return false;
    }

}

void MainWindow::itemClicked(QTreeWidgetItem* item) {
    try {
        if( item->type() == ItemType3 ) {
            editor->clear();
            string bookName = item->parent()->parent()->text(0).toStdString();
            string chapterName = item->parent()->text(0).toStdString();
            int versionNum = std::stoi( item->text(0).toStdString() );

            if( canEdit(bookName, chapterName, versionNum) ) {
                editor->setReadOnly( false );
            }
            else {
                editor->setReadOnly(true);
            }

            // show book
            showBook( bookName, chapterName, versionNum );

            // enable edit buttons
            if( editor->isReadOnly() ) {
                synedMode();
            }
            else {
                editMode();
            }

            try {
                if( client->getLastVersionNum( bookName, chapterName ) < versionNum ) {
                    ui->syncButton->setEnabled( true );
                    ui->syncButton->setText( "Sync" );
                }
                else {
                    ui->syncButton->setEnabled( false );
                    ui->syncButton->setText( "Synced" );
                }
                ui->syncButton->setToolTip( QString::number( versionNum ) + " -> " + QString::number( client->getLastVersionNum( bookName, chapterName ) ) );
            }
            catch( BookNotExist ) {
                ui->syncButton->setEnabled( true );
                ui->syncButton->setText( "Sync" );
                ui->syncButton->setToolTip( "" );
            }

            currBookName = bookName;
            currChapterName = chapterName;
            currVersionNum = versionNum;
        }
        else {
            ui->syncButton->setEnabled( false );
            ui->syncButton->setText( "Sync" );
        }
    }
    catch(...) {
        (new error("Error",""))->show();
    }
}


////////// show tree view books /////////////////////

QTreeWidgetItem* MainWindow::addBook( string bookName, bool haveRightClick ) {
    try {
        QTreeWidgetItem *item;
        if( haveRightClick ) {
            item = new QTreeWidgetItem(tree,ItemType1);
        }
        else {
            item = new QTreeWidgetItem(tree,ItemType5);
        }
        item->setText(0, QString::fromStdString(bookName));
        tree->addTopLevelItem(item);
        return item;
    }
    catch(...) {
        (new error("Error",""))->show();
    }
}

QTreeWidgetItem* MainWindow::addChapter( QTreeWidgetItem* book, string chapterName, bool type ) {
    try {
        QTreeWidgetItem *item;
        if( type ) {
            item = new QTreeWidgetItem(ItemType2);
        }
        else {
            item = new QTreeWidgetItem(ItemType4);
        }
        item->setText(0, QString::fromStdString(chapterName));
        book->addChild(item);
        return item;
    }
    catch(...) {
        (new error("Error",""))->show();
    }
}

void MainWindow::addVersion( QTreeWidgetItem* chapter, int versionNum, bool local ) {
    try {
        QTreeWidgetItem *item;
        if( local ) {
            item = new QTreeWidgetItem(ItemType3);
        }
        else {
            item = new QTreeWidgetItem();
        }
        item->setText(0, QString::number(versionNum));
        chapter->addChild(item);
    }
    catch(...) {
        (new error("Error",""))->show();
    }
}

void MainWindow::showServerTreeBooks() {

    try {
        vector<string> bookList = client->getBookList();
        ui->serverRadio->setChecked(true);
        tree->setHeaderLabel( "Server Library" );
        tree->clear();
        editor->clear();

        for (size_t i = 0; i < bookList.size(); i++) {

            QTreeWidgetItem* book = addBook( bookList[i] );

            try {
                vector<string>chapterList = client->getChapterList( bookList[i] );
                for (size_t j = 0; j < chapterList.size(); j++) {
                    addChapter( book, chapterList[j] );
                }
            }
            catch( NotAccess ) {
                delete book;
            }

        }
    }
    catch(...) {
        (new error("Error",""))->show();
    }

}

void MainWindow::showLocalTreeBooks() {

    try {
        vector<string> bookList = client->getLocalBookList();
        ui->clientRadio->setChecked(true);
        tree->setHeaderLabel( "Local Library" );
        tree->clear();

        for (size_t i = 0; i < bookList.size(); i++) {

            QTreeWidgetItem* book = addBook( bookList[i], false );
            vector<string>chapterList = client->getLocalChapterList( bookList[i] );

            for (size_t j = 0; j < chapterList.size(); j++) {

                QTreeWidgetItem* chapter = addChapter( book, chapterList[j], false );
                size_t lastVersion = client->getLocalLastVersionNum( bookList[i], chapterList[j] );

                for (size_t k = 0; k <= lastVersion; k++) {
                    addVersion( chapter, k, true );
                }

            }

        }
    }
    catch(...) {
        (new error("Error",""))->show();
    }

}


//////////// check boxes ////////////////

void MainWindow::on_serverRadio_clicked()
{
    showServerTreeBooks();
}

void MainWindow::on_clientRadio_clicked()
{
    showLocalTreeBooks();
}
///////////////////////////////////////////



///////////////////// QActions /////////////////////////

void MainWindow::downloadBook( QString bookName ) {

    try {
        vector<string>chapterList = client->getChapterList( bookName.toStdString() );
        for (size_t i = 0; i < chapterList.size(); i++) {
            client->downloadLastVersion( bookName.toStdString(), chapterList[i] );
    //        client->addLocalNewVersion( bookName.toStdString(), chapterList[i] );
        }
        ui->clientRadio->setChecked(true);
        showLocalTreeBooks();
    }
    catch(...) {
        (new error("Error",""))->show();
    }

}

void MainWindow::editBook( QString bookName ) {
    try{
        ::editBook* w = new ::editBook( client, bookName );
        w->show();
        connect( w, SIGNAL(accepted()), this, SLOT(showLocalTreeBooks()) );
    }
    catch( NotAccess ) {
        (new error("Not Access","only owner can editbook!"))->show();
    }
    catch(...) {
        (new error("Error",""))->show();
    }


}

void MainWindow::publishBook( QString bookName ) {
    try {
        client->publishBook( bookName.toStdString() );
        showServerTreeBooks();
    }
    catch( NotAccess ) {
        (new error("Not Access","only owner can publishBook!"))->show();
    }
    catch(...) {
        (new error("Error",""))->show();
    }
}

void MainWindow::downloadChapter( QString bookName, QString chaptername ) {
    try {
        client->downloadLastVersion( bookName.toStdString(), chaptername.toStdString() );
        ui->clientRadio->setChecked(true);
        showLocalTreeBooks();
    }
    catch( NotAccess ) {
        (new error("Not Access","you cant download this chapter!"))->show();
    }
    catch(...) {
        (new error("Error",""))->show();
    }
}

void MainWindow::downgradeChapter( QString bookName, QString chaptername ) {
    try {
        downgradeForm* form = new downgradeForm( bookName, chaptername, client );
        form->show();
    }
    catch( NotAccess ) {
        (new error("Not Access","only owner can downgrade book!"))->show();
    }
    catch(...) {
        (new error("Error",""))->show();
    }
}
//////////////////////////////////////////////////////

void MainWindow::on_addlineButton_clicked()
{
    try {
        int lineNum = ui->lineNum->text().toInt();
        client->addLocalLine( currBookName, currChapterName, currVersionNum, lineNum - 1 );
        showBook( currBookName, currChapterName, currVersionNum );
    }
    catch(...) {
        (new error("Error",""))->show();
    }
}

void MainWindow::on_editlineButton_clicked()
{
    try {
        // get line num
        int lineNum = ui->lineNum->text().toInt() - 1;

        if( lineNum != 0 ) {
            // get line text
            QTextDocument *doc = editor->document();
            QTextBlock tb = doc->findBlockByLineNumber( lineNum );
            QString oldText = tb.text();

            // make new editline window
            editline* editlinewindow = new editline( client, lineNum, oldText, currBookName, currChapterName, currVersionNum );

            // disable main window and show editline window
            this->setEnabled(false);
            editlinewindow->show();

            // if editwindow accepted or rejected, enable this window again
            connect( editlinewindow, SIGNAL(accepted()), this, SLOT(enableWindow()) );
            connect( editlinewindow, SIGNAL(rejected()), this, SLOT(enableWindow()) );
        }
    }
    catch(...) {
        (new error("Error",""))->show();
    }
}

void MainWindow::changeLineNum() {
    int lineNum = editor->textCursor().blockNumber();
    ui->lineNum->setText( QString::number(lineNum+1) );
}

void MainWindow::on_deleteLineButton_clicked()
{
    try {
        // get info
        int versionNum = client->getLocalLastVersionNum(currBookName, currChapterName);
        int lineNum = ui->lineNum->text().toInt() - 1;

        if( lineNum != 0 ) {

            // send to server
            if( lineNum != 0) {
                client->deleteLocalLine( currBookName, currChapterName, versionNum, lineNum - 1 );
            }
            else {
                client->editLocalLine( currBookName, currChapterName, versionNum, lineNum, "" );
            }
            // show book
            showBook( currBookName, currChapterName, versionNum );

        }
    }
    catch(...) {
        (new error("Error",""))->show();
    }
}

void MainWindow::on_syncButton_clicked()
{
    try {
        synedMode();
        client->syncVersion( currBookName, currChapterName, currVersionNum );
        showBook(currBookName, currChapterName, currVersionNum);
    }
    catch( NotAccess ) {
        (new error("Not Access","you cant add new book to server"))->show();
        editMode();
    }
    catch( BookNotExist ) {
        (new error("Book Not Exist","this book is not exist yed!"))->show();
        ui->syncButton->setText( "Sync" );
        ui->syncButton->setEnabled( true );
        editMode();
    }
    catch( OldVersion ) {
        (new error("Old Version","your version is out of date!"))->show();
        ui->syncButton->setText( "Sync" );
        ui->syncButton->setEnabled( true );
        editMode();
    }
}

void MainWindow::on_fileButton_clicked()
{
    try {
        string fileAddress = QFileDialog::getOpenFileName(this).toStdString();

        ifstream file;
        file.open( fileAddress.c_str() );
        if( file ) {
            string fileLine;
            int lineNum = ui->lineNum->text().toInt() - 1;
            while ( getline(file, fileLine) ) {
                client->addLocalLine(currBookName, currChapterName, currVersionNum, lineNum);
                client->editLocalLine(currBookName, currChapterName, currVersionNum, lineNum, fileLine);
                lineNum++;
            }
        }
        showBook( currBookName, currChapterName, currVersionNum );
    }
    catch(...) {
        (new error("Error",""))->show();
    }
}

void MainWindow::enableWindow() {
    this->setEnabled( true );
    showBook( currBookName, currChapterName, currVersionNum );
}

void MainWindow::synedMode() {

    ui->addlineButton->setEnabled( false );
    ui->editlineButton->setEnabled( false );
    ui->deleteLineButton->setEnabled( false );
    ui->fileButton->setEnabled( false );
    ui->lineNum->setEnabled( false );

    editor->setReadOnly( true );

    ui->syncButton->setEnabled(false);
    ui->syncButton->setText( "Synced" );

}

void MainWindow::disableMode() {

    ui->addlineButton->setEnabled( false );
    ui->editlineButton->setEnabled( false );
    ui->deleteLineButton->setEnabled( false );
    ui->fileButton->setEnabled( false );
    ui->lineNum->setEnabled( false );

    editor->setReadOnly( true );

    ui->syncButton->setEnabled(false);
    ui->syncButton->setText( "Sync" );

}

void MainWindow::editMode() {

    ui->addlineButton->setEnabled( true );
    ui->editlineButton->setEnabled( true );
    ui->deleteLineButton->setEnabled( true );
    ui->fileButton->setEnabled( true );
    ui->lineNum->setEnabled( true );

    editor->setReadOnly( false );

    ui->syncButton->setEnabled(true);
    ui->syncButton->setText( "Sync" );

}

void MainWindow::newVersion( QString bookName, QString chaptername ) {
    try {
        client->addLocalNewVersion( bookName.toStdString(), chaptername.toStdString() );
        vector<int> versionList = client->getLocalVersionList( bookName.toStdString(), chaptername.toStdString() );
        QTreeWidgetItem *item = new QTreeWidgetItem(ItemType3);
        item->setText(0, QString::number( versionList.size()-1 ) );
        tree->currentItem()->addChild( item );
    }
    catch(...) {
        (new error("Error",""))->show();
    }
}

void MainWindow::addBookWindow() {
    try {
        newBookForm* w = new newBookForm( client );
        w->show();
        connect( w, SIGNAL(accepted()), this, SLOT(showLocalTreeBooks()) );
    }
    catch( BookExist ) {
        (new error("BookExist","use other name"))->show();
    }
    catch( UserNotExist ) {
        (new error("UserNotExist","this user not found"))->show();
    }
    catch(...) {
        (new error("Error",""))->show();
    }
}

void MainWindow::newChapter( QString bookName ) {
    try {
        newChapterForm* w = new newChapterForm( client, bookName );
        w->show();
        connect( w, SIGNAL(accepted()), this, SLOT(showLocalTreeBooks()) );
    }
    catch( ChapterExist ) {
        (new error("ChapterExist","use other name"))->show();
    }
    catch(...) {
        (new error("Error",""))->show();
    }
}

void MainWindow::showDownloadBookForm() {
    try {
        downloadForm* w = new downloadForm( client );
        w->show();
    }
    catch( BookNotExist ) {
        (new error("BookNotExist","cant find this book"))->show();
    }
    catch(...) {
        (new error("Error",""))->show();
    }
}

void MainWindow::showRequestWindow() {
    try {
        requestListForm* w = new requestListForm( client );
        w->show();
    }
    catch( NotAccess ) {
        (new error("Not Access","how get this book?!"))->show();
    }
    catch(...) {
        (new error("Error",""))->show();
    }
}

void MainWindow::sendRequestToAdmin() {
    try {
        client->addBookRequest();
        ui->actionSend_Request->setEnabled(false);
    }
    catch(...) {
        (new error("Error",""))->show();
    }
}

void MainWindow::showChangeRoleWindow() {
    try {
        changeRoleForm* w = new changeRoleForm( client );
        w->show();
    }
    catch( NotAccess ) {
        (new error("Not Access","how get this book?!"))->show();
    }
    catch(...) {
        (new error("Error",""))->show();
    }
}
