#include "DecVariant/dec_variant/random_code.h"
#include "DecVariant/dec_variant/random_num.h"
#include <DecVariant/dec_variant.h>
#include <cstddef>
#include <iostream>
#include <map>
#include <string>


using namespace std;

int main(){
    std::cout << "START" << std::endl;

    std::map<int, int> counter_a;
    for(size_t i = 0; i < 1000000; i++){
        int ret = DecVar::RandomNumUniform(1, 6).get();
        if(!counter_a.contains(ret)){
            counter_a.try_emplace(ret, 0);
        }
        counter_a[ret]++;
    }
    for(auto& it : counter_a){
        std::cout << it.first << " : " << it.second << std::endl;
    }

    std::map<int, int> counter_b;
    for(size_t i = 0; i < 1000000; i++){
        int ret = DecVar::RandomNumNormal(0,1).get();
        if(!counter_b.contains(ret)){
            counter_b.try_emplace(ret, 0);
        }
        counter_b[ret]++;
    }
    for(auto& it : counter_b){
        std::cout << it.first << " : " << it.second << std::endl;
    }

    std::cout << "END" << std::endl;
    return 0;
}