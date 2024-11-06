
#ifndef DEC_VARIANT_WEIGHT_OPTION
#define DEC_VARIANT_WEIGHT_OPTION

#include <algorithm>
#include <limits>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <memory>

#ifndef DEC_VARIANT_MAIN
    #define DEC_VARIANT_SUB
    #include <DecVariant/dec_variant/range_map.h>
    #include <DecVariant/dec_variant.h>
#endif

namespace DecVar {




template<typename T>
class WeightOption{
public:
    inline void register_option(int _threshold, T _option){
        _thresholds.push_back(_threshold);
        _options.emplace(_threshold, _option);
        std::sort(_thresholds.begin(), _thresholds.end());
    }
    inline void load_options(){
        _is_options_loaded = true;

        const int _min = _thresholds.front();
        const int _max = _thresholds.back();

        int _last_val = _min - 10;
        bool _is_first = true;
        for(auto& it : _thresholds){
            if(!_is_first){
                _range_map.emplace(_last_val, it, _options[_last_val]);
            }else{
                _is_first =false;
            }
            _last_val = it;
        }
        _range_map.emplace(_last_val, _last_val + 10, _options[_last_val]);

        _range_map.compute_result_cache();
    }
    inline T query(int _k){
        if(!_is_options_loaded){
            load_options();
        }
        return _range_map.lookup(_k);
    }
private:
    RangeMap<T> _range_map;

    bool _is_options_loaded = false;

    std::vector<int> _thresholds;
    std::map<int, T> _options;
};

}

#endif