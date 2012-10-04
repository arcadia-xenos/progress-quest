#ifndef C_SPELL_H
#define C_SPELL_H

#include <QString>
#include "pq7_config.h"

class c_Spell
{
public:
    c_Spell();
    c_Spell(int index);

    // accessors
    QString Name();
    QString Level();

    void incrSpellLevel();

    void setNameIndex(int index);
    void setRandName();
    void setSpellLevel(int level);


private:
    int nameIndex, levelValue;

};

#endif // C_SPELL_H
