#include "dialog_opening.h"
#include "ui_dialog_opening.h"

Dialog_Opening::Dialog_Opening(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Opening)
{
    ui->setupUi(this);
}

Dialog_Opening::~Dialog_Opening()
{
    delete ui;
}
