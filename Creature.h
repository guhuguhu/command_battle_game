#include <iostream>
#include <vector>
#include <memory>
#include "Technique.h"

class Creature {
public:
    const std::string name;
private:
    int max_hp; //最大hp
    const int power; //力
    const int speed; //速さ
    const int defence; //硬さ

protected:
    int hp; //hp
    std::vector<std::shared_ptr<const Technique>> learned_techs; //覚えている技

public:
    Creature(std::string n, int h, int p, int s, int d);

    Creature(std::string n, int h, int p, int s, int d, std::vector<std::shared_ptr<const Technique>> &t);

    bool winSpeed(const Creature &cre) const;

    bool isDowned() const;

    void displayHp() const;
    
    void learn_tech(std::shared_ptr<const Technique> tech); 

    void lost_tech(std::shared_ptr<const Technique> tech);

    void techAttack(std::shared_ptr<const Technique> tech, std::shared_ptr<Creature> cre);

    void recoveryAllHp();

    void damaged(int d);
    std::shared_ptr<const Technique> randomTech() const;

};

class Player: public Creature {
private:
    int mp; //mp
    int max_mp; //最大mp

public:
    Player(std::string n, int h, int p, int s, int d, int mp);
    std::vector<std::shared_ptr<const Technique>> getCanTechs() const;
    void displayHpMp() const;
    void recoveryAllMp();
    int getMp() const; 
    void techAttack(std::shared_ptr<const Technique> tech, std::shared_ptr<Creature> cre);
};

class Monster: public Creature {
public:    
    Monster(std::string n, int h, int p, int s, int d, std::vector<std::shared_ptr<const Technique>> tech);
    void randomAttack(std::shared_ptr<Creature> cre);
};