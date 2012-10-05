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
}

int Entity::Encumbrance()
{
    int build(0);
    for (int i = 0; i < Inventory.size(); i++) {
        build += Inventory.at(i)->Weight * Quantity.at(i);
    }
    return build;
}

int Entity::maxXP()
{
    // xp for next level is calculated on specific
    // exponential fn curve centered around level 150

    float Lv = Level.toFloat();
    float a = 1.5e8; // 150 million (base value)
    float c = 1.095; // coeffecient
    float h = 150.0; // bend

    return (int)(a * pow(c, (Lv - h)) );
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

