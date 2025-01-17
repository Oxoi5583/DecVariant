#include <DecVariant/dec_variant.h>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <map>
#include <string>



using namespace std;

int main(){
    std::cout << "START" << std::endl;
    DecVar::WeightOption<string> _wo;
    _wo.set_range(INT8_MIN, INT8_MAX);
    _wo.register_option(-127, "-A");
    _wo.register_option(-50, "A");
    _wo.register_option(-25, "B");
    _wo.register_option(0, "C");
    _wo.register_option(25, "D");
    _wo.register_option(50, "E");
    _wo.register_option(100, "F");
    _wo.load_options();


    std::cout << -100 << " : " << _wo.query(-100) << std::endl;
    std::cout << 1 << " : "  << _wo.query(1) << std::endl;
    std::cout << 65 << " : "  << _wo.query(65) << std::endl;
    std::cout << 95 << " : "  << _wo.query(95) << std::endl;
    std::cout << 45 << " : "  << _wo.query(45) << std::endl;
    std::cout << 79 << " : "  << _wo.query(79) << std::endl;
    std::cout << 81 << " : "  << _wo.query(81) << std::endl;

    for(int i = -100; i < 100; i++){
        std::cout << i << " : " << _wo.query(i) << std::endl;
    }
    

    std::cout << _wo.min() << std::endl;
    std::cout << _wo.max() << std::endl;
    

    std::cout << "END" << std::endl;
    return 0;
}