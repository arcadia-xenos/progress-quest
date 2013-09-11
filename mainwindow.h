#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*
#include "entity.h"
#include "c_spell.h"
#include "c_item.h"
#include "c_monster.h"
#include "pq7_config.h"
*/
#include "c_world.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;

    //int Act;
    //QString Action;
    //c_Monster* curMonster;
    //t_pq_state State;

    void initFrames();
    //void initPlayer();

    void addAct();
    void addQuest(QString name);
    QString randQuest();

    void setMonster();
    void addMonDrop();
    QString sellInvItem();
    void rmInvItem();

    void buyNewEq();
    bool canBuyNewEq(t_pq_equip eqtype);
    c_Item *getPurchaseItem(t_pq_equip eqtype);
    c_Item* upgradeEq(t_pq_equip eqtype , int grade);

    void winStats();
    void winSpells();

    void updSpellTbl();
    void updInvTbl();
    void updEquipTbl();
    void updStatsTbl();

    void tranState();

    // timer drive
    QTimer *pb_action_timer;

public slots:
    void incr_pb_action_value();
    void incr_pb_experience_value();
    void incr_pb_encumbrance_value();
    void incr_pb_plot_value();
    void incr_pb_quest_value();

    void gameSave();

    void setAction();
};

#endif // MAINWINDOW_H
