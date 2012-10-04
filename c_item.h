#ifndef C_ITEM_H
#define C_ITEM_H

#include <QString>
#include "pq7_config.h"

class c_Item
{
public:
    c_Item();

    int Weight;

    // accessors
    QString Name();
    void setName(QString setname);

    int Bonus();
    void setBonus(int setbonus);

    int Appraisal();

    int Grade();


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

    void clear();

private:
    QString basename;
    int     basegrade;

    QStringList modifiers;
    QList<bool> modprefix;
    QList<int>  modgrades;

    int bonus;
};

#endif // C_ITEM_H
