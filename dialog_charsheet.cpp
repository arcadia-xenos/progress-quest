#include "dialog_charsheet.h"
#include "ui_dialog_charsheet.h"

Dialog_charSheet::Dialog_charSheet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_charSheet)
{
    ui->setupUi(this);

    Dialog_charSheet::initRaceCb();
    Dialog_charSheet::initClassCb();

    Dialog_charSheet::initStats(12);

    Dialog_charSheet::testNameText(); // deactivate OK on startup

    connect(ui->btn_ok, SIGNAL(released()), this, SLOT(transferCharToGame()));
    connect(ui->btn_cancel, SIGNAL(released()), this, SLOT(close()));

    // Name is required, if text is in edit box - activate OK
    connect (ui->lne_name, SIGNAL(textEdited(QString)), this, SLOT(testNameText()));
}

Dialog_charSheet::~Dialog_charSheet()
{
    delete ui;
}

void Dialog_charSheet::transferCharToGame()
{
    // silent ignore non-named
    //if (ui->lne_name->text().isEmpty())
    //    return;

    //      Traits
    game->Player->Name  = ui->lne_name->text();
    game->Player->Race  = ui->cmb_race->currentText();
    game->Player->Voc   = ui->cmb_class->currentText();

    //      Stats
    game->Player->STR   = QString::number(ui->sbx_str->value());
    game->Player->INT   = QString::number(ui->sbx_int->value());
    game->Player->WIS   = QString::number(ui->sbx_wis->value());
    game->Player->DEX   = QString::number(ui->sbx_dex->value());
    game->Player->CON   = QString::number(ui->sbx_con->value());
    game->Player->CHA   = QString::number(ui->sbx_chr->value());

    // set isLoaded to let everyone know we accepted a new char
    game->isLoaded = true;

    // shutdown dialog
    this->close();
}

void Dialog_charSheet::initRaceCb()
{
    /*
     *      Loads available char races into combo box qwidget
     */
    for (int i=0; i < gConfig->Races.size(); i++)
        ui->cmb_race->addItem(
                    gConfig->Races.at(i).split("|").at(0),
                    QVariant::fromValue(i)
                    );
}

void Dialog_charSheet::initClassCb()
{
    /*
     *      Loads available char classes into combo box qwidget
     */
    for (int i=0; i < gConfig->Klasses.size(); i++)
        ui->cmb_class->addItem(
                    gConfig->Klasses.at(i).split("|").at(0),
                    QVariant::fromValue(i)
                    );
}

void Dialog_charSheet::initStats(int base)
{
    ui->sbx_str->setValue(base);
    ui->sbx_int->setValue(base);
    ui->sbx_wis->setValue(base);
    ui->sbx_dex->setValue(base);
    ui->sbx_con->setValue(base);
    ui->sbx_chr->setValue(base);
}

void Dialog_charSheet::testNameText()
{
    if (ui->lne_name->text().isEmpty())
    {
        ui->btn_ok->setEnabled(false);
    }
    else
    {
        ui->btn_ok->setEnabled(true);
    }
}
