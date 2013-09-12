#ifndef DIALOG_OPENING_H
#define DIALOG_OPENING_H

#include <QDialog>

namespace Ui {
class Dialog_Opening;
}

class Dialog_Opening : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog_Opening(QWidget *parent = 0);
    ~Dialog_Opening();
    
private:
    Ui::Dialog_Opening *ui;
};

#endif // DIALOG_OPENING_H
