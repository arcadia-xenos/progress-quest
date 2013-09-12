#ifndef DIALOG_CHARSHEET_H
#define DIALOG_CHARSHEET_H

#include <QDialog>

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
};

#endif // DIALOG_CHARSHEET_H
