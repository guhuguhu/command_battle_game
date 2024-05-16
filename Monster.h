#include <iostream>
#include <vector>
#include "Technique.h"

class Monster {
public:
    const std::string name;
private:
    int hp; //hp
    int max_hp; //最大hp
    const int power; //力
    const int speed; //速さ
    const int defence; //硬さ
    std::vector<const Technique*> learned_techs; //覚えている技

public:
    Monster(std::string n, int h, int p, int s, int d);

    Monster(std::string n, int h, int p, int s, int d, std::vector<const Technique*> &t);

    bool winSpeed(const Monster &m) const;

    bool isDowned() const;

    void displayHp() const;
    
    void learn_tech(const Technique *tech); 

    void lost_tech(const Technique *tech);

    const Technique *getTech(const int i) const;

    int getNTech() const;

    void techAttack(const Technique *tech, Monster *mons);

    void recoveryAllHp();

    void damaged(int d);
    const Technique *randomTech() const;

};

class Player: public Monster {
private:
    int mp; //mp
    int max_mp; //最大mp

public:
    Player(std::string n, int h, int p, int s, int d, int mp);
    void showTechs(bool onlyCan) const;
    void displayMp() const;
    void recoveryAllMp();
    int getMp() const; 
    void techAttack(const Technique *tech, Monster *mons);
    bool canTech(Technique* tech) const; 
};