#include "mainwindow.h"
#include "serveraddress.h"
#include <QApplication>
#include <cstdlib>
#include "/home/sadegh/net/client/client.h"
#include "editline.h"
#include "newbookform.h"


using namespace std;

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    serverAddress w;
//    MainWindow w( new Client(new ClientSocket("127.0.0.1", 8080)) );
    w.show();

    return a.exec();
}
