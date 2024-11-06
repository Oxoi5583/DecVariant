#include <DecVariant/dec_variant.h>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

using namespace std;



int main(){
    std::cout << "START" << std::endl;
    DecVar::WeightOption<string> _wo;
    _wo.set_range(0, 150);
    _wo.register_option(10, "A");
    _wo.register_option(25, "B");
    _wo.register_option(50, "C");
    _wo.register_option(80, "D");
    _wo.register_option(65, "E");
    _wo.register_option(65, "G");
    _wo.register_option(100, "F");
    _wo.load_options();

    /*
    std::cout << -100 << " : " << _wo.query(-100) << std::endl;
    std::cout << 1 << " : "  << _wo.query(1) << std::endl;
    std::cout << 65 << " : "  << _wo.query(65) << std::endl;
    std::cout << 95 << " : "  << _wo.query(95) << std::endl;
    std::cout << 45 << " : "  << _wo.query(45) << std::endl;
    std::cout << 79 << " : "  << _wo.query(79) << std::endl;
    std::cout << 81 << " : "  << _wo.query(81) << std::endl;
    */
    /*
    for(size_t i = 0; i < 100; i++){
        int _r = _wo.rand();
        std::cout << _r << " : " << _wo.query(_r) << std::endl;
    }
    */

    std::cout << _wo.min() << std::endl;
    std::cout << _wo.max() << std::endl;
    

    std::cout << "END" << std::endl;
    return 0;
}