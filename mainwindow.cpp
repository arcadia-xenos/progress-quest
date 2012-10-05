#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>


//make gConfig to be global
c_Config* gConfig;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // set current plot act
    Act = 0;

    State = pq_state_heading_to_killing_fields;

    // timer drive
    pb_action_timer = new QTimer(this);
    // connect timer drive
    connect(pb_action_timer, SIGNAL(timeout()), this, SLOT(incr_pb_action_value()));

    // new main classes
    Player = new Entity;
    gConfig = new c_Config;

    curMonster = new c_Monster;

    // setup / show ui
    ui->setupUi(this);

    // inits for data to the ui
    MainWindow::initPlayer();
    MainWindow::initFrames();

    // start actions
    MainWindow::setAction();
    pb_action_timer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::incr_pb_action_value()
{
    int value = ui->pb_action->value();
    if ( ++value < ui->pb_action->maximum())
    {
        ui->pb_action->setValue(value);
    }
    else
    {
        ui->pb_action->setValue(value % ui->pb_action->maximum());

        switch(State) {
        case pq_state_reserved_1: break;;
        case pq_state_heading_to_killing_fields: break;;
        case pq_state_fight:
            MainWindow::incr_pb_experience_value();

            MainWindow::incr_pb_quest_value();

            MainWindow::incr_pb_encumbrance_value();
            MainWindow::addMonDrop();
            break;;
        case pq_state_heading_to_town: break;;
        case pq_state_selling_off:
            MainWindow::rmInvItem();
            MainWindow::incr_pb_encumbrance_value();
            break;;
        case pq_state_buying_new_equip:
            MainWindow::buyNewEq();
            break;;
        }

        MainWindow::tranState();
    }
}

void MainWindow::incr_pb_encumbrance_value()
{
    // get percent value of encumbrance
    int value = int( ((float)Player->Encumbrance() / (float)Player->maxEncumbrance() * 100.0) );

    // set value to bar
    ui->pb_encumbrance->setValue(value);
}

void MainWindow::incr_pb_plot_value()
{
    QString actName;
    actName = "Act ";

    int value = ui->pb_plot->value() + 6;
    if ( value < ui->pb_plot->maximum())
    {
        // progress plot
        ui->pb_plot->setValue(value);

    }
    else
    {
        // completed plot act - add new one

        //      reset progress bar
        ui->pb_plot->setValue(value % ui->pb_plot->maximum());

        //      check current act
        ui->lst_plot->setCurrentRow(ui->lst_plot->count() - 1);
        ui->lst_plot->currentItem()->setCheckState(Qt::Checked);

        //      clear quests and start new one
        ui->lst_quests->clear();
        MainWindow::addQuest(MainWindow::randQuest());

        //      add new act
        Act++;
        MainWindow::addAct();

    }
}

void MainWindow::incr_pb_quest_value()
{
    int value = ui->pb_quest->value() + 12;
    if ( value < ui->pb_quest->maximum())
    {
        // progress quest
        ui->pb_quest->setValue(value);

    }
    else
    {
        // completed quest - add new one

        //      reset progress bar
        ui->pb_quest->setValue(value % ui->pb_quest->maximum());

        //      check last item in list
        ui->lst_quests->setCurrentRow(ui->lst_quests->count() - 1);
        ui->lst_quests->currentItem()->setCheckState(Qt::Checked);

        //      add new and progress plot
        MainWindow::addQuest(MainWindow::randQuest());
        MainWindow::incr_pb_plot_value();
    }
}

void MainWindow::incr_pb_experience_value()
{

    if (State == pq_state_fight) {

        // incr player xp
        Player->XP = Player->XP.number(Player->XP.toInt() + curMonster->winXP());

        // create pb value from player percentage
        int value = gConfig->fnPercentOf(Player->XP.toInt(), Player->maxXP());

        // is < 100% ?
        if ( value < ui->pb_experience->maximum())
        {
            ui->pb_experience->setValue(value);

        }
        else
        {
            // level up

            //      reset progress bar
            value = (value % ui->pb_experience->maximum());
            ui->pb_experience->setValue(value);

            //      incr level
            Player->incrLevel();
            ui->tbl_traits->setCurrentCell(3,1);
            ui->tbl_traits->currentItem()->setText(Player->Level);

            // win better stats
            MainWindow::winStats();

            // win new spells
            MainWindow::winSpells();

        }
    }
}

void MainWindow::initFrames()
{
    //QBrush lstItemGreyed(Qt::gray, Qt::Dense6Pattern);
    //QBrush lstItemWhite(Qt::white, Qt::SolidPattern);
    QListWidgetItem lstItemChecked, lstItemUnchecked;
    lstItemChecked.setTextColor(Qt::gray);
    lstItemChecked.setCheckState(Qt::Checked);
    lstItemUnchecked.setCheckState(Qt::Unchecked);


    // traits
    for (int i = 0; i < gConfig->Traits.size(); i++) {
        ui->tbl_traits->setItem(i, 0, new QTableWidgetItem( gConfig->Traits.at(i) ));
    }
    ui->tbl_traits->setItem(0, 1, new QTableWidgetItem( Player->Name ));
    ui->tbl_traits->setItem(1, 1, new QTableWidgetItem( Player->Race ));
    ui->tbl_traits->setItem(2, 1, new QTableWidgetItem( Player->Voc ));
    ui->tbl_traits->setItem(3, 1, new QTableWidgetItem( Player->Level ));


    // stats
    MainWindow::updStatsTbl();

    // spells
    MainWindow::updSpellTbl();

    // equipment
    MainWindow::updEquipTbl();

    // list inventory
    MainWindow::updInvTbl();

    // list initial plotline
    if (Act == 0) {
        MainWindow::addAct();
        ui->lst_plot->currentItem()->setCheckState(Qt::Checked);
        Act++;
        MainWindow::addAct();
    }
    else
    {
        MainWindow::addAct();

    }

    // list initial quest
    MainWindow::addQuest(MainWindow::randQuest());
}

void MainWindow::initPlayer()
{
    c_Spell *spell = new c_Spell;
    //c_Item *weapon = new c_Item;
    //c_Item *sheild = new c_Item;
    //QList<c_Item*> armor;
    int index(0);

    // rand traits
    Player->Name = Player->nameRand();
    Player->Race = Player->raceRand();
    Player->Voc  = Player->vocRand();

    // add starting spell
    spell->setRandName();
    Player->Spells.append(spell);

    // add starting weapon (a weak one =D )
    Player->Weapon = MainWindow::makeEqByGrade(pq_equip_weapon, -4);

    // Look ma, no sheild!
    Player->Sheild = new c_Item;

    // add two starting armors (weak, random)
    for(int i(0); i < 9; i++) {
        Player->Armor.append(new c_Item);
    }
    for (int i(0); i < 2; i++) {
        index = rand() % Player->Armor.size();
        delete Player->Armor[index];
        Player->Armor[index] = MainWindow::makeEqByGrade(pq_equip_armor, -2);
    }

    // finally, money to drink at the bar with
    Player->Gold = 10;
}


QString MainWindow::randQuest()
{
    /*
       3 types of quests:
            Hunt, Fetch, Seek

       Hunt are for monsters. Fetch is for boring items. Seek is some special item.
    */

    int randQuest = rand() % 3 + 1;

    QString rtnQuest;
    rtnQuest.clear();

    QStringList cdata;

    c_Item special;

    switch(randQuest) {

    case 1:
        // Hunt quest

        //      preamble
        switch (rand() % 3) {
        case 1:  rtnQuest += "Quell the "; break;;
        case 2:  rtnQuest += "Placate the "; break;;
        default: rtnQuest += "Hunt the ";
        }

        //      object
        cdata = gConfig->Monsters.at(rand() % gConfig->Monsters.size()).split("|");
        rtnQuest += cdata.at(0); // name
        break;;

    case 2:
        // Fetch quest

        //      preable
        switch (rand() % 4) {
        case 1:  rtnQuest += "Deliver this "; break;;
        case 2:  rtnQuest += "Collect payment for this "; break;;
        case 3:  rtnQuest += "Hide this "; break;;
        default: rtnQuest += "Fetch my ";
        }

        //      object
        cdata << gConfig->BoringItems.at(rand() % gConfig->BoringItems.size());
        rtnQuest += cdata.at(0);
        break;;

    case 3:
        // Seek quest

        //      preamble
        switch (rand() % 3) {
        case 1:  rtnQuest += "Inquire after the "; break;;
        case 2:  rtnQuest += "Aspire for the "; break;;
        default: rtnQuest += "Seek you the ";
        }

        //      object
        special.makeSpecial();
        if (rand() % 3 == 0) {
            special.addAdjMod();
        }
        rtnQuest += special.Name();
        break;;

    default:
        rtnQuest = "?";
    }

    return rtnQuest;
}

void MainWindow::addQuest(QString name)
{
    ui->lst_quests->addItem(new QListWidgetItem ());
    ui->lst_quests->setCurrentRow(ui->lst_quests->count() - 1);
    ui->lst_quests->currentItem()->setText(name);
    ui->lst_quests->currentItem()->setCheckState(Qt::PartiallyChecked);
}

void MainWindow::addAct()
{
    QString actName;

    if (Act == 0) {
        actName = "Prologue";
    }
    else
    {
        actName =  "Act ";
        actName += gConfig->toRoman(Act);
    }

    ui->lst_plot->addItem(new QListWidgetItem ());
    ui->lst_plot->setCurrentRow(ui->lst_plot->count() - 1);
    ui->lst_plot->currentItem()->setText(actName);
    ui->lst_plot->currentItem()->setCheckState(Qt::PartiallyChecked);
}

void MainWindow::setAction()
{
    Action.clear();
    switch(State) {
    case pq_state_reserved_1:
        // reserved
        break;;
    case pq_state_heading_to_killing_fields:
        // heading to killing feilds
        Action = tr("Heading to the Killing Feilds");
        pb_action_timer->setInterval(75);
        break;;
    case pq_state_fight:
        // fight
        MainWindow::setMonster();
        Action = tr("Executing ") +\
                gConfig->Indefinite(curMonster->Discription());
        pb_action_timer->setInterval(50);
        break;;
    case pq_state_heading_to_town:
        // back to Town
        Action = tr("Going back to Town to sell off");
        pb_action_timer->setInterval(75);
        break;;
    case pq_state_selling_off:
        // selling off
        Action = tr("Selling ") + MainWindow::sellInvItem();
        pb_action_timer->setInterval(20);
        break;;
    case pq_state_buying_new_equip:
        // shopping!!
        Action = tr("Negotiating purchase of new equipment");
        pb_action_timer->setInterval(35);
        break;;
    default:
        Action = tr("You are lost in another plane of existance");
        pb_action_timer->setInterval(1000);
    }
    ui->lbl_action->setText(Action);
}

void MainWindow::tranState()
{
    switch (State) {
    case pq_state_reserved_1:
        State = pq_state_heading_to_killing_fields;
        break;;
    case pq_state_heading_to_killing_fields:
        State = pq_state_fight;
        break;;
    case pq_state_fight:
        if (Player->Encumbrance() > Player->maxEncumbrance())
            State = pq_state_heading_to_town;
        break;;
    case pq_state_heading_to_town:
        State = pq_state_selling_off;
        break;;
    case pq_state_selling_off:
        if (Player->Inventory.empty())
            State = pq_state_buying_new_equip;
        break;;
    case pq_state_buying_new_equip:
        if (Player->Gold < Player->Level.toInt() *
                (80 + gConfig->fnPercent(Player->Level.toInt(), 80)) )
            State = pq_state_heading_to_killing_fields;
        break;;
    default:
        State = pq_state_reserved_1;
    }

    MainWindow::setAction();
}

void MainWindow::setMonster()
{
    bool success(false);

    // determine monster level from player's
    int Lv = Player->Level.toInt();
    Lv = Lv - (rand() % 10); // reduce monster lv up to -9 levels
    if (Lv < 0) Lv = 0; // no less than 0

    // fill out monster
    do {
        curMonster->clear();

        if (    curMonster->makeByLevel(Lv) ||
                curMonster->makeMounted(Lv) ||
                curMonster->makeGroup(Lv)
           )
            success = true;
    } while (! success);
}

void MainWindow::addMonDrop()
{

    c_Item* drop;

    for(int i(0); i < curMonster->Drops().size(); i++) {

        drop = new c_Item;
        int found(-1);

        drop->setName(curMonster->Drops().at(i));
        drop->Weight = 1;

        // if found in inventory, add another
        for(int t = 0; t < Player->Inventory.size(); t++) {
            if (Player->Inventory.at(t)->Name() == drop->Name()) {
                Player->Quantity[t] = Player->Quantity.at(t) + 1;
                ui->tbl_inventory->setCurrentCell(t+1, 1);
                found = t;
            }
        }

        // add if not
        if (found < 0) {
            Player->Inventory.append(drop);
            Player->Quantity.append(1);
            ui->tbl_inventory->setCurrentCell(ui->tbl_inventory->rowCount(), 1);
        }
    }

    // add special
    if (curMonster->isSpecial) {
        drop = new c_Item;
        drop->makeSpecial();
        drop->addAdjMod();
        Player->Inventory.append(drop);
        Player->Quantity.append(1);
        ui->tbl_inventory->setCurrentCell(ui->tbl_inventory->rowCount(), 1);
        //delete drop;
    }

    MainWindow::updInvTbl();
}

void MainWindow::rmInvItem()
{
    // this is the old PQ v6 way of sale value
    int saleValue = Player->Quantity.last() * Player->Level.toInt();

    // trade items for gold
    Player->Inventory.removeLast();
    Player->Quantity.removeLast();
    ui->tbl_inventory->removeRow(ui->tbl_inventory->rowCount());
    Player->Gold += saleValue;

    MainWindow::updInvTbl();
}

QString MainWindow::sellInvItem()
{
    // reverse through player inventory and remove table
    // contents as you go

    QString build;
    int saleValue = Player->Quantity.last() * Player->Level.toInt();

    // build a return: "q whatever[s] for n gold"
    build = QString().number(Player->Quantity.last()) + tr(" ");

    if (Player->Quantity.last() > 1)
        build += gConfig->sufPlural(Player->Inventory.last()->Name()) + tr(" ");
    else
        build += Player->Inventory.last()->Name() + tr(" ");

    build += tr("for ") + QString().number(saleValue) + tr(" gold");

    return build;
}

void MainWindow::updInvTbl()
{
    ui->tbl_inventory->clearContents();
    ui->tbl_inventory->setRowCount(1 + Player->Inventory.size());

    // gold first
    ui->tbl_inventory->setItem(0, 0, new QTableWidgetItem("Gold") );
    ui->tbl_inventory->setItem(0, 1, new QTableWidgetItem(QString().number(Player->Gold)) );

    // remaining inv list
    for (int i(0); i < Player->Inventory.size(); i++) {
        ui->tbl_inventory->setItem(i+1, 0, new QTableWidgetItem(Player->Inventory.at(i)->Name()) );
        ui->tbl_inventory->setItem(i+1, 1, new QTableWidgetItem(QString().number(Player->Quantity.at(i))) );
    }

    ui->lbl_inventory->setText( tr("Inventory ") +\
                                QString().number(Player->Encumbrance()) +\
                                tr(" units") );
}


void MainWindow::winStats()
{
    int stat_bonus = rand() % 4 + 4;
    do {
        if ( (rand() % 3 == 0) && (stat_bonus > 0) ) {
            Player->STR = Player->STR.number(Player->STR.toInt() + 1);
            stat_bonus--;
        }
        if ( (rand() % 3 == 0) && (stat_bonus > 0) ) {
            Player->INT = Player->INT.number(Player->INT.toInt() + 1);
            stat_bonus--;
        }
        if ( (rand() % 3 == 0) && (stat_bonus > 0) ) {
            Player->WIS = Player->WIS.number(Player->WIS.toInt() + 1);
            stat_bonus--;
        }
        if ( (rand() % 3 == 0) && (stat_bonus > 0) ) {
            Player->DEX = Player->DEX.number(Player->DEX.toInt() + 1);
            stat_bonus--;
        }
        if ( (rand() % 3 == 0) && (stat_bonus > 0) ) {
            Player->CON = Player->CON.number(Player->CON.toInt() + 1);
            stat_bonus--;
        }
        if ( (rand() % 3 == 0) && (stat_bonus > 0) ) {
            Player->CHA = Player->CHA.number(Player->CHA.toInt() + 1);
            stat_bonus--;
        }
    } while (stat_bonus > 0);

    Player->HPMax = Player->HPMax.number(Player->HPMax.toInt() + (rand() % 12 + 1));
    Player->MPMax = Player->MPMax.number(Player->MPMax.toInt() + (rand() % 8 + 1));

    MainWindow::updStatsTbl();
}

void MainWindow::winSpells()
{
    bool found = false;

    c_Spell* spell = new c_Spell;

    // incr current spell levels
    for (int i(0); i < Player->Spells.size(); i++) {
        if (rand() % 3 == 0) {
            Player->Spells.at(i)->incrSpellLevel();
        }
    }

    // maybe a new spell?
    spell->setRandName();

    // find if new spell exists
    for (int i(0); i < Player->Spells.size(); i++) {
        if (Player->Spells.at(i)->Name() == spell->Name())
            found = true;
    }

    // discard if found
    if (found)
        delete spell;
    else
        //add to list
        Player->Spells.append(spell);

    MainWindow::updSpellTbl();
}


void MainWindow::buyNewEq()
{
    c_Item* equip;
    t_pq_equip select;
    bool found(false);
    int pick(0);

    // first find new things to buy
    if (Player->Weapon->Name() == tr("") ) {
        delete Player->Weapon;
        Player->Weapon = MainWindow::makeEqByGrade(pq_equip_weapon, Player->Level.toInt());
        Player->Gold -= gConfig->fnPercent(Player->Gold, ((rand() % 3 + 4) * 10) ); // cost = 40%-60%
        found = true;
    }
    else
        if (Player->Sheild->Name() == tr("")) {
            delete Player->Sheild;
            Player->Sheild = MainWindow::makeEqByGrade(pq_equip_shield, Player->Level.toInt());
            Player->Gold -= gConfig->fnPercent(Player->Gold, ((rand() % 3 + 3) * 10) ); // cost = 30%-50%
            found = true;
        }
        else
            for(int i(0); ( (! found) && (i < Player->Armor.size()) ); i++) {
                if (Player->Armor.at(i)->Name() == tr("")){
                    delete Player->Armor[i];
                    Player->Armor[i] = MainWindow::makeEqByGrade(pq_equip_armor, Player->Level.toInt());
                    Player->Gold -= gConfig->fnPercent(Player->Gold, ((rand() % 3 + 2) * 10) ); // cost = 20%-40%
                    found=true;
                }
            }

    if (! found) {
        // if all filled, then upgrade
        select = (t_pq_equip)(rand() % 3); // random equip
        switch(select) {
        case pq_equip_weapon:
            equip = MainWindow::upgradeEq(select, Player->Weapon->Grade());
            delete Player->Weapon;
            Player->Weapon = equip;
            Player->Gold -= gConfig->fnPercent(Player->Gold, ((rand() % 3 + 4) * 10) ); // cost = 40%-60%
            break;;
        case pq_equip_shield:
            equip = MainWindow::upgradeEq(select, Player->Sheild->Grade());
            delete Player->Sheild;
            Player->Sheild = equip;
            Player->Gold -= gConfig->fnPercent(Player->Gold, ((rand() % 3 + 4) * 10) ); // cost = 40%-60%
            break;;
        case pq_equip_armor:
            pick = rand() % Player->Armor.size();
            equip = MainWindow::upgradeEq(select, Player->Armor.at(pick)->Grade());
            delete Player->Armor[pick];
            Player->Armor[pick] = equip;
            Player->Gold -= gConfig->fnPercent(Player->Gold, ((rand() % 3 + 3) * 10) ); // cost = 30%-50%
            break;;
        }
    }

    MainWindow::updEquipTbl();
}

c_Item* MainWindow::makeEqByGrade(t_pq_equip eqtype, int grade)
{
    c_Item* equip = new c_Item;

    switch(eqtype) {

    case pq_equip_weapon:

        equip->makeClosestGrade(eqtype, grade);

        // 2 possible mods, 50% chnc each: player level affects pos/neg
        for(int i(0); i < 2; i++) {
            if (rand() % 2 == 0) {
                if (rand() % Player->Level.toInt() < 5) equip->addWeaponNegMod();
                else equip->addWeaponMod();
            }
        }

        // set bonus to make up differance in grade
        equip->setBonus(grade - equip->Grade());

        break;;

    case pq_equip_shield:

        equip->makeClosestGrade(eqtype, grade);

        // 2 possible mods, 50% chnc each: player level affects pos/neg
        for(int i(0); i < 2; i++) {
            if (rand() % 2 == 0) {
                if (rand() % Player->Level.toInt() < 5) equip->addDefNegMod();
                else equip->addDefMod();
            }
        }

        // set bonus to make up differance in grade
        equip->setBonus(grade - equip->Grade());

        break;;

    case pq_equip_armor:

        equip->makeClosestGrade(eqtype, grade);

        // 2 possible mods, 50% chnc each: player level affects pos/neg
        for(int i(0); i < 2; i++) {
            if (rand() % 2 == 0) {
                if (rand() % Player->Level.toInt() < 5) equip->addDefNegMod();
                else equip->addDefMod();
            }
        }

        // set bonus to make up differance in grade
        equip->setBonus(grade - equip->Grade());

        break;;
    }

    return equip;
}

