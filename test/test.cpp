#include <cstddef>
#include <DecVariant/dec_variant.h>
#include <iostream>
#include <vector>

int main(){
    DecVar::CycleVector<int> _cv;
    for(size_t i = 0; i < 100; i++){
        _cv.push_back(i);
    }

    int ret;
    while (_cv.next()) {
        ret = _cv.get();
        std::cout << ret << std::endl;
    }

    return 0;
}