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
    isLoaded = false;
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
 *  rtns:       c_Item* (of specified level)
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
    c_World::save("pq_savefile.pqd");
}

void c_World::save(QString filename)
{
    Json::Value root;
    std::string mKey = "World";

    std::ofstream saveFile;
    saveFile.open(filename.toStdString().c_str(),std::ios::trunc);

    if (saveFile.is_open()) {
        /*
        int Act;
        QString Action;
        t_pq_state State;
        */
        root[mKey]["Act"] = Act;
        root[mKey]["Action"] = Action.toStdString();
        root[mKey]["ActionTime"] = actionTime;
        root[mKey]["State"] = (int)State;

        /*
        int pb_action;
        int pb_experience;
        int pb_encumbrance;
        int pb_plot;
        int pb_quest;
        */
        root[mKey]["pb_action"] = pb_action;
        root[mKey]["pb_experience"] = pb_experience;
        root[mKey]["pb_encumbrance"] = pb_encumbrance;
        root[mKey]["pb_plot"] = pb_plot;
        root[mKey]["pb_quest"] = pb_quest;

        /*
        QStringList quests;
        */
        root[mKey]["Quests"] = c_World::listToArray(quests);

        //Entity* Player;
        root[mKey]["Player"] = Player->save();

        //c_Monster* Monster;
        root[mKey]["Monster"] = Monster->save();

    }
    else
    {
        // file failed to open... wtf
    }

    saveFile << root << std::endl;

    saveFile.close();
}

void c_World::load()
{
    c_World::load(QString::fromStdString("pq_savefile.pqd"));
}

void c_World::load(QString filename)
{
    Json::Value root;
    Json::Reader readSave;

    std::ifstream saveFile;
    saveFile.open(filename.toStdString().c_str());

    // open file
    if (saveFile.is_open())
    {
        // parse json
        if (! readSave.parse(saveFile, root, false))
        {
            // failed to read
            //std::cerr << "JSON Parse fail on file " << filename << ":" << std::endl;
            //std::cerr << readSave.getFormatedErrorMessages();
            //exit (1);
            QMessageBox mBox;
            mBox.setWindowTitle(QString::fromStdString("JSON Parse fail on file ") + filename );
            mBox.setText(QString::fromStdString(readSave.getFormatedErrorMessages()));
            mBox.exec();
            exit(1);
        }
    }
    else
    {
        // file fail
        //std::cerr << "file " << filename << " failed to open" << std::endl;
        //exit(1);
        QMessageBox mBox;
        mBox.setWindowTitle(QString::fromStdString("Progress Quest load ") + filename);
        mBox.setText(QString::fromStdString("Failed to open"));
        mBox.exec();
        exit(1);
    }
    saveFile.close();
    // end file parsing

    //chain the json loader
    c_World::load(root);
}

void c_World::load(Json::Value root)
{
    // unpack world values from anonymous main json object
    root = root.get("World", Json::Value::null);

    //Entity* Player;
    Player->load(root.get("Player", Json::objectValue));

    //c_Monster* Monster;
    Monster->load(root.get("Monster", Json::objectValue));

    /*
        int Act;
        QString Action;
        t_pq_state State;
    */
    Act     = root.get("Act", 99).asInt();
    Action  = QString::fromStdString(root.get("Action", "Knock knock...").asString());
    actionTime = root.get("ActionTime", 50).asInt();
    State   = (t_pq_state)root.get("State", 0).asInt();

    /*
        QStringList quests;
    */
    // if not found, passes empty json array to helper which will return empty qstringlist
    quests = c_World::arrayToList(root.get("Quests", Json::arrayValue));

    /*
        int pb_action;
        int pb_experience;
        int pb_encumbrance;
        int pb_plot;
        int pb_quest;
    */
    pb_action       = root.get("pb_action", 99).asInt();
    pb_experience   = root.get("pb_experience", 99).asInt();
    pb_encumbrance  = root.get("pb_encumbrance", 99).asInt();
    pb_plot         = root.get("pb_plot", 99).asInt();
    pb_quest        = root.get("pb_quest", 99).asInt();

    // set loaded flag
    isLoaded = true;
}

// save helper for quest list
Json::Value c_World::listToArray(QStringList &list)
{
    Json::Value array;
    array.clear();
    for (int i=0; i < list.size(); i++)
    {
        array.append(list.at(i).toStdString());
    }
    return array;
}


// load helper for quest list
QStringList c_World::arrayToList(Json::Value array)
{
    QStringList list;
    list.clear();

    // load json array to qstring list
    for (unsigned int i=0; i < array.size(); i++)
    {
        list.append( QString::fromStdString(array[i].asString()) );
    }
    return list;
}
