#include "Battle.h"
#include <list>
#include <cassert>

Battle::Battle(Player *p, Monster *m) : turn(0), player(p), monster(m){}

const Technique *Battle::input_tech() {
    player->showTechs(true);
    int n_techs = player->getNTech();
    assert(n_techs > 0);

    std::cout << std::endl;
    std::cout << "choose number of Technique." << std::endl;
    int tech_i;
    std::cin >> tech_i;
    return player->getTech(tech_i - 1);
}

void Battle::winnerJudge() {
    if (monster->isDowned()) {
        winner = player->name;
    } else if (player->isDowned()) {
        winner = monster->name;
    }
}

void Battle::displayAllMonsHpMp () const {
    player->displayHp();
    player->displayMp();
    monster->displayHp();
}
// m1, m2それぞれの攻撃を1回ずつ行う。スピードが高い方が先制攻撃できる。勝者の名前を返す。決着がつかない場合はnobodyを返す
void Battle::start_turn () {
    std::cout << std::endl << "turn" << turn+1 << std::endl;
    displayAllMonsHpMp();

    const Technique *tech = input_tech();

    Monster *mons[2];
    if (player->winSpeed(*monster)) {
        mons[0] = player; 
        mons[1] = monster;
    } else {
        mons[0] = monster; 
        mons[1] = player;
    }
    for (int i=0; i<2; i++) {
        mons[i]->techAttack(tech, mons[(i+1)%2]);
        winnerJudge();
    }
    turn++;
}

//プレイヤーが勝った場合はtrue、負けた場合はfalseを返す
bool Battle::start_battle() {
    int i = 1;
    while(true) {
        start_turn();
        if (winner != "") {
            std::cout << winner << " win" << std::endl;
            if (winner == player->name)
                return true;
            else 
                return false;
        } 
    }
}