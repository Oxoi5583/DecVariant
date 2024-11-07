#include <DecVariant/dec_variant.h>
#include <cstddef>
#include <iostream>
#include <string>


using namespace std;

int main(){
    std::cout << "START" << std::endl;
    DecVar::DynamicWeightOption<string> _dwo;
    
    int a = 30;
    _dwo.register_option(10, "A");
    _dwo.register_option(20, "B");
    _dwo.register_option(&a, "C");
    _dwo.register_option(40, "D");
    _dwo.register_option(900, "E");

    std::map<string,int> _test_map;
    _test_map.emplace("A",0);
    _test_map.emplace("B",0);
    _test_map.emplace("C",0);
    _test_map.emplace("D",0);

    int total = 0;
    for(size_t i = 0; i < 100000; i++){
        string _a = _dwo.get_rand_result();
        //std::cout << _a << std::endl;

        total++;
        _test_map[_a]++;
    }

    for(auto& it : _test_map){
        std::cout << it.first << " : " << it.second << " ( " << (double)it.second/(double)total *100 << "% )" << std::endl;
        
    }

    std::cout << "END" << std::endl;
    return 0;
}