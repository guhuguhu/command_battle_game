#include "Creature.h"
#include <map>
#include <tuple>
#include <memory>

class Battle {
private:
    int turn;
    std::shared_ptr<Player> player;
    std::shared_ptr<Monster> monster;
    std::string winner; 

public:
    Battle(std::shared_ptr<Player> p, std::shared_ptr<Monster> m);
    bool start_battle();
    void start_turn();
    std::shared_ptr<const Technique> input_tech();
    void winnerJudge();
    void displayAllCreaturesHpMp() const;
};