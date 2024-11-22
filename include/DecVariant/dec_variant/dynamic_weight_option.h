
#ifndef DEC_VARIANT_DYNAMIC_WEIGHT_OPTION
#define DEC_VARIANT_DYNAMIC_WEIGHT_OPTION



#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <numeric>
#include <vector>

#ifndef DEC_VARIANT_MAIN
    #define DEC_VARIANT_SUB
    #include <DecVariant/dec_variant/random_num.h>
    #include <DecVariant/dec_variant.h>
#endif

namespace DecVar {

template<typename T>
class DynamicWeightOption {

typedef int Weight;

protected:

    template<typename F>
    struct Option{
    public:
        Option(Option<F>& _another)
        : _static_weight(_another._static_weight)
        , _weight_ptr(_another._weight_ptr)
        , _value(_another._value)
        , _is_weight_static(_another._is_weight_static){}
        Option(Weight* _input_weight, F _input_value)
        : _static_weight(0)
        , _weight_ptr(_input_weight)
        , _value(_input_value)
        , _is_weight_static(false){}
        Option(Weight _input_weight, F _input_value)
        : _static_weight(_input_weight)
        , _weight_ptr(&_static_weight)
        , _value(_input_value)    
        , _is_weight_static(true){}
        ~Option(){}
        

        inline Weight get_weight(){
            return *_weight_ptr;
        }
        inline F get_value(){
            return _value;
        }
        inline bool get_is_weight_static(){
            return _is_weight_static;
        }

    private:
        bool    _is_weight_static = false;
        Weight  _static_weight = 0;
        Weight* _weight_ptr = nullptr;
        F       _value;

    };

public:
    inline void register_option(Weight* _weight, T _value){
        _options.push_back(std::make_unique<Option<T>>(_weight, _value));
    }
    inline void register_option(Weight _weight, T _value){
        _static_weight_sum += _weight;
        _options.push_back(std::make_unique<Option<T>>(_weight, _value));
    }

    inline int get_total_weight(){
        Weight ret = _static_weight_sum;
        for(auto& _option : _options){
            if(!_option->get_is_weight_static()){
                ret += _option->get_weight();
            }
        }
        return ret;
    }

    inline T get_rand_result(){
        int _k = _get_rand_key();
        return _query(_k);
    }
private:
    std::vector<std::unique_ptr<Option<T>>> _options;
    int _static_weight_sum = 0;

    inline int _get_rand_key(){
        return RandomNum(1, get_total_weight()).get();
    }
    inline T _query(int _k){
        Weight _sum = 0;
        for(auto& _option : _options){
            _sum += _option->get_weight();

            if(_sum >= _k){
                return _option->get_value();
            }
        }

        throw std::invalid_argument( "[DynamicWeightOption] Query Key have to be in range of 0 to total weight of options.");
    }

};

}


// Test Code
/*
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
*/

#endif