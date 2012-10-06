#ifndef C_ITEM_H
#define C_ITEM_H

#include <cmath>
#include <QString>
#include "pq7_config.h"

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
};

#endif // C_ITEM_H
