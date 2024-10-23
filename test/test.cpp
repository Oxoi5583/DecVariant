#include "dec_variant/cycle_numeric.h"
#include <cstddef>
#include <dec_variant.h>
#include <iostream>
#include <vector>

int main(){
    DecVar::CycleNumeric<int> _cn1(0, -5, 100);
    for(size_t i = 0; i < 1000 ; i ++){
        _cn1++;
        std::cout << _cn1.to_str() << std::endl;
    }

    DecVar::CycleNumeric<double> _cn2(0, -5, 100);
    for(size_t i = 0; i < 1000 ; i ++){
        _cn2 += 5.5;
        std::cout << _cn2.to_str() << std::endl;
    }

    return 0;
}