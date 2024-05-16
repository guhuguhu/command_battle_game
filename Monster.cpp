#include <iostream>
#include <cassert>
#include "Monster.h"
#include "Random.h"

Monster::Monster(std::string n, int h, int p, int s, int d) :
name(n), hp(h), max_hp(h), power(p), speed(s), defence(d) {};

Monster::Monster(std::string n, int h, int p, int s, int d, std::vector<const Technique*> &t) :
name(n), hp(h), max_hp(h), power(p), speed(s), defence(d), learned_techs(t) {};

bool Monster::winSpeed(const Monster &m) const {
        return speed > m.speed;
}

const Technique *Monster::randomTech() const {
    int n = learned_techs.size();
    assert(n > 0);
    int n_tech = from1toNRandom(n);
    return getTech(n_tech - 1);
}

bool Monster::isDowned() const {
    return hp <= 0;
}

void Monster::displayHp() const {
    std::cout << name << " hp " << hp << std::endl; 
}

//技を覚える
void Monster::learn_tech(const Technique *tech) {
    learned_techs.push_back(tech);
    std::cout << name << " learn " << tech->name << std::endl;
} 

//技を忘れる
void Monster::lost_tech(const Technique *tech) {
    for (auto t = learned_techs.begin(); t < learned_techs.end(); t++) {
        if ((*t)->name == tech->name) {
            learned_techs.erase(t);
            std::cout << name << " lost " << (*t)->name << std::endl;
            break;
        }
    }
} 

const Technique *Monster::getTech(const int i) const {
    return learned_techs[i];
}

void Monster::damaged(int d) {
    hp -= d;
}

//ある技で攻撃
void Monster::techAttack(const Technique *tech, Monster *m) {
    std::cout << std::endl << name << " " << tech->name << " " << m->name << std::endl;
    int offense = tech->culOffense(power);
    if (offense == -1) {
        std::cout << "don't hit" << std::endl;
    } else {
        int d = offense / m->defence + 1;
        m->damaged(d);
        std::cout << d << " damage" << std::endl;
    }
}

//覚えている技の数を取得
int Monster::getNTech() const{
    return learned_techs.size();
}

//hpを全回復する
void Monster::recoveryAllHp() {
    hp = max_hp;
}

Player::Player(std::string n, int h, int p, int s, int d, int mp) : 
mp(mp), max_mp(mp), Monster(n, h, p, s, d) {};

void Player::displayMp() const {
    std::cout << name << " mp " << mp << std::endl; 
}

//覚えている技を表示する。onlyCanがtrueのときはmpが足りていて使える技のみ表示する
void Player::showTechs(bool onlyCan = false) const {
    int n = getNTech();
    assert(n > 0);

    std::cout << std::endl;
    for (int i = 0; i < n; i++) {
        const Technique *tech = getTech(i);
        if (!onlyCan || tech->getMp() < mp) {
            std::cout << i + 1 << ". ";
            getTech(i)->show();
        }
    }
}

void Player::recoveryAllMp() {
    mp = max_mp;
}

int Player::getMp() const {
    return mp;
}

//ある技で攻撃
void Player::techAttack(const Technique *tech, Monster *m) {
    mp -= tech->getMp();
    Monster::techAttack(tech, m);
}
