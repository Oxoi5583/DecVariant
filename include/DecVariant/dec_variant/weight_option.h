
#ifndef DEC_VARIANT_WEIGHT_OPTION
#define DEC_VARIANT_WEIGHT_OPTION

#include <algorithm>
#include <cassert>
#include <climits>
#include <limits>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <map>
#include <set>
#include <vector>
#include <memory>

#ifndef DEC_VARIANT_MAIN
    #define DEC_VARIANT_SUB
    #include <DecVariant/dec_variant/random_num.h>
    #include <DecVariant/dec_variant/range_map.h>
    #include <DecVariant/dec_variant.h>
#endif

namespace DecVar {




template<typename T>
class WeightOption{
public:
    inline void register_option(int _threshold, T _option){
        bool is_registered_threshold_duplicated = _thresholds_for_check_duplicate.contains(_threshold);
        assert(!is_registered_threshold_duplicated);

        _thresholds_for_check_duplicate.emplace(_threshold);
        _thresholds.push_back(_threshold);
        _options.emplace(_threshold, _option);
        std::sort(_thresholds.begin(), _thresholds.end());
    }
    inline void set_range(int _min, int _max){
        _is_range_set = true;
        _range_min = _min;
        _range_max = _max;
    }
    inline void load_options(){
        _is_options_loaded = true;

        const int _min = _thresholds.front();
        const int _max = _thresholds.back();

        int _last_val;
        if(!_is_range_set){
            _last_val = _min - 10;
        }else{
            _last_val = _range_min;
        }

        bool _is_first = true;
        for(auto& it : _thresholds){
            assert(it >= _min && it <= _max);

            if(!_is_first){
                _range_map.emplace(_last_val, it, _options[_last_val]);
            }else{
                _is_first =false;
            }
            _last_val = it;
        }
        
        if(!_is_range_set){
            _range_map.emplace(_last_val, _last_val + 10, _options[_last_val]);
        }else{
            _range_map.emplace(_last_val, _range_max, _options[_last_val]);
        }
        

        _range_map.compute_result_cache();
    }
    inline T query(int _k){
        if(!_is_options_loaded){
            load_options();
        }
        return _range_map.lookup(_k);
    }
    inline int min(){
        return _range_map.min();
    }
    inline int max(){
        return _range_map.max();
    }
    inline int rand(){
        return RandomNum(min(),max()).get();
    }
private:
    RangeMap<T> _range_map;

    bool _is_options_loaded = false;

    bool _is_range_set = false;
    int _range_min = INT_MIN;
    int _range_max = INT_MAX;

    std::set<int> _thresholds_for_check_duplicate;
    std::vector<int> _thresholds;
    std::map<int, T> _options;
};


}

// Test Script
/*
int main(){
    std::cout << "START" << std::endl;
    DecVar::WeightOption<string> _wo;
    _wo.set_range(0, 150);
    _wo.register_option(10, "A");
    _wo.register_option(25, "B");
    _wo.register_option(50, "C");
    _wo.register_option(80, "D");
    _wo.register_option(65, "E");
    _wo.register_option(100, "F");
    _wo.load_options();


    std::cout << -100 << " : " << _wo.query(-100) << std::endl;
    std::cout << 1 << " : "  << _wo.query(1) << std::endl;
    std::cout << 65 << " : "  << _wo.query(65) << std::endl;
    std::cout << 95 << " : "  << _wo.query(95) << std::endl;
    std::cout << 45 << " : "  << _wo.query(45) << std::endl;
    std::cout << 79 << " : "  << _wo.query(79) << std::endl;
    std::cout << 81 << " : "  << _wo.query(81) << std::endl;

    for(size_t i = 0; i < 100; i++){
        int _r = _wo.rand();
        std::cout << _r << " : " << _wo.query(_r) << std::endl;
    }
    

    std::cout << _wo.min() << std::endl;
    std::cout << _wo.max() << std::endl;
    

    std::cout << "END" << std::endl;
    return 0;
}
*/


#endif