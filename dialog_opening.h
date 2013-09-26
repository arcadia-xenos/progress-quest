#ifndef DIALOG_OPENING_H
#define DIALOG_OPENING_H

#include <QObject>
#include <QDialog>
#include <QString>
#include <QFileDialog>
#include "dialog_charsheet.h"

#include "c_world.h"

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

public slots:
    void randNewChar();
    void createNewChar();
    void loadChar();
};

#endif // DIALOG_OPENING_H
