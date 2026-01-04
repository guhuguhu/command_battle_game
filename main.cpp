#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <map>
#include <memory>
#include "Random.h"
#include "Battle.h"

//Technique.csvから技をロード
void load_Technique(std::map<std::string, std::shared_ptr<const Technique>> &techs) {
    std::ifstream ifs("./Technique.csv");
    std::string line;
    while (getline(ifs, line)) {
        std::istringstream line_(line);
        std::vector<std::string> status;
        std::string s;
        while (getline(line_, s, ',')) {
            status.push_back(s);
        }
        auto tech = std::make_shared<Technique>(status[0], stoi(status[1]), stoi(status[2]), stoi(status[3]));
        techs[status[0]] = tech;
    }
}

//プレイヤーの初期化。Player.csvからプレイヤーのステイタスをロード。名前をプレイヤーが入力
std::shared_ptr<Player> init_Player(std::map<std::string, std::shared_ptr<const Technique>> techs) {
    std::ifstream ifs("./Player.csv");
    std::string line;
    getline(ifs, line);
    std::istringstream line_(line);
    std::vector<std::string> status;
    std::string s;
    while (getline(line_, s, ',')) {
        status.push_back(s);
    }
    std::cout << "Please input name." << std::endl;
    std::string Player_name;
    std::cin >> Player_name;
    auto player = std::make_shared<Player>(Player_name, stoi(status[0]), stoi(status[1]), stoi(status[2]), stoi(status[3]), stoi(status[4]));
    for (int j = 5; j < status.size(); j++) {
        player->learn_tech(techs[status[j]]);
    }
    return player;
}

//Monster.csvからモンスターのステイタスをロード
void load_Monster(std::list<std::shared_ptr<Monster>> &monsters, std::map<std::string, std::shared_ptr<const Technique>> &techs) {
    std::ifstream ifs("./Monster.csv");
    std::string line;
    while (getline(ifs, line)) {
        std::istringstream line_(line);
        std::vector<std::string> status;
        std::string s;
        while (getline(line_, s, ',')) {
            status.push_back(s);
        }
        std::vector<std::shared_ptr<const Technique>> mons_techs;
        for (int j = 5; j < status.size(); j++) {
            mons_techs.push_back(techs[status[j]]);
        }
        auto mons = std::make_shared<Monster>(status[0], stoi(status[1]), stoi(status[2]), stoi(status[3]), stoi(status[4]), mons_techs);
        monsters.push_back(mons);
    }
}

int main() {
    std::map<std::string, std::shared_ptr<const Technique>> techniques;
    load_Technique(techniques);

    std::list<std::shared_ptr<Monster>> monsters;
    load_Monster(monsters, techniques);

    auto player = init_Player(techniques);

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