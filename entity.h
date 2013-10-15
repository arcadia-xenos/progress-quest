#ifndef ENTITY_H
#define ENTITY_H

#include <cmath>
#include "c_spell.h"
#include "c_item.h"
#include "pq7_config.h"
#include <iostream>
#include <fstream>

#include <QObject>
#include <QString>

#include "json/json.h"

class Entity : public QObject
{
    Q_OBJECT

public:
    explicit Entity(QObject *parent = 0);

    // traits (Voc=Vocation)
    QString Name, Race, Voc, Level;

    // stats
    QString STR, INT, WIS, DEX, CON, CHA, HPMax, MPMax;

    // experience
    QString XP;
    qulonglong maxXP();



    // spells
    QList<c_Spell*> Spells;

    // equipment
    c_Item*         Weapon;
    c_Item*         Sheild;
    QList<c_Item*>  Armor;

    // used for buying new equipment
    c_Item*         Purchase;
    QString         purchType();
    void            setPurchNew(bool is_new);

    // inventory
    QList<c_Item*> Inventory;
    QList<int> Quantity;
    int Encumbrance();
    int maxEncumbrance();

    // Gold (ah, weightless gold)
    int Gold;

    // random methods - used in init
    QString nameRand();
    QString raceRand();
    QString vocRand();
    void incrLevel();

    Json::Value save();
    void load(Json::Value entityRoot);

signals:
    void levelUp();

public slots:

    
private:

    bool isNewPurchase;

    // methods
    QString statRand(int basevalue, int offset);
    int fnFib(int value);

    // save / load helper
    Json::Value spellListToArray(QList<c_Spell *> &list);
    Json::Value itemListToArray(QList<c_Item *> &list);
    Json::Value invListToArray(QList<c_Item *> &iList, QList<int> &nList);

    QList<c_Spell *> arrayToSpellList(Json::Value array);
    QList<c_Item *> arrayToItemList(Json::Value array);
    void arrayToInvList(Json::Value array, QList<c_Item *> &iList, QList<int> &nList);
};

#endif // ENTITY_H
