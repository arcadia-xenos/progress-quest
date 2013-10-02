#ifndef C_WORLD_H
#define C_WORLD_H

#include "entity.h"
#include "c_spell.h"
#include "c_item.h"
#include "c_monster.h"
#include "pq7_config.h"
#include <iostream>
#include <fstream>

#include <QObject>
#include <QList>
#include <QMessageBox>

#include <jsoncpp/json/json.h>

typedef enum {
    pq_debug_none                       = 0,
    pq_debug_zero_action_timer          = 1 << 0,
    pq_debug_always_trigger_action      = 1 << 1,
    pq_debug_action_triggers_save       = 1 << 2,
    pq_debug_reserved_1                 = 1 << 3,
    pq_debug_active                     = 1 << 15
} t_pq_debug;

typedef enum {
    pq_state_reserved_1,
    pq_state_heading_to_killing_fields,
    pq_state_fight,
    pq_state_heading_to_town,
    pq_state_selling_off,
    pq_state_buying_new_equip
} t_pq_state;

class c_World : public QObject
{
    Q_OBJECT
public:
    explicit c_World(QObject *parent = 0);

    /*
     *      Player instance - gamewide
     */
    Entity* Player;

    /*
     *      Monster instance - gamewide
     */
    c_Monster* Monster;

    /*
     *      State values
     */
    int Act;
    QString Action;
    t_pq_state State;

    /*
     *      Progress Bar values
     */
    int pb_action;
    int pb_experience;
    int pb_encumbrance;
    int pb_plot;
    int pb_quest;

    /*
     *      Quest history
     */
    QStringList quests;

    /*
     *      Timer Interval
     */
    int actionTime;

    /*
     *      Flag for Post Load UI Processing
     */
    bool isLoaded;

    /*
     *    Public Methods
     */
    c_Item* makeEqByGrade(t_pq_equip eqtype , int grade);
    void initPlayer();

    bool isDebugFlagSet(t_pq_debug flag);
    bool isDebugFlagReset(t_pq_debug flag);
    void setDebugFlag(t_pq_debug flag);
    void resetDebugFlag(t_pq_debug flag);
    void toggleDebugFlag(t_pq_debug flag);
    void debugClear();
    void debugActive();

private:

    // save / load helpers
    Json::Value listToArray(QStringList &list);
    QStringList arrayToList(Json::Value array);

    /*
     *      Debug flags
     */
    quint32 debug;

signals:
    //void debugChanged(quint32 dbgValue);
    //void gameSaved();
    //void gameLoaded();

public slots:
    void save();
    void save(QString filename);
    void load();
    void load(QString filename);
    void load(Json::Value root);
};

#endif // C_WORLD_H

extern c_World* game;
