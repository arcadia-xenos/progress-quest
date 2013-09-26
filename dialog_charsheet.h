#ifndef DIALOG_CHARSHEET_H
#define DIALOG_CHARSHEET_H

#include <QDialog>
#include <QString>
#include <QList>
#include "c_world.h"
#include "pq7_config.h"

namespace Ui {
class Dialog_charSheet;
}

class Dialog_charSheet : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog_charSheet(QWidget *parent = 0);
    ~Dialog_charSheet();
    
private:
    Ui::Dialog_charSheet *ui;

    void initRaceCb();
    void initClassCb();
    void initStats(int base);

public slots:
    void transferCharToGame();
    void testNameText();
};

#endif // DIALOG_CHARSHEET_H
