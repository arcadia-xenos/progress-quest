#include "c_item.h"

c_Item::c_Item()
{
    c_Item::clear();
}

QString c_Item::Name()
{
    QString rtn;
    rtn.clear();

    // start with bonus
    if (bonus != 0) {
        if (bonus > 0) rtn += "+";
        rtn += QString().number(bonus);
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
    return bonus;
}

void c_Item::setBonus(int setbonus)
{
    bonus = setbonus;
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
    g += bonus;

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

void c_Item::clear()
{
    basename.clear();
    basegrade = 0;
    modifiers.clear();
    modgrades.clear();
    modprefix.clear();
    bonus = 0;
    Weight =0;
}
