#ifndef C_ITEM_H
#define C_ITEM_H

#include <cmath>
#include <QString>
#include <QObject>
#include "pq7_config.h"
#include <iostream>
#include <fstream>

#include "json/json.h"

class c_Item
{
public:
    c_Item();

    int Weight;

    // accessors
    QString Name();
    void setName(QString itemName);

    int Bonus();
    void setBonus(int bonus);

    int Appraisal();
    void setPrice(int gold);

    int Grade();

    t_pq_equip Type();
    void setType(t_pq_equip eqType);

    void setASlot(int slot);
    int getASlot();


    // methods
    void makeWeapon();
    void addWeaponMod();
    void addWeaponNegMod();

    void makeSheild();
    void makeArmor();
    void addDefMod();
    void addDefNegMod();

    void makeBitem();
    void makeSpecial();

    void addOfMod();
    void addAdjMod();

    void makeClosestGrade(t_pq_equip iType, int grade);

    void clear();
    Json::Value save();
    void load(Json::Value itemRoot);

private:
    t_pq_equip itemType;

    QString basename;
    int     basegrade;

    QStringList modifiers;
    QList<bool> modprefix;
    QList<int>  modgrades;

    int itemBonus;

    int price;

    int armorSlot;

    // save / load helpers
    Json::Value modListToArray(QStringList &mList, QList<bool> &pList, QList<int> &gList);
    void arrayToModList(Json::Value array, QStringList &mList, QList<bool> &pList, QList<int> &gList);

};

#endif // C_ITEM_H
