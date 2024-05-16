#include <iostream>

class Technique {
public:
    const std::string name;
private:
    const int ratio; //ダメージ倍率
    const int hit_rate; //命中率
    const int mp; //消費mp
    
public:
    Technique(const std::string n, const int r, const int hr, const int mp = 0);
    Technique(const std::string n, const std::string r, const std::string hr, const std::string mp);
    Technique(const Technique &tech);

    int culOffense(const int power) const;
    int getMp() const;
    void show() const;
};