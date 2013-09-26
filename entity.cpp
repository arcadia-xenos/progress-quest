#include "entity.h"

Entity::Entity(QObject *parent) :
    QObject(parent)
{
    // traits
    Name = "";
    Race = "";
    Voc = "";
    Level = "1";

    // stats
    STR = statRand(12,6);
    INT = statRand(12,6);
    WIS = statRand(12,6);
    DEX = statRand(12,6);
    CON = statRand(12,6);
    CHA = statRand(12,6);

    HPMax = statRand(22,10);
    MPMax = statRand(12,8);

    XP = "0";

    // spells / equip aren't freely given
    Inventory.clear();
    Quantity.clear();
    Spells.clear();
    Armor.clear();

    isNewPurchase = true;
}

int Entity::Encumbrance()
{
    int totWeight(0);
    for (int i = 0; i < Inventory.size(); i++) {
        totWeight += Inventory.at(i)->Weight * Quantity.at(i);
    }
    return totWeight;
}

QString Entity::purchType()
{
    if (isNewPurchase)
        return "new";
    else
        return "upgrade";
}
void Entity::setPurchNew(bool is_new)
{
    isNewPurchase = is_new;
}

qulonglong Entity::maxXP()
{
    // xp for next level is calculated by exp curve
    // see pq7_level_advancement_curvatures.ggb (geogebra4 file)
    // for more info

    float Lv = Level.toFloat();
    float base = 1130.0; // xp at bend level
    float curvature = 1.09512; // coeffecient
    float bend = 20.0; // start bending at level

    return (int)(base * pow(curvature, (Lv - bend)) );
}

int Entity::maxEncumbrance()
{
    return STR.toInt() + 15;
}

QString Entity::statRand(int basevalue, int offset)
{
    return QString::number(rand() % basevalue + offset);
}

QString Entity::nameRand()
{
    QString build;
    QStringList nameparts;
    nameparts << "zul" << "arg" << "eb" << "cork" << "dar"
              << "dor" << "sar" << "nar" << "en" << "mor"
              << "goth" << "buf" << "er" << "ag" << "ort"
              << "tor" << "tar" << "grim" << "val" << "kul"
              << "kun" << "xi" << "ja" << "ju" << "or"
              << "mard" << "ed" << "chu" << "thi" << "oub"
              << "sch" << "chi" << "ki" << "lo" << "lun";

    for (int i =0; i < 3; i++) {
        build += nameparts.at(rand() % nameparts.size());
    }

    build = build.left(1).toUpper()+build.mid(1);

    return build;
}

QString Entity::raceRand()
{
    QStringList cdata;
    cdata = gConfig->Races.at(rand() % gConfig->Races.size()).split("|");
    return cdata.at(0); // race name
}

QString Entity::vocRand()
{
    QStringList cdata;
    cdata = gConfig->Klasses.at(rand() % gConfig->Klasses.size()).split("|");
    return cdata.at(0); // class name
}

int Entity::fnFib(int value)
{
    // sanity
    if (value < 1) return 0;

    QList<int> build;

    // seed fibonacci seq (first 3)
    build.clear();
    build.append(0);
    build.append(1);
    build.append(1);

    // first 3 values already figured
    if (value <= 3) {
        return build.at(value - 1);
    }
    else
    {
        // calculate 4 and higher
        for (int i(3); i <= value; i++)
        {
            // exchange down
            build[0] = build.at(1);
            build[1] = build.at(2);

            // new value (f(n) = f(n-1) + f(n-2))
            build[2] = build.at(1) + build.at(0);
        }
     }

    return build.at(2);
}

void Entity::incrLevel()
{
    XP = tr("0");
    Level = QString().number(Level.toInt() + 1);
}

Json::Value Entity::save()
{
    Json::Value root;
    std::string mKey = "Entity";
    /*
    QString Name, Race, Voc, Level;
    */
    root[mKey]["Name"] = Name.toStdString();
    root[mKey]["Race"] = Race.toStdString();
    root[mKey]["Class"] = Voc.toStdString();
    root[mKey]["Level"] = Level.toStdString();
    /*
    QString STR, INT, WIS, DEX, CON, CHA, HPMax, MPMax;
    */
    root[mKey]["STR"] = STR.toStdString();
    root[mKey]["INT"] = INT.toStdString();
    root[mKey]["WIS"] = WIS.toStdString();
    root[mKey]["DEX"] = DEX.toStdString();
    root[mKey]["CON"] = CON.toStdString();
    root[mKey]["CHA"] = CHA.toStdString();
    root[mKey]["HPMax"] = HPMax.toStdString();
    root[mKey]["MPMax"] = MPMax.toStdString();
    /*
    QString XP;
    */
    root[mKey]["XP"] = XP.toStdString();

    /*
    QList<c_Spell*> Spells;
    */
    root[mKey]["Spells"] = Entity::spellListToArray(Spells);

    /*
    c_Item*         Weapon;
    c_Item*         Sheild;
    QList<c_Item*>  Armor;
    */
    root[mKey]["Weapon"] = Weapon->save();
    root[mKey]["Sheild"] = Sheild->save();
    root[mKey]["Armor"] = Entity::itemListToArray(Armor);

    /*
    QList<c_Item*> Inventory;
    QList<int> Quantity;
    */
    root[mKey]["Inventory"] = Entity::invListToArray(Inventory, Quantity);

    /*
    int Gold;
    */
    root[mKey]["Gold"] = Gold;

    return root;
}

