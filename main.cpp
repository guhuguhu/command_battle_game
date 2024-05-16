#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <map>
#include "Random.h"
#include "Battle.h"

constexpr int M_STATUS_COUNT = 6; //モンスターのステータスの個数

//Technique.csvから技をロード
void load_Technique(std::map<std::string, const Technique *> &techs) {
    std::ifstream ifs("./Technique.csv");
    std::string line;
    while (getline(ifs, line)) {
        std::istringstream line_(line);
        std::string status[M_STATUS_COUNT];
        int i = 0;        
        while (getline(line_, status[i++], ',')) {}
        const Technique *tech = new Technique(status[0], stoi(status[1]), stoi(status[2]), stoi(status[3]));
        techs[status[0]] = tech;
    }
}

//プレイヤーの初期化。Player.csvからプレイヤーのステイタスをロード。名前をプレイヤーが入力
Player *init_Player() {
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
    Player *p = new Player(Player_name, stoi(status[0]), stoi(status[1]), stoi(status[2]), stoi(status[3]), stoi(status[4]));
    return p;
}

//Monster.csvからモンスターのステイタスをロード
void load_Monster(std::map<std::string, const Monster *> &monsters, std::map<std::string, const Technique *> &techs) {
    std::ifstream ifs("./Monster.csv");
    std::string line;
    while (getline(ifs, line)) {
        std::istringstream line_(line);
        std::string status[M_STATUS_COUNT];
        int i = 0;        
        while (getline(line_, status[i++], ',')) {}
        const Technique *tech = techs[status[5]];
        std::vector<const Technique*> learned_tech;
        learned_tech.push_back(tech);
        const Monster *m = new Monster(status[0], stoi(status[1]), stoi(status[2]), stoi(status[3]), stoi(status[4]), learned_tech);
        monsters[status[0]] = m;
    }
}

int main() {
    constexpr int M_COUNT = 3; //バトルするモンスターの数
    constexpr int T_COUNT = 3; //プレイヤーが覚える技の数
    std::map<std::string, const Technique *> techniques;
    load_Technique(techniques);

    std::map<std::string, const Monster *> monsters;
    load_Monster(monsters, techniques);


    Player *player = init_Player();

    std::cout << std::endl << std::endl;

    std::string t_list[T_COUNT] = {"tackle","punch","kick"};
    for (int i=0;i<T_COUNT;i++) {
        player->learn_tech(techniques[t_list[i]]);
    }

    std::string m_list[M_COUNT] = {"m1","m2","m3"};

    bool clear = true; // trueであれば全勝。クリア
    //モンスターと順にバトル
    for (int i=0;i<M_COUNT;i++) {
        std::cout << std::endl << std::endl << "round" << i+1 << std::endl;
        Monster monster(*monsters[m_list[i]]);
        std::cout << monster.name << " appear" << std::endl;
        Battle battle(player, &monster);
        clear &= battle.start_battle();
        //負けたら終了
        if (!clear) break;
        // hpとmpを全回復 
        player->recoveryAllHp();
        player->recoveryAllMp();
    } 

    //全勝したらクリア
    if (clear) 
        std::cout << std::endl << std::endl << "clear." << std::endl;
    else 
        std::cout << std::endl << std::endl << "game over." << std::endl;

    return 0;
}