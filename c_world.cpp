#include "c_world.h"

c_World::c_World(QObject *parent) :
    QObject(parent)
{
    Player = new Entity;
    Monster = new c_Monster;
    Act = 0;
    Action  = "";
    State = pq_state_reserved_1;
    pb_action = 0;
    pb_encumbrance = 0;
    pb_experience = 0;
    pb_plot = 0;
    pb_quest = 0;
    //c_World::initPlayer();
    jsonRoot.clear();
}

void c_World::initPlayer()
/*
 *      Player creation
 *
 *  calls:      makeEqByGrade
 *  rtns:       void
 *  affects:    c_World::Player
 *
 *  Relies on entity constructor to baseline some values,
 *  fills in and overwrites others that are player
 *  specific.
 */
{
    c_Spell *spell = new c_Spell;
    //c_Item *weapon = new c_Item;
    //c_Item *sheild = new c_Item;
    //QList<c_Item*> armor;
    int index(0), i(0);

    // rand traits
    Player->Name = Player->nameRand();
    Player->Race = Player->raceRand();
    Player->Voc  = Player->vocRand();

    // add starting spell
    spell->setRandName();
    Player->Spells.append(spell);

    // add starting weapon (a weak one =D )
    Player->Weapon = c_World::makeEqByGrade(pq_equip_weapon, -4);

    // Look ma, no sheild!
    Player->Sheild = new c_Item;

    // add two starting armors (weak, random)
    for(int i(0); i < 9; i++) {
        Player->Armor.append(new c_Item);
    }
    // 2 *unique* armors - not the same one twice
    do {
        index = rand() % Player->Armor.size();
        if (Player->Armor.at(index)->Name() == tr("")) {
            delete Player->Armor[index];
            Player->Armor[index] = c_World::makeEqByGrade(pq_equip_armor, -2);
            i++;
        }
    } while (i < 2);

    // finally, money to drink at the bar with
    Player->Gold = 25;
}

c_Item* c_World::makeEqByGrade(t_pq_equip eqtype, int grade)
/*
 *      Make Equipment By Grade
 *
 *  calls:      c_Item methods
 *  rtns:       c_Item (of specified level)
 *  affects:    none
 *
 *  Used by various to produce items of specific type at
 *  requested level (grade)
 */
{
    c_Item* equip = new c_Item;
    t_pq_equip eqSelect = eqtype;

    // handle "any" type
    if (eqSelect == pq_equip_any)
        eqSelect = static_cast<t_pq_equip>(rand() % 3);

    // main types
    switch(eqSelect) {

    case pq_equip_weapon:

        equip->makeClosestGrade(eqSelect, grade);

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

        equip->makeClosestGrade(eqSelect, grade);

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

        equip->makeClosestGrade(eqSelect, grade);

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

    case pq_equip_any:
        break;;
    }

    return equip;
}

void c_World::save()
{

    std::ofstream fh_saveFile;
    fh_saveFile.open("pq_savefile_test.pqd",std::ios::trunc);

    if (fh_saveFile.is_open()) {
        /*
        int Act;
        QString Action;
        t_pq_state State;
        */
        jsonRoot["World"]["Act"] = Act;
        jsonRoot["World"]["Action"] = Action.toStdString();
        jsonRoot["World"]["State"] = (int)State;
//        fh_saveFile << Act << std::endl;
//        fh_saveFile << Action.toStdString() << std::endl;
//        fh_saveFile << (int)State << std::endl;

        /*
        int pb_action;
        int pb_experience;
        int pb_encumbrance;
        int pb_plot;
        int pb_quest;
        */
        jsonRoot["World"]["pb_action"] = pb_action;
        jsonRoot["World"]["pb_experience"] = pb_experience;
        jsonRoot["World"]["pb_encumbrance"] = pb_encumbrance;
        jsonRoot["World"]["pb_plot"] = pb_plot;
        jsonRoot["World"]["pb_quest"] = pb_quest;
//        fh_saveFile << pb_action << std::endl;
//        fh_saveFile << pb_experience << std::endl;
//        fh_saveFile << pb_encumbrance << std::endl;
//        fh_saveFile << pb_plot << std::endl;
//        fh_saveFile << pb_quest << std::endl;

        //Entity* Player;
        jsonRoot["World"]["Player"] = Player->save();

        //c_Monster* Monster;
        jsonRoot["World"]["Monster"] = Monster->save();

    }
    else
    {
        // file failed to open... wtf
    }
    fh_saveFile << jsonRoot << std::endl;
    fh_saveFile.close();
}

//void c_World::load()
//{
//    std::ifstream fh_saveFile;
//    fh_saveFile.open("pq_savefile_test");

//    if (fh_saveFile.is_open()) {

//        //Entity* Player;
//        //Player->load(fh_saveFile);

//        //c_Monster* Monster;
//        //Monster->load(fh_saveFile);

//        /*
//        int Act;
//        QString Action;
//        t_pq_state State;
//        */
////        fh_saveFile >> Act;
////        fh_saveFile >> Action;
////        fh_saveFile >> State;

//        /*
//        int pb_action;
//        int pb_experience;
//        int pb_encumbrance;
//        int pb_plot;
//        int pb_quest;
//        */
////        fh_saveFile >> pb_action;
////        fh_saveFile >> pb_experience;
////        fh_saveFile >> pb_encumbrance;
////        fh_saveFile >> pb_plot;
////        fh_saveFile >> pb_quest;
//    }
//    else
//    {
//        // file failed to open... wtf
//    }
//    fh_saveFile.close();
//}
