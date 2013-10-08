#include "dialog_opening.h"
#include "ui_dialog_opening.h"

Dialog_Opening::Dialog_Opening(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Opening)
{

    ui->setupUi(this);

    // attach buttons to functions
    connect(ui->btn_random, SIGNAL(released()), this, SLOT(randNewChar()));
    connect(ui->btn_load, SIGNAL(released()), this, SLOT(loadChar()));
    connect(ui->btn_createNew, SIGNAL(released()), this, SLOT(createNewChar()));
}

Dialog_Opening::~Dialog_Opening()
{
    delete ui;
}

void Dialog_Opening::randNewChar()
{
    /*
        Because mainwindow drives a random new creation by
        default, this just allows the opening menu to exit
    */
    this->close();
}

void Dialog_Opening::createNewChar()
{
    /*
     *      Create a new character according
     *      to user inputs
     */

    game->isLoaded = false; // insure default

    // create and interact with create new char dialog
    Dialog_charSheet ui_create;
    ui_create.exec();

    // we can leave is char data was accepted
    if (game->isLoaded)
        this->close();
}

void Dialog_Opening::loadChar()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open PQ7 Save File"), ".", tr("Save Files (*.pqd)"));

    if (filename.isEmpty()) return; // cancellation guard

    game->load(filename);
    this->close();
}
