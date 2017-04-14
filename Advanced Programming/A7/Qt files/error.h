#ifndef ERROR_H
#define ERROR_H

#include <QDialog>

namespace Ui {
class error;
}

class error : public QDialog
{
    Q_OBJECT

public:
    explicit error(QString title, QString text,QWidget *parent = 0);
    ~error();

private:
    Ui::error *ui;
};

#endif // ERROR_H