c_Item* MainWindow::upgradeEq(t_pq_equip eqtype, int grade)
{
    c_Item* equip = new c_Item;

    switch (eqtype) {
    case pq_equip_weapon:
        equip = MainWindow::makeEqByGrade(eqtype, grade + 1);
        break;;
    case pq_equip_shield:
        equip = MainWindow::makeEqByGrade(eqtype, grade + 1);
        break;;
    case pq_equip_armor:
        equip = MainWindow::makeEqByGrade(eqtype, grade + 1);
        break;;
    }

    return equip;
}

void MainWindow::updEquipTbl()
{
    // wipe
    ui->tbl_equipment->clearContents();
    ui->tbl_equipment->setRowCount(2 + Player->Armor.size());

    // reload equipment from player and config
    ui->tbl_equipment->setRowCount(gConfig->Equips.size());
    for (int i = 0; i < gConfig->Equips.size(); i++) {
        ui->tbl_equipment->setItem( i, 0, new QTableWidgetItem(gConfig->Equips.at(i)) );
    }
    ui->tbl_equipment->setItem(0, 1, new QTableWidgetItem(Player->Weapon->Name()) );
    ui->tbl_equipment->setItem(1, 1, new QTableWidgetItem(Player->Sheild->Name()) );
    for (int i(0); i < Player->Armor.size(); i++) {
         ui->tbl_equipment->setItem(i + 2, 1, new QTableWidgetItem(Player->Armor.at(i)->Name()) );
    }
}

void MainWindow::updStatsTbl()
{
    // wipe
    ui->tbl_stats->clearContents();
    ui->tbl_stats->setRowCount(2 + gConfig->PrimeStats.size());

    // stats
    for (int i = 0; i < gConfig->PrimeStats.size(); i++) {
        ui->tbl_stats->setItem(i, 0, new QTableWidgetItem(gConfig->PrimeStats.at(i)));
    }
    ui->tbl_stats->setItem(ui->tbl_stats->rowCount() - 2, 0, new QTableWidgetItem("HP Max"));
    ui->tbl_stats->setItem(ui->tbl_stats->rowCount() - 1, 0, new QTableWidgetItem("MP Max"));

    //      Load stats from player
    ui->tbl_stats->setItem(0, 1, new QTableWidgetItem(Player->STR));
    ui->tbl_stats->setItem(1, 1, new QTableWidgetItem(Player->INT));
    ui->tbl_stats->setItem(2, 1, new QTableWidgetItem(Player->WIS));
    ui->tbl_stats->setItem(3, 1, new QTableWidgetItem(Player->DEX));
    ui->tbl_stats->setItem(4, 1, new QTableWidgetItem(Player->CON));
    ui->tbl_stats->setItem(5, 1, new QTableWidgetItem(Player->CHA));
    ui->tbl_stats->setItem(6, 1, new QTableWidgetItem(Player->HPMax));
    ui->tbl_stats->setItem(7, 1, new QTableWidgetItem(Player->MPMax));

}

void MainWindow::updSpellTbl()
{
    // clear table
    ui->tbl_spells->clearContents();

    // spell list
    ui->tbl_spells->setRowCount(Player->Spells.size());
    for (int i = 0; i < Player->Spells.size(); i++) {
        ui->tbl_spells->setItem( i, 0, new QTableWidgetItem(Player->Spells.at(i)->Name()) );
        ui->tbl_spells->setItem( i, 1, new QTableWidgetItem(Player->Spells.at(i)->Level()) );
    }
}
