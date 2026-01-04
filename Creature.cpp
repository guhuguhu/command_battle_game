#include <iostream>
#include <cassert>
#include <memory>
#include "Creature.h"
#include "Random.h"

Creature::Creature(std::string n, int h, int p, int s, int d) :
name(n), hp(h), max_hp(h), power(p), speed(s), defence(d) {};

Creature::Creature(std::string n, int h, int p, int s, int d, std::vector<std::shared_ptr<const Technique>> &t) :
name(n), hp(h), max_hp(h), power(p), speed(s), defence(d), learned_techs(t) {};

bool Creature::winSpeed(const Creature &cre) const {
        return speed > cre.speed;
}

std::shared_ptr<const Technique> Creature::randomTech() const {
    int n = learned_techs.size();
    assert(n > 0);
    int n_tech = from1toNRandom(n);
    return getTech(n_tech - 1);
}

bool Creature::isDowned() const {
    return hp <= 0;
}

void Creature::displayHp() const {
    std::cout << name << " hp " << hp << std::endl; 
}

//技を覚える
void Creature::learn_tech(std::shared_ptr<const Technique> tech) {
    learned_techs.push_back(tech);
} 

//技を忘れる
void Creature::lost_tech(std::shared_ptr<const Technique> tech) {
    for (auto t = learned_techs.begin(); t < learned_techs.end(); t++) {
        if ((*t)->name == tech->name) {
            learned_techs.erase(t);
            break;
        }
    }
} 

std::shared_ptr<const Technique> Creature::getTech(const int i) const {
    return learned_techs[i];
}

void Creature::damaged(int d) {
    if (hp >= d) {
        hp -= d;
    } else {
        hp = 0;
    }
}

//指定された技で攻撃
void Creature::techAttack(std::shared_ptr<const Technique> tech, std::shared_ptr<Creature> cre) {
    std::cout << std::endl << name << " " << tech->name << " " << cre->name << std::endl;
    int offense = tech->culOffense(power);
    if (offense == -1) {
        std::cout << "don't hit" << std::endl;
    } else {
        int d = offense / cre->defence + 1;
        cre->damaged(d);
        std::cout << d << " damage" << std::endl;
    }
}

//覚えている技の数を取得
int Creature::getNTech() const{
    return learned_techs.size();
}

//hpを全回復する
void Creature::recoveryAllHp() {
    hp = max_hp;
}

Monster::Monster(std::string n, int h, int p, int s, int d, std::vector<std::shared_ptr<const Technique>> tech) : Creature(n, h, p, s, d, tech) {};

//ランダムの技で攻撃
void Monster::randomAttack(std::shared_ptr<Creature> cre) {
    const auto tech = randomTech();
    techAttack(tech, cre);
}

Player::Player(std::string n, int h, int p, int s, int d, int mp) : 
mp(mp), max_mp(mp), Creature(n, h, p, s, d) {};

void Player::displayMp() const {
    std::cout << name << " mp " << mp << std::endl; 
}

//覚えている技を表示する。onlyCanがtrueのときはmpが足りていて使える技のみ表示する
void Player::showTechs(bool onlyCan = false) const {
    int n = getNTech();
    assert(n > 0);

    std::cout << std::endl;
    for (int i = 0; i < n; i++) {
        auto tech = getTech(i);
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
void Player::techAttack(std::shared_ptr<const Technique> tech, std::shared_ptr<Creature> cre) {
    mp -= tech->getMp();
    Creature::techAttack(tech, cre);
}
