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
//        if      (itemType == pq_equip_weapon) factor += 8;
//        else if (itemType == pq_equip_shield) factor += 6;
//        else if (itemType == pq_equip_armor)  factor += 7;

        if      (itemType == pq_equip_weapon) factor += 18;
        else if (itemType == pq_equip_shield) factor += 26;
        else if (itemType == pq_equip_armor)  factor += 22;

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
        //g += (float)g * ((float)modgrades.at(i)/5.0) ;
        g += modgrades.at(i);
    }

    // add bonus
    g += (float)itemBonus;

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
    //basegrade = 25 + (rand() % 20 - 10); // [15..34]
    basegrade = 15 + (rand() % 20 - 10); // [5..19]
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

Json::Value c_Item::save()
{
    Json::Value root;
    std::string mKey = "Item";

    //t_pq_equip itemType;
    //fh << (int)itemType << std::endl;
    root["Type"] = (int)itemType;

    //QString basename;
    //int     basegrade;
    root["Name"] = basename.toStdString();
    root["BaseGrade"] = basegrade;

    /*
    QStringList modifiers;
    QList<bool> modprefix;
    QList<int>  modgrades;
    */
    root["Modifiers"] = c_Item::modListToArray(modifiers, modprefix, modgrades);
    //int itemBonus;
    root["Bonus"] = itemBonus;

    //int price;
    root["Price"] = price;

    //int armorSlot;
    root["ArmorSlot"] = armorSlot;

    /*
    int Weight;
    */
    root["Weight"] = Weight;

    return root;
}

void c_Item::load(Json::Value itemRoot)
{
    //t_pq_equip itemType;
    itemType = (t_pq_equip) itemRoot.get("Type", 0).asInt();

    //QString basename;
    //int     basegrade;
    basename = QString::fromStdString(itemRoot.get("Name", "").asString());
    basegrade = itemRoot.get("BaseGrade", 0).asInt();

    /*
    QStringList modifiers;
    QList<bool> modprefix;
    QList<int>  modgrades;
    */
    c_Item::arrayToModList(itemRoot.get("Modifiers", Json::arrayValue),
                           modifiers,
                           modprefix,
                           modgrades
                           );

    //int itemBonus;
    itemBonus = itemRoot.get("Bonus", 0).asInt();

    //int price;
    price = itemRoot.get("Price", 0).asInt();

    //int armorSlot;
    armorSlot = itemRoot.get("ArmorSlot", 0).asInt();

    //int Weight;
    Weight = itemRoot.get("Weight", 1).asInt();
}

Json::Value c_Item::modListToArray(QStringList &mList, QList<bool> &pList, QList<int> &gList)
{
    Json::Value array, set;
    array.clear();

    for (int i=0; i < mList.size(); i++)
    {
        set.clear();

        set.append(mList.at(i).toStdString());
        set.append(pList.at(i));
        set.append(gList.at(i));

        array.append(set);
    }
    return array;
}

void c_Item::arrayToModList(Json::Value array, QStringList &mList, QList<bool> &pList, QList<int> &gList)
{
    Json::Value set;

    // if not already - wipe lists
    mList.clear();
    pList.clear();
    gList.clear();

    // cycle through items
    for (Json::ArrayIndex i=0; i < array.size(); i++)
    {
        //set.clear(); //needed?
        set = array.get(i,Json::arrayValue);

        // read in ordered set of values
        mList.append(QString::fromStdString(set.get((Json::ArrayIndex)0, "").asString()));
        pList.append(set.get((Json::ArrayIndex)1, false).asBool());
        gList.append(set.get((Json::ArrayIndex)2, 0).asInt());
    }
}
