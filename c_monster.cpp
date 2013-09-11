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

unsigned long long int c_Monster::winXP()
{
    // monster xp based on parabolic curve
    // see pq7_level_advancement_curvatures.ggb (geogebra4 file)
    // for more info

    if (awardXP <= 0) {
        // monster xp awards are lowish in value...
        // float should handle it
        float lv = c_Monster::Level().toFloat();
        float base_xp = 10;
        float factor = 17;

        // special bonus
        if (isSpecial)
            base_xp +=  5.0; // careful

        awardXP = (unsigned long long int)
                (base_xp + (pow(lv,2.0) / pow(factor,2.0)) );
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
    //if (rand() % 10 == 0) c_Monster::makeSpecial();
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

void c_Monster::makeSpecial(int level)
{
    // non-reentrent
    if (! isSpecial) {
        QStringList list, cdata;

        // select the closest special bonus (should be multiples, randomize)
        list = c_Monster::pickSpcByLevel(level);
        cdata = list.at(rand() % list.size()).split("|");

        // a "special" monster is a new race of sorts
        monster_race = gConfig->capWords(gConfig->fnInterpStr(cdata.at(0), monster_race));
        monster_level += cdata.at(1).toInt();
        isSpecial = true;
    }
}

QStringList c_Monster::pickSpcByLevel(int level)
{
    int curSpcLevel(0), curLv(0), closestDiff(9999), closestFind(0);
    QStringList finds;
    finds.clear();

    // traverse all specials
    for(int i(0); i < gConfig->MonSpecial.size(); i++) {

        curSpcLevel = gConfig->MonSpecial.at(i).split("|").at(1).toInt();
        curLv = monster_level + curSpcLevel;

        //exact match
        if (level - curLv == 0) {
            finds.append(gConfig->MonSpecial.at(i)); // add to finds
        }
        else
        {
            // if closer record and go on
            if (abs(level - curLv) < closestDiff) {
                closestDiff = abs(level - curLv);
                closestFind = curSpcLevel;
            }
        }
    }

    // no exacts found - do closest matchs
    if (finds.empty()) {
        for(int i(0); i < gConfig->MonSpecial.size(); i++) {
            curSpcLevel = gConfig->MonSpecial.at(i).split("|").at(1).toInt();
            if (curSpcLevel == closestFind) finds.append(gConfig->MonSpecial.at(i));
        }
    }

    return finds;
}

bool c_Monster::makeByLevel(int level)
{
    // be careful modifing this tryCount, used iteratively elsewhere
    int tryCount = 5;
    int chanceSpc(0);
    QStringList cdata;

    // attempt to align highest available monster for level
    do {
        c_Monster::clear();

        // grab a monster
        cdata = gConfig->Monsters.at(rand() % gConfig->Monsters.size()).split("|");
        monster_race = cdata.at(0);
        monster_level = cdata.at(1).toInt();
        drops.append(cdata.at(2));

        // random chance of special monster - incr with level
        chanceSpc = 10 - (level / 10);
        if (chanceSpc < 2) chanceSpc = 1; // 50% at lv 90+
        if (rand() % chanceSpc == 0) c_Monster::makeSpecial(level);

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
    if (level < 20) return false;

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
        //lvMinion = gConfig->fnRandTop(lvLeader, 50);
        lvMinion = rand() % (lvLeader - 1) + 1;

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
            discription = minion.Discription()+ tr(", traveling with ") +
                    gConfig->Indefinite(leader.Discription());
        else
            discription = tr("group of ") + QString().number(numOfMinions) + tr(" ") +
                    gConfig->sufPlural(minion.Discription()) + tr(", lead by ") +
                    gConfig->Indefinite(leader.Discription());

        monster_race = tr("Monster Group");
        monster_level = leader.Level().toInt() + minion.Level().toInt() * numOfMinions;
        drops.append(leader.Drops());
        for (int i(0); i < gConfig->fnPercent(numOfMinions, 25); i++)
                drops.append(minion.Drops());
        dropsFormatted=true;
        isGroup = true;
        isSpecial = leader.isSpecial || minion.isSpecial;
    }

    return found;
}

//void c_Monster::save(std::ofstream fh)
//{
//    /*
//    QString monster_race;
//    int monster_level;
//    */
//    fh << monster_race << std::endl;
//    fh << monster_level << std::endl;
//    /*
//    QStringList mods;
//    QList<int> mod_values;
//    */
//    fh << mods.size() << std::endl;
//    for (int i=0; i < mods.size(); i++) {
//        fh << mods.at(i) << std::endl;
//    }
//    fh << mod_values.size() << std::endl;
//    for (int i=0; i < mods_values.size(); i++) {
//        fh << mods_values.at(i) << std::endl;
//    }
//    /*
//    QStringList drops;
//    bool dropsFormatted;
//    */
//    fh << drops.size() << std::endl;
//    for (int i=0; i < drops.size(); i++) {
//        fh << drops.at(i) << std::endl;
//    }
//    fh << dropsFormatted ? tr("true") : tr("false") << std::endl;
//    /*
//    QString discription;
//    QString level;
//    unsigned long long int awardXP;
//    */
//    fh << discription << std::endl;
//    fh << level << std::endl;
//    fh << awardXP << std::endl;
//}

//void c_Monster::load(std::ifstream fh)
//{
//    /*
//    QString monster_race;
//    int monster_level;
//    */
//    fh >>  monster_race;
//    fh >> monster_level;
//    /*
//    QStringList mods;
//    QList<int> mod_values;
//    */
//    fh >> mods.size();
//    for (int i=0; i < mods.size(); i++) {
//        fh >> mods.at(i);
//    }
//    fh >> mod_values.size();
//    for (int i=0; i < mods_values.size(); i++) {
//        fh >> mods_values.at(i);
//    }
//    /*
//    QStringList drops;
//    bool dropsFormatted;
//    */
//    fh >> drops.size();
//    for (int i=0; i < drops.size(); i++) {
//        fh >> drops.at(i);
//    }
//    fh >> dropsFormatted ? tr("true") : tr("false");
//    /*
//    QString discription;
//    QString level;
//    unsigned long long int awardXP;
//    */
//    fh >> discription;
//    fh >> level;
//    fh >> awardXP;
//}