void Entity::load(Json::Value entityRoot)
{
    // unpack entity values
    entityRoot = entityRoot.get("Entity", Json::objectValue);

    /*
    QString Name, Race, Voc, Level;
    */
    Name = QString::fromStdString(entityRoot.get("Name", "").asString());
    Race = QString::fromStdString(entityRoot.get("Race", "").asString());
    Voc = QString::fromStdString(entityRoot.get("Class", "").asString());
    Level = QString::fromStdString(entityRoot.get("Level", "").asString());
    /*
    QString STR, INT, WIS, DEX, CON, CHA, HPMax, MPMax;
    */
    STR = QString::fromStdString(entityRoot.get("STR", "").asString());
    INT = QString::fromStdString(entityRoot.get("INT", "").asString());
    WIS = QString::fromStdString(entityRoot.get("WIS", "").asString());
    DEX = QString::fromStdString(entityRoot.get("DEX", "").asString());
    CON = QString::fromStdString(entityRoot.get("CON", "").asString());
    CHA = QString::fromStdString(entityRoot.get("CHA", "").asString());
    HPMax = QString::fromStdString(entityRoot.get("HPMax", "").asString());
    MPMax = QString::fromStdString(entityRoot.get("MPMax", "").asString());

    /*
    QString XP;
    */
    XP = QString::fromStdString(entityRoot.get("XP", "").asString());

    /*
    QList<c_Spell*> Spells;
    */
    Spells = Entity::arrayToSpellList(entityRoot.get("Spells", Json::arrayValue));

    /*
    c_Item*         Weapon;
    c_Item*         Sheild;
    QList<c_Item*>  Armor;
    */
    Weapon->load(entityRoot.get("Weapon",Json::arrayValue));
    Sheild->load(entityRoot.get("Sheild",Json::arrayValue));
    Armor = Entity::arrayToItemList(entityRoot.get("Armor",Json::arrayValue));

    /*
    QList<c_Item*> Inventory;
    QList<int> Quantity;
    */
    Entity::arrayToInvList(entityRoot.get("Inventory",Json::arrayValue), Inventory, Quantity);

    /*
    int Gold;
    */
    Gold = entityRoot.get("Gold", 0).asInt();
}

Json::Value Entity::spellListToArray(QList<c_Spell *> &list)
{
    Json::Value array;
    array.clear();
    for (int i=0; i < list.size(); i++){
        array.append(list.at(i)->save());
    }
    return array;
}

Json::Value Entity::itemListToArray(QList<c_Item *> &list)
{
    Json::Value array;
    array.clear();
    for (int i=0; i < list.size(); i++)
    {
        array.append(list.at(i)->save());
    }
    return array;
}

Json::Value Entity::invListToArray(QList<c_Item *> &iList, QList<int> &nList)
{

    Json::Value array, pair;
    array.clear();
    for (int i=0; i < iList.size(); i++)
    {
        pair.clear();

        pair.append(iList.at(i)->save());
        pair.append(nList.at(i));

        array.append(pair);
    }
    return array;
}

QList<c_Spell *> Entity::arrayToSpellList(Json::Value array)
{
    QList<c_Spell *> list;
    for (Json::ArrayIndex i=0; i < array.size(); i++)
    {
        list.append(new c_Spell);
        list.at(list.size() - 1)->load(array.get(i, Json::objectValue));
    }
    return list;
}

QList<c_Item *> Entity::arrayToItemList(Json::Value array)
{
    QList<c_Item *> list;
    for (Json::ArrayIndex i=0; i < array.size(); i++)
    {
        list.append(new c_Item);
        list.at(list.size() - 1)->load(array.get(i, Json::objectValue));
    }
    return list;
}

void Entity::arrayToInvList(Json::Value array, QList<c_Item *> &iList, QList<int> &nList)
{
    Json::Value pair;
    pair.clear();

    iList.clear();
    nList.clear();

    for (Json::ArrayIndex i=0; i < array.size(); i++)
    {
        pair = array.get(i, Json::arrayValue);

        iList.append(new c_Item);
        iList.at(iList.size() - 1)->load(pair.get((Json::ArrayIndex)0,Json::objectValue));

        nList.append(pair.get((Json::ArrayIndex)1, 0).asInt());
    }
}
