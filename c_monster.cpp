#include "c_monster.h"

c_Monster::c_Monster(QObject *parent) :
    QObject(parent)
{
    c_Monster::clear();
}

void c_Monster::clear()
{
    monster_race.clear();
    monster_level=0;

    mods.clear();
    mod_values.clear();

    drops.clear();
    dropsFormatted = false;

    discription = "";
    level = "";

    isMounted = false;
    isGroup = false;

    isSpecial = false;

    awardXP = 0;
}

QString c_Monster::Discription()
{
    /*
      monster description builds rely on the following rules in the c_Config data

        1) the labels are appropiately context free (no duplicates, no cross meanings, etc)
        2) '*' is used only once and is either at the beginning or end of the pattern
        3) '*' indicates where current build string should go

     */
    if (discription == tr("")) {
        QString build;
        QStringList tmp;

        build = monster_race; // basename

        // apply mod list
        for (int i(0); i < mods.size(); i++){
            build = gConfig->fnInterpStr(mods.at(i), build);
        }

        discription = build;
    }

    return discription;
}

QString c_Monster::Level()
{
    if (level == tr("")) {
        int build = monster_level;
        for(int i = 0; i < mod_values.size(); i++) {
            build += mod_values.at(i);
        }
        level = QString().number(build);
    }
    return level;
}

int c_Monster::winXP()
{
    if (awardXP <= 0) {
        int lv = c_Monster::Level().toInt();
        int base_xp = 10;

        // zero level monsters
        if (lv < 1) {
            lv = 1;
            base_xp = 5;
        }

        // special bonus
        if (isSpecial)
            base_xp = 15;

        awardXP = lv * base_xp;
    }

    return awardXP;
}

QStringList c_Monster::Drops()
{
    if (! dropsFormatted) {
        for(int i(0); i < drops.size(); i++) {
            // handle special drops
            if (drops.at(i) == tr("*"))
                drops[i] = gConfig->MonSpcDrop.at(rand() % gConfig->MonSpcDrop.size());


            //if (! isMounted && ! isGroup) // preformatted
            drops[i] = monster_race.toLower() + tr(" ") + drops.at(i);
        }
        dropsFormatted = true;
    }
    return drops;
}

void c_Monster::makeRandMonster()
{
    QStringList cdata;

    // grab a monster
    cdata = gConfig->Monsters.at(rand() % gConfig->Monsters.size()).split("|");
    monster_race = cdata.at(0);
    monster_level = cdata.at(1).toInt();
    drops.append(cdata.at(2));

    // total range of mods for level displacement -20..+20
    if (rand() % 3 == 0) c_Monster::addAge(); // -5..+5
    if (rand() % 3 == 0) c_Monster::addHealth(); // -5..+5
    if (rand() % 3 == 0) c_Monster::addCast(); // -5..+5
    if (rand() % 3 == 0) c_Monster::addSize(); // -5..+5

    // special - can increase levels drastically (up to +150?)
    if (rand() % 10 == 0) c_Monster::addSpecial();
}

void c_Monster::addAge()
{
    QStringList cdata;
    cdata = gConfig->MonAge.at(rand() % gConfig->MonAge.size()).split("|");
    mods << cdata.at(0);
    mod_values.append(cdata.at(1).toInt());
}

void c_Monster::addCast()
{
    QStringList cdata;
    cdata = gConfig->MonCast.at(rand() % gConfig->MonCast.size()).split("|");
    mods << cdata.at(0);
    mod_values.append(cdata.at(1).toInt());
}

void c_Monster::addHealth()
{
    QStringList cdata;
    cdata = gConfig->MonHealth.at(rand() % gConfig->MonHealth.size()).split("|");
    mods << cdata.at(0);
    mod_values.append(cdata.at(1).toInt());
}

void c_Monster::addSize()
{
    QStringList cdata;
    cdata = gConfig->MonSize.at(rand() % gConfig->MonSize.size()).split("|");
    mods << cdata.at(0);
    mod_values.append(cdata.at(1).toInt());
}

void c_Monster::addSpecial()
{
    QStringList cdata;
    cdata = gConfig->MonSpecial.at(rand() % gConfig->MonSpecial.size()).split("|");

    // a "special" monster is a new race of sorts (prepended and capped "mod", for now)
    mods.prepend(gConfig->capWords(cdata.at(0)));
    mod_values.prepend(cdata.at(1).toInt());
    isSpecial = true;
}

bool c_Monster::makeByLevel(int level)
{
    // be careful modifing this tryCount, used iteratively elsewhere
    int tryCount = 5;
    QStringList cdata;

    // attempt to align highest available monster for level
    do {
        c_Monster::clear();

        // grab a monster
        cdata = gConfig->Monsters.at(rand() % gConfig->Monsters.size()).split("|");
        monster_race = cdata.at(0);
        monster_level = cdata.at(1).toInt();
        drops.append(cdata.at(2));

        // specials heuristics - applies knowledge of mod data
        if (level - monster_level > 150) {
            do {
                mods.clear();
                mod_values.clear();
                c_Monster::addSpecial();
            } while (mod_values.at(0) < 100);
        }
        else if (level - monster_level > 100) {
            do {
                mods.clear();
                mod_values.clear();
                c_Monster::addSpecial();
            } while ( (mod_values.at(0) < 50) &&
                      (mod_values.at(0) > 100) );
        }
        else if (level - monster_level > 50) {
            do {
                mods.clear();
                mod_values.clear();
                c_Monster::addSpecial();
            } while ( (mod_values.at(0) < 20) &&
                      (mod_values.at(0) > 50) );
        }
        else
        {
            // low level random chance of low special
            if (rand() % 10 == 0) {
                do {
                    mods.clear();
                    mod_values.clear();
                    c_Monster::addSpecial();
                } while (mod_values.at(0) > 20);
            }
        }

        // total range of mods for level displacement -20..+20
        if (rand() % 3 == 0) c_Monster::addAge(); // -5..+5
        if (rand() % 3 == 0) c_Monster::addHealth(); // -5..+5
        if (rand() % 3 == 0) c_Monster::addCast(); // -5..+5
        if (rand() % 3 == 0) c_Monster::addSize(); // -5..+5
        tryCount--;
    } while ( (c_Monster::Level() != QString().number(level)) && (tryCount > 0) );

    if (c_Monster::Level() != QString().number(level))
        return false; //fail
    else return true; //success

}

bool c_Monster::makeLevelRange(int lowest_level, int highest_level)
{
    /*
        trys to find monster by level from highest to lowest
    */
    int i(highest_level);
    bool found;

    do {
        found = c_Monster::makeByLevel(i);
        i--;
    } while ( (! found) && (i >= lowest_level) );

    return found;
}

bool c_Monster::makeMounted(int level)
{
    // trys to create a pair of monsters operating as a unit

    // sanity - blow off lowest levels
    if (level < 3) return false;

    int tryCount = 7;
    int lvTryCount = 50;

    c_Monster rider;
    c_Monster mount;

    int lvRider(0), lvMount(0);

    bool found(false), lvFound(false);


    // try to find a unit of proper combined level

    // first find a level combination (cheaper than feeding it through makeByLevel)
    do {
        // rand upper (abs) 1/2 of level
        lvRider = gConfig->fnRandTop(level, 50);
        lvMount = gConfig->fnRandTop(lvRider, 50);
        if ( lvRider + lvMount == level )
            lvFound = true;
        lvTryCount--;
    } while ( (! lvFound) && (lvTryCount > 0) );

    // attempt to create by levels
    if (lvFound) {
        do {
            if ( (rider.makeByLevel(lvRider))  &&
                 (mount.makeByLevel(lvMount)) )
                found = true;
            tryCount--;
        } while ( (! found) && (tryCount > 0) );

        // construct mounted monster
        if (found){
            c_Monster::clear();
            discription = rider.Discription() + tr(" mounted on a ") + mount.Discription();
            monster_race = tr("Mounted Monster");
            monster_level = rider.Level().toInt() + mount.Level().toInt();
            drops.append(rider.Drops());
            drops.append(mount.Drops());
            dropsFormatted = true;
            isMounted = true;
            isSpecial = rider.isSpecial || mount.isSpecial;
        }
    }

    return found;
}

bool c_Monster::makeMountedRange(int lowest_level, int highest_level)
{
    // mounted monster from highest to lowest in range
    int i(highest_level);
    bool found;

    do {
        found = c_Monster::makeMounted(i);
        i--;
    } while ( (! found) && (i >= lowest_level) );

    return found;
}

bool c_Monster::makeGroup(int level)
{
    // for my sanity - takes away nasty low level cases
    if (level < 8) return false;

    // trys to create a gang of monsters with combined level
    c_Monster minion;
    c_Monster leader;

    int tryCount = 5;
    int lvLeader(0), lvMinion(0), numOfMinions(0);
    bool found(false);

    // calculate levels for leader and minions

    // the %200 limits level deprec at high levels
    lvLeader = gConfig->fnRandTop((level % 200), 50);

    if (lvLeader < 2)
        lvMinion = 1;
    else
        lvMinion = gConfig->fnRandTop(lvLeader, 50);

    numOfMinions = (level - lvLeader)/lvMinion;


    // form group - by levels
    do {
        if (leader.makeByLevel(lvLeader))
            if (minion.makeByLevel(lvMinion))
                found = true;
        tryCount--;
    } while ( (! found) && (tryCount > 0) );

    if (found) {
        c_Monster::clear();
        if (numOfMinions < 2)
            discription = minion.Discription()+ tr(" ") + tr(", travelling with ") +
                    gConfig->Indefinite(leader.Discription());
        else
            discription = tr("group of ") + QString().number(numOfMinions) + tr(" ") +
                    gConfig->sufPlural(minion.Discription()) + tr(", lead by ") +
                    gConfig->Indefinite(leader.Discription());

        monster_race = tr("Monster Group");
        monster_level = leader.Level().toInt() + minion.Level().toInt() * numOfMinions;
        drops.append(leader.Drops());
        for (int i(0); i < gConfig->fnPercent(numOfMinions, 10); i++)
                drops.append(minion.Drops());
        dropsFormatted=true;
        isGroup = true;
        isSpecial = leader.isSpecial || minion.isSpecial;
    }

    return found;
}
