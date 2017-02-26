#ifndef LOADINGPAGE_H
#define LOADINGPAGE_H

#include <QDialog>

namespace Ui {
class loadingPage;
}

class loadingPage : public QDialog
{
    Q_OBJECT

public:
    explicit loadingPage(QWidget *parent = 0);
    ~loadingPage();

private:
    Ui::loadingPage *ui;
};

#endif // LOADINGPAGE_H
