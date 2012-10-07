#ifndef PQ7_CONFIG_H
#define PQ7_CONFIG_H

#include <QStringList>
#include <QString>
#include <QObject>

typedef enum {
    pq_equip_weapon,
    pq_equip_shield,
    pq_equip_armor,
    pq_equip_any
} t_pq_equip;

class c_Config
{

public:
    c_Config();

    QStringList Traits;
    QStringList PrimeStats;
    QStringList Equips;
    QStringList Spells;
    QStringList OffenseAttrib;
    QStringList DefenseAttrib;
    QStringList Shields;
    QStringList Armors;
    QStringList Weapons;
    QStringList Specials;
    QStringList ItemAttrib;
    QStringList ItemOfs;
    QStringList BoringItems;
    QStringList Monsters;
    QStringList MonHealth;
    QStringList MonAge;
    QStringList MonSize;
    QStringList MonCast;
    QStringList MonSpecial;
    QStringList MonSpcDrop;
    QStringList OffenseBad;
    QStringList DefenseBad;
    QStringList Races;
    QStringList Klasses;
    QStringList Titles;
    QStringList ImpressiveTitles;

    QString toRoman(int value);
    QString capWords(QString string);
    QString Indefinite(QString string);
    //QString Definite(QString string);
    QString sufPlural(QString string);
    int fnPercent(int value, int percent);
    int fnPercentOf(int value, int of);
    unsigned long long int fnPercentOf(unsigned long long int value, unsigned long long int of);
    int fnRandTop(int value, int percent);
    QString fnInterpStr(QString pattern, QString interpolation);

private:

};

//make gConfig to be an extern global
extern c_Config* gConfig;


#endif // PQ7_CONFIG_H
