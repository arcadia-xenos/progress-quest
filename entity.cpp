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
    int build(0);
    for (int i = 0; i < Inventory.size(); i++) {
        build += Inventory.at(i)->Weight * Quantity.at(i);
    }
    return build;
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

unsigned long long int Entity::maxXP()
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

//void Entity::save(std::ofstream fh)
//{

//    /*
//    QString Name, Race, Voc, Level;
//    */
//    fh << Name << std::endl;
//    fh << Race << std::endl;
//    fh << Voc << std::endl;
//    fh << Level << std::endl;
//    /*
//    QString STR, INT, WIS, DEX, CON, CHA, HPMax, MPMax;
//    */
//    fh << STR << std::endl;
//    fh << INT << std::endl;
//    fh << WIS << std::endl;
//    fh << DEX << std::endl;
//    fh << CON << std::endl;
//    fh << CHA << std::endl;
//    fh << HPMax << std::endl;
//    fh << MPMax << std::endl;
//    /*
//    QString XP;
//    unsigned long long maxXP();
//    */
//    fh << XP << std::endl;
//    fh << maxXP << std::endl;
//    /*
//    QList<c_Spell*> Spells;
//    */
//    fh << Spells.size() << std::endl;
//    for (int i=0; i<Spells.size(); i++){
//        fh << Spells.at(i)->save(fh);
//    }
//    /*
//    c_Item*         Weapon;
//    c_Item*         Sheild;
//    QList<c_Item*>  Armor;
//    */
//    fh << Weapon->save(fh);
//    fh << Sheild->save(fh);
//    fh << Armor.size() << std::endl;
//    for (int i=0; i < Armor.size(); i++) {
//        fh << Armor.at(i)->save(fh);
//    }
//    /*
//    QList<c_Item*> Inventory;
//    QList<int> Quantity;
//    */
//    fh << Inventory.size() << std::endl;
//    for (int i=0; i < Inventory.size(); i++) {
//        fh << Inventory.at(i)->save(fh);
//        fh << Quantity.at(i) << std::endl;
//    }
//    /*
//    int Gold;
//    */
//    fh << Gold << std::endl;
//}

//void Entity::load(std::ifstream fh)
//{
//    // local helper values
//    int arrSize;

//    /*
//    QString Name, Race, Voc, Level;
//    */
//    fh >> Name;
//    fh >> Race;
//    fh >> Voc;
//    fh >> Level;
//    /*
//    QString STR, INT, WIS, DEX, CON, CHA, HPMax, MPMax;
//    */
//    fh >> STR;
//    fh >> INT;
//    fh >> WIS;
//    fh >> DEX;
//    fh >> CON;
//    fh >> CHA;
//    fh >> HPMax;
//    fh >> MPMax;
//    /*
//    QString XP;
//    unsigned long long maxXP();
//    */
//    fh >> XP;
//    fh >> maxXP;
//    /*
//    QList<c_Spell*> Spells;
//    */
//    fh >> arrSize;
//    for (int i=0; i < arrSize; i++){
//        Spells.at(i)->load(fh);
//    }
//    /*
//    c_Item*         Weapon;
//    c_Item*         Sheild;
//    QList<c_Item*>  Armor;
//    */
//    Weapon->load(fh);
//    Sheild->load(fh);
//    fh >> arrSize;
//    for (int i=0; i < arrSize; i++) {
//        Armor.at(i)->load(fh);
//    }
//    /*
//    QList<c_Item*> Inventory;
//    QList<int> Quantity;
//    */
//    fh >> arrSize;
//    for (int i=0; i < arrSize; i++) {
//        Inventory.at(i)->load(fh);
//        fh >> Quantity.at(i);
//    }
//    /*
//    int Gold;
//    */
//    fh >> Gold;
//}
