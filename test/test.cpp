#include "dec_variant/limited_numeric.h"
#include <iostream>
#include <dec_variant.h>

int main(){
    DecVar::LimitedNumeric<double> _ln(0,-10,50);
    std::cout << _ln.to_str() << std::endl;

    _ln++;
    std::cout << _ln.to_str() << std::endl;
    _ln--;
    _ln--;
    std::cout << _ln.to_str() << std::endl;

    _ln += 999;
    std::cout << _ln.to_str() << std::endl;

    _ln -= 999;
    std::cout << _ln.to_str() << std::endl;

    _ln = 999;
    std::cout << _ln.to_str() << std::endl;

    _ln = _ln - 1000000;
    std::cout << _ln.to_str() << std::endl;

    return 0;
}