#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <map>
#include <memory>
#include "Random.h"
#include "Battle.h"

constexpr int M_STATUS_COUNT = 6; //モンスターのステータスの個数

//Technique.csvから技をロード
void load_Technique(std::vector<std::shared_ptr<const Technique>> &techs) {
    std::ifstream ifs("./Technique.csv");
    std::string line;
    while (getline(ifs, line)) {
        std::istringstream line_(line);
        std::string status[M_STATUS_COUNT];
        int i = 0;        
        while (getline(line_, status[i++], ',')) {}
        auto tech = std::make_shared<Technique>(status[0], stoi(status[1]), stoi(status[2]), stoi(status[3]));
        techs.push_back(tech);
    }
}

//プレイヤーの初期化。Player.csvからプレイヤーのステイタスをロード。名前をプレイヤーが入力
std::shared_ptr<Player> init_Player() {
    std::ifstream ifs("./Player.csv");
    std::string line;
    getline(ifs, line);
    std::istringstream line_(line);
    std::string status[M_STATUS_COUNT];
    int i = 0;        
    while (getline(line_, status[i++], ',')) {}
    std::cout << "Please input name." << std::endl;
    std::string Player_name;
    std::cin >> Player_name;
    auto p = std::make_shared<Player>(Player_name, stoi(status[0]), stoi(status[1]), stoi(status[2]), stoi(status[3]), stoi(status[4]));
    return p;
}

//Monster.csvからモンスターのステイタスをロード
void load_Monster(std::list<std::shared_ptr<Monster>> &monsters, std::vector<std::shared_ptr<const Technique>> &techs) {
    std::ifstream ifs("./Monster.csv");
    std::string line;
    while (getline(ifs, line)) {
        std::istringstream line_(line);
        std::string status[M_STATUS_COUNT];
        int i = 0;        
        while (getline(line_, status[i++], ',')) {}
        auto mon = std::make_shared<Monster>(status[0], stoi(status[1]), stoi(status[2]), stoi(status[3]), stoi(status[4]), techs);
        monsters.push_back(mon);
    }
}

int main() {
    std::vector<std::shared_ptr<const Technique>> techniques;
    load_Technique(techniques);

    std::list<std::shared_ptr<Monster>> monsters;
    load_Monster(monsters, techniques);

    auto player = init_Player();

    std::cout << std::endl << std::endl;

    for (auto tech : techniques) {
        player->learn_tech(tech);
    }

    bool clear = true; // trueであれば全勝。クリア
    int i = 1;
    //モンスターと順にバトル
    for (auto monster : monsters) {
        std::cout << std::endl << std::endl << "round" << i << std::endl;
        std::cout << monster->name << " appear" << std::endl;
        Battle battle(player, monster);
        clear &= battle.start_battle();
        //負けたら終了
        if (!clear) break;
        // hpとmpを全回復 
        player->recoveryAllHp();
        player->recoveryAllMp();
        i++;
    } 

    //全勝したらクリア
    if (clear) 
        std::cout << std::endl << std::endl << "clear." << std::endl;
    else 
        std::cout << std::endl << std::endl << "game over." << std::endl;

    return 0;
}