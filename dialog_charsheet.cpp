#include "dialog_charsheet.h"
#include "ui_dialog_charsheet.h"

Dialog_charSheet::Dialog_charSheet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_charSheet)
{
    ui->setupUi(this);
}

Dialog_charSheet::~Dialog_charSheet()
{
    delete ui;
}
