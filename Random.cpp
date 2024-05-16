#include <random>
#include "Random.h"

//1からnまでの整数乱数を生成
int from1toNRandom(int n) {
    
    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());
    std::uniform_int_distribution<int> dist(1, n);
    
   return dist(engine);
}
