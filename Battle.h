#include "Creature.h"
#include <map>
#include <tuple>

class Battle {
private:
    int turn;
    Player *player;
    Monster *monster;
    std::string winner; 

public:
    Battle(Player *p, Monster *m);
    bool start_battle();
    void start_turn();
    Monster *input_target();
    const Technique *input_tech();
    Monster *randomTarget();
    void winnerJudge();
    void displayAllCreaturesHpMp() const;
};