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
    itemType = pq_equip_any;
    price = 0;
    armorSlot = 0;
}

// TODO: allviate processing on multiple calls
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

void c_Item::setName(QString itemName)
{
    basename = itemName;
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

    // factored appraisal
    if (price == 0) {
        int factor(0);
        int g = c_Item::Grade();

        // set super low grade
        if (g < 0) {
            g = 1;
            factor = 3;
        }
        // factor by grade
        else if (g < 20)    factor = 7;
        else if (g < 50)    factor = 5;
        else if (g < 100)   factor = 3;
        else                factor = 1;

        // factor by type (any = by grade only)
        if      (itemType == pq_equip_weapon) factor += 800;
        else if (itemType == pq_equip_shield) factor += 600;
        else if (itemType == pq_equip_armor)  factor += 700;

        // set price
        price = g * factor;
    }

    // appraised or set price
    return price;
}

void c_Item::setPrice(int gold)
{
    price = gold;
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

t_pq_equip c_Item::Type()
{
    return itemType;
}

void c_Item::setType(t_pq_equip eqType)
{
    itemType = eqType;
}


// armor slot access is used by equip purchase
void c_Item::setASlot(int slot)
{
    armorSlot=slot;
}

int c_Item::getASlot()
{
    return armorSlot;
}

void c_Item::makeWeapon()
{
    QStringList cdata;
    cdata = gConfig->Weapons.at(rand() % gConfig->Weapons.size()).split("|");
    basename  = cdata.at(0);            //name
    basegrade = cdata.at(1).toInt();    //value
    Weight = 1;
    itemType = pq_equip_weapon;
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
    itemType = pq_equip_shield;
}

void c_Item::makeArmor()
{
    QStringList cdata;
    cdata = gConfig->Armors.at(rand() % gConfig->Armors.size()).split("|");
    basename  = cdata.at(0);            //name
    basegrade = cdata.at(1).toInt();    //value
    Weight = 1;
    itemType = pq_equip_armor;
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
    itemType = pq_equip_any;
}

void c_Item::makeSpecial()
{
    basename = gConfig->Specials.at(rand() % gConfig->Specials.size());
    basegrade = 50 + (rand() % 20 - 10); // [40..59]
    Weight = 1;
    itemType = pq_equip_any;
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
    t_pq_equip eqSelect = iType;

    // handle "any" selection
    if (eqSelect == pq_equip_any)
        eqSelect = static_cast<t_pq_equip>(rand() % 3); //random type

    // choose list by type
    switch(eqSelect) {
    case pq_equip_weapon:
        itemList = &gConfig->Weapons;
        break;;
    case pq_equip_shield:
        itemList = &gConfig->Shields;
        break;;
    case pq_equip_armor:
        itemList = &gConfig->Armors;
        break;;
    case pq_equip_any:
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
    itemType = eqSelect;

}

void c_Item::save(std::ofstream &fh)
{
    //t_pq_equip itemType;
    fh << (int)itemType << std::endl;

    //QString basename;
    //int     basegrade;
    fh << basename.toStdString() << std::endl;
    fh << basegrade << std::endl;

    /*
    QStringList modifiers;
    QList<bool> modprefix;
    QList<int>  modgrades;
    */
    fh << modifiers.size() << std::endl;
    for (int i=0; i < modifiers.size(); i++) {
        //fh << modifiers.at(i).toStdString() << " ";
        fh << modifiers.at(i).toStdString() << std::endl;
    }
    //fh << std::endl; // end of line
    fh << modprefix.size() << std::endl;
    for (int i=0; i < modprefix.size(); i++) {
        if (modprefix.at(i))
            fh << "true" << std::endl;
        else
            fh << "false" << std::endl;
        //fh << modprefix.at(i) ? "true" : "false" << std::endl;
    }
    fh << modgrades.size() << std::endl;
    for (int i=0; i < modgrades.size(); i++) {
        fh << modgrades.at(i) << std::endl;
    }

    //int itemBonus;
    fh << itemBonus << std::endl;

    //int price;
    fh << price << std::endl;

    //int armorSlot;
    fh << armorSlot << std::endl;
}

//void c_Item::load(std::ifstream fh)
//{
//    // locals to help load back values
//    int arrSize;
//    QString boolValue;

//    //t_pq_equip itemType;
//    fh >> itemType;

//    //QString basename;
//    //int     basegrade;
//    fh >> basename;
//    fh >> basegrade;

//    /*
//    QStringList modifiers;
//    QList<bool> modprefix;
//    QList<int>  modgrades;
//    */
//    fh >> arrSize;
//    for (int i=0; i < arrSize; i++) {
//        fh >> modifiers.at(i);
//    }
//    fh >> arrSize;
//    for (int i=0; i < arrSize; i++) {
//        fh >> boolValue;
//        if (boolValue = tr("true"))
//            modprefix.at(i) = true;
//        else
//            modprefix.at(i) = false;
//    }
//    fh >> arrSize;
//    for (int i=0; i < arrSize; i++) {
//        fh >> modgrades.at(i);
//    }

//    //int itemBonus;
//    fh >> itemBonus;

//    //int price;
//    fh >> price;

//    //int armorSlot;
//    fh >> armorSlot;
//}
