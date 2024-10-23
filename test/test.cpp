#include "DecVariant/dec_variant/lock_and_key.h"
#include <cstddef>
#include <DecVariant/dec_variant.h>
#include <iostream>

int main(){
    auto _p = LOCK_KEY_GENERATOR->create_pair_of_lock_key();
    DecVar::Lock _l = _p.first;
    DecVar::Key _k = _p.second;

    _lock << _key;


    if (_l) {
        std::cout << "Lock was opened." << std::endl;
    }

    return 0;
}
