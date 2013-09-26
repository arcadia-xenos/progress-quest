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
#include <QMessageBox>

#include <jsoncpp/json/json.h>

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


private:

    // save / load helpers
    Json::Value listToArray(QStringList &list);
    QStringList arrayToList(Json::Value array);

signals:

public slots:
    void save();
    void save(QString filename);
    void load();
    void load(QString filename);
    void load(Json::Value root);
};

#endif // C_WORLD_H

extern c_World* game;
