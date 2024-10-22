#include <iostream>
#include <dec_variant.h>

int main(){
    for(size_t i = 0; i < 100; i++){
        DecVar::UniqueId _uid;
        std::cout << _uid.to_str() << std::endl;
    }

    return 0;
}