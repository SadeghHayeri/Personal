#ifndef MYTREE
#define MYTREE

#include <QApplication>
#include <QMenu>
#include <QMouseEvent>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QIcon>
#include "mainwindow.h"

static const int ItemType1 = QTreeWidgetItem::UserType;         // server book
static const int ItemType2 = QTreeWidgetItem::UserType + 1;     // server chapter
static const int ItemType3 = QTreeWidgetItem::UserType + 2;     // local version
static const int ItemType4 = QTreeWidgetItem::UserType + 3;     // local chapter
static const int ItemType5 = QTreeWidgetItem::UserType + 4;     // local book

class MyTree : public QTreeWidget
{
    Q_OBJECT

public:
    MyTree( MainWindow* _mainWindow )
        : mainWindow(_mainWindow)
    {
        setContextMenuPolicy(Qt::CustomContextMenu);

        connect(this,
                SIGNAL(customContextMenuRequested(const QPoint&)),
                SLOT(onCustomContextMenuRequested(const QPoint&)));        
    }

private slots:
    void onCustomContextMenuRequested(const QPoint& pos) {
        QTreeWidgetItem* item = itemAt(pos);
        if (item) {         
            showContextMenu(item, viewport()->mapToGlobal(pos));
        }
    }

    void showContextMenu(QTreeWidgetItem* item, const QPoint& globalPos) {
        currItam = item;
        QMenu menu;

        QIcon downloadIcon("/home/sadegh/net/client/png/download.png");
        QIcon downgradeIcon("/home/sadegh/net/client/png/history.png");
        QIcon editIcon("/home/sadegh/net/client/png/edit.png");
        QIcon publishIcon("/home/sadegh/net/client/png/publish.png");
        QIcon addIcon("/home/sadegh/net/client/png/symbol.png");
        QIcon addChapterIcon("/home/sadegh/net/client/png/add-circular-button.png");


        switch (item->type()) {
            case ItemType1:
                menu.addAction(downloadIcon, "Download");
                menu.addAction(editIcon,"Edit");
                menu.addAction(publishIcon,"Publish");
                break;

            case ItemType2:
                menu.addAction(downloadIcon,"Download");
                menu.addAction(downgradeIcon,"Downgrade");
                break;

            case ItemType4:
                menu.addAction(addIcon,"New Version");
                break;

            case ItemType5:
                menu.addAction(addChapterIcon,"New Chapter");
                break;

        }
        connect(&menu, SIGNAL(triggered(QAction*)), this, SLOT(menuSelection(QAction*)));

        menu.exec(globalPos);
    }

    void menuSelection(QAction* action) {

        switch (currItam->type()) {
            case ItemType1:
                if( action->text() == "Download" )
                    mainWindow->downloadBook( currItam->text(0) );
                else if( action->text() == "Edit" )
                    mainWindow->editBook( currItam->text(0) );
                else if( action->text() == "Publish" )
                    mainWindow->publishBook( currItam->text(0) );
                break;

            case ItemType2:
                if( action->text() == "Download" )
                    mainWindow->downloadChapter( currItam->parent()->text(0), currItam->text(0) );
                else if( action->text() == "Downgrade" )
                    mainWindow->downgradeChapter( currItam->parent()->text(0), currItam->text(0) );

                break;

            case ItemType4:
                if( action->text() == "New Version" )
                    mainWindow->newVersion( currItam->parent()->text(0), currItam->text(0) );
                break;

            case ItemType5:
                if( action->text() == "New Chapter" )
                    mainWindow->newChapter( currItam->text(0) );
                break;
        }
    }

private:
     MainWindow* mainWindow;
     QTreeWidgetItem* currItam;
};


#endif // MYTREE
