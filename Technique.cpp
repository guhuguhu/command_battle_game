#include "Technique.h"
#include "Random.h"

Technique::Technique(std::string n, int r, int hr, int mp) : name(n), ratio(r), hit_rate(hr), mp(mp) {}
Technique::Technique(std::string n, std::string r, std::string hr, std::string mp) : name(n), ratio(stoi(r)), hit_rate(stoi(hr)), mp(stoi(mp)) {}
Technique::Technique(const Technique &tech) : Technique(tech.name, tech.ratio, tech.hit_rate){}

//力と技の倍率の積により攻撃力を算出
int Technique::culOffense(const int power) const {
    if (from1toNRandom(100) <= hit_rate)
        return power * ratio / 100;
    return -1;
}

int Technique::getMp() const {
    return mp;
}

void Technique::show() const{
    std::cout << name << ": " << "ratio " << ratio <<" hit rate "  << hit_rate << " mp " << mp <<" " << std::endl;
}