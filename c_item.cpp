#include "c_item.h"

c_Item::c_Item()
{
    c_Item::clear();
}

void c_Item::clear()
{
    basename.clear();
    basegrade = 0;
    modifiers.clear();
    modgrades.clear();
    modprefix.clear();
    itemBonus = 0;
    Weight =0;
}

QString c_Item::Name()
{
    QString rtn;
    rtn.clear();

    // start with bonus
    if (itemBonus != 0) {
        if (itemBonus > 0) rtn += "+";
        rtn += QString().number(itemBonus);
        rtn += " ";
    }

    // apply prefix modifiers
    for(int i = 0; i < modifiers.size(); i++) {
        if (modprefix.at(i)) {
            rtn += modifiers.at(i);
            rtn += " ";
        }
    }

    // add basename
    rtn += basename;

    // apply postfix mods
    for(int i = 0; i < modifiers.size(); i++) {
        if (! modprefix.at(i)) {
            rtn += " ";
            rtn += modifiers.at(i);
        }
    }

    return rtn;
}

void c_Item::setName(QString setname)
{
    basename = setname;
}


int c_Item::Bonus()
{
    return itemBonus;
}

void c_Item::setBonus(int bonus)
{
    itemBonus = bonus;
}

int c_Item::Appraisal()
{
    int price = c_Item::Grade();

    // lowest price value
    if (price < 1)
        price = 0; //grats, you're worthless!

    return price;
}

int c_Item::Grade()
{
    int g(0);

    // base value
    g += basegrade;

    // assess mods
    for(int i(0); i < modgrades.size(); i++) {
        g += modgrades.at(i);
    }

    // add bonus
    g += itemBonus;

    return g;
}

void c_Item::makeWeapon()
{
    QStringList cdata;
    cdata = gConfig->Weapons.at(rand() % gConfig->Weapons.size()).split("|");
    basename  = cdata.at(0);            //name
    basegrade = cdata.at(1).toInt();    //value
    Weight = 1;

}

void c_Item::addWeaponMod()
{
    QStringList cdata;
    cdata = gConfig->OffenseAttrib.at(rand() % gConfig->OffenseAttrib.size()).split("|");
    modifiers << cdata.at(0);            //mod
    modgrades << cdata.at(1).toInt();    //value
    modprefix << true;
}

void c_Item::addWeaponNegMod()
{
    QStringList cdata;
    cdata = gConfig->OffenseBad.at(rand() % gConfig->OffenseBad.size()).split("|");
    modifiers << cdata.at(0);            //mod
    modgrades << cdata.at(1).toInt();    //value
    modprefix << true;
}

void c_Item::makeSheild()
{
    QStringList cdata;
    cdata = gConfig->Shields.at(rand() % gConfig->Shields.size()).split("|");
    basename  = cdata.at(0);            //name
    basegrade = cdata.at(1).toInt();    //value
    Weight = 1;

}

void c_Item::makeArmor()
{
    QStringList cdata;
    cdata = gConfig->Armors.at(rand() % gConfig->Armors.size()).split("|");
    basename  = cdata.at(0);            //name
    basegrade = cdata.at(1).toInt();    //value
    Weight = 1;

}

void c_Item::addDefMod()
{
    QStringList cdata;
    cdata = gConfig->DefenseAttrib.at(rand() % gConfig->DefenseAttrib.size()).split("|");
    modifiers << cdata.at(0);            //mod
    modgrades << cdata.at(1).toInt();    //value
    modprefix << true;
}

void c_Item::addDefNegMod()
{
    QStringList cdata;
    cdata = gConfig->DefenseBad.at(rand() % gConfig->DefenseBad.size()).split("|");
    modifiers << cdata.at(0);            //mod
    modgrades << cdata.at(1).toInt();    //value
    modprefix << true;
}


void c_Item::makeBitem()
{
    basename = gConfig->BoringItems.at(rand() % gConfig->BoringItems.size());
    basegrade = 1;
    Weight = 1;

}

void c_Item::makeSpecial()
{
    basename = gConfig->Specials.at(rand() % gConfig->Specials.size());
    basegrade = 50 + (rand() % 20 - 10); // [40..59]
    Weight = 1;

}

void c_Item::addOfMod()
{
    QString item_of;
    item_of = "of ";
    item_of += gConfig->ItemOfs.at(rand() % gConfig->ItemOfs.size());
    modifiers << item_of;
    modgrades << 250 + (rand() % 100 - 200); // [150..349]
    modprefix << false;
}

void c_Item::addAdjMod()
{
    modifiers <<  gConfig->ItemAttrib.at(rand() % gConfig->ItemAttrib.size());
    modgrades << 500 + (rand() % 100 - 200); // [400..599]
    modprefix << true;
}

void c_Item::makeClosestGrade(t_pq_equip iType, int grade)
{
    QStringList* itemList;

    switch(iType) {
    case pq_equip_weapon:
        itemList = &gConfig->Weapons;
        break;;
    case pq_equip_shield:
        itemList = &gConfig->Shields;
        break;;
    case pq_equip_armor:
        itemList = &gConfig->Armors;
        break;;
    }

    bool found(false);
    int index(0), curGrade(0), lastDiff(0), closestGrade(0);
    QStringList cdata, listFound;

    // traverse all weapons - list exacts / find closest
    do {
        // extract grade from current item
        cdata = itemList->at(index).split("|");
        curGrade = cdata.at(1).toInt();

        // check equals - toggle found / add name
        if (curGrade == grade) {
            found = true;
            listFound.append(cdata.at(0)); // add name
        }
        else
        {
            // prime lastDiff (make larger than 0)
            if (lastDiff == 0) lastDiff = abs(grade - curGrade);

            // find closest grade
            if (abs(grade - curGrade) <= lastDiff) {
                lastDiff = abs(grade - curGrade);
                closestGrade = curGrade;
            }
        }
        index++;

    } while (index < itemList->size());

    // no exact grades found
    if (! found)
    {
        // use closest grade - find all -> listFound
        for (index=0; index < itemList->size(); index++) {
            cdata = itemList->at(index).split("|");
            if (cdata.at(1).toInt() == closestGrade)
                listFound.append(cdata.at(0));
        }
    }

    // randomize from names list (closest or exact)
    basename = listFound.at(rand() % listFound.size());
    if (found) basegrade = grade;
    else basegrade = closestGrade;
    Weight = 1;
}

