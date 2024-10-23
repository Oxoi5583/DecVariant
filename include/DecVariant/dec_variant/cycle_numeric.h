#ifndef DEC_VARIANT_CYCLE_NUMERIC
#define DEC_VARIANT_CYCLE_NUMERIC

#ifndef DEC_VARIANT_MAIN
    #define DEC_VARIANT_SUB
    #include <DecVariant/dec_variant.h>
#endif

#include <string>
#include <algorithm>
#include <assert.h>
#include <concepts>

namespace DecVar {

template<typename T>
requires arithmetic<T>
struct CycleNumeric : public DecVariant{
private:
    T _num_max;
    T _num_min;
    T _num_val;

    template<typename N>
    requires arithmetic<N>
    inline static N cycle(N _val, N _min, N _max){
        N _ret = _val;
        if(_val > _max){
            N _diff = _val - _max;
            _ret = _min + _diff;
        }
        if(_val < _min){
            N _diff = _min - _val;
            _ret = _max - _diff;
        }
        return _ret;
    }
    inline static int cycle(int _val, int _min, int _max){
        int _ret = _val;
        if(_val > _max){
            int _diff = _val - _max - 1;
            _ret = _min + _diff;
        }
        if(_val < _min){
            int _diff = _min - _val - 1;
            _ret = _max - _diff;
        }
        return _ret;
    }


public:
    CycleNumeric(T _val ,T _min, T _max)
    : DecVariant(DecVariantType::CYCLE_NUMERIC)
    , _num_val(_val)
    , _num_max(_max)
    , _num_min(_min) {
        // Check if input value fit
        assert(_max >= _min);
        assert(_val <= _max);
        assert(_val >= _min);
    }

    template<typename N>
    requires arithmetic<N>
    inline CycleNumeric operator+(const N& _v){
        this->_num_val = cycle(this->_num_val + _v, this->_num_min, this->_num_max);
        return *this;
    }
    template<typename N>
    requires arithmetic<N>
    inline CycleNumeric operator-(const N& _v){
        this->_num_val = cycle(this->_num_val - _v, this->_num_min, this->_num_max);
        return *this;
    }
    template<typename N>
    requires arithmetic<N>
    inline CycleNumeric operator=(const N& _v){
        this->_num_val = cycle((T)_v, this->_num_min, this->_num_max);
        return *this;
    }
    template<typename N>
    requires arithmetic<N>
    inline CycleNumeric operator*(const N& _v){
        this->_num_val = cycle(this->_num_val * _v, this->_num_min, this->_num_max);
        return *this;
    }
    template<typename N>
    requires arithmetic<N>
    inline CycleNumeric operator/(const N& _v){
        this->_num_val = cycle(this->_num_val / _v, this->_num_min, this->_num_max);
        return *this;
    }
    template<typename N>
    requires arithmetic<N>
    inline CycleNumeric operator==(const N& _v){
        return this->_num_val == _v;
    }
    template<typename N>
    requires arithmetic<N>
    inline CycleNumeric operator!=(const N& _v){
        return this->_num_val != _v;
    }
    template<typename N>
    requires arithmetic<N>
    inline CycleNumeric operator>=(const N& _v){
        return this->_num_val >= _v;
    }
    template<typename N>
    requires arithmetic<N>
    inline CycleNumeric operator<=(const N& _v){
        return this->_num_val <= _v;
    }
    template<typename N>
    requires arithmetic<N>
    inline CycleNumeric operator+=(const N& _v){
        this->_num_val = cycle(this->_num_val + _v, this->_num_min, this->_num_max);
        return *this;
    }
    template<typename N>
    requires arithmetic<N>
    inline CycleNumeric operator-=(const N& _v){
        this->_num_val = cycle(this->_num_val - _v, this->_num_min, this->_num_max);
        return *this;
    }


    inline CycleNumeric operator+(const CycleNumeric& _v){
        this->_num_val = cycle(this->_num_val + _v._num_val, this->_num_min, this->_num_max);
        return *this;
    }
    inline CycleNumeric operator-(const CycleNumeric& _v){
        this->_num_val = cycle(this->_num_val - _v._num_val, this->_num_min, this->_num_max);
        return *this;
    }
    inline CycleNumeric operator=(const CycleNumeric& _v){
        this->_num_val = cycle((T)_v._num_val, this->_num_min, this->_num_max);
        return *this;
    }
    inline CycleNumeric operator*(const CycleNumeric& _v){
        this->_num_val = cycle(this->_num_val * _v._num_val, this->_num_min, this->_num_max);
        return *this;
    }
    inline CycleNumeric operator/(const CycleNumeric& _v){
        this->_num_val = cycle(this->_num_val / _v._num_val, this->_num_min, this->_num_max);
        return *this;
    }
    inline CycleNumeric operator==(const CycleNumeric& _v){
        return this->_num_val == _v._num_val;
    }
    inline CycleNumeric operator!=(const CycleNumeric& _v){
        return this->_num_val != _v._num_val;
    }
    inline CycleNumeric operator>=(const CycleNumeric& _v){
        return this->_num_val >= _v._num_val;
    }
    inline CycleNumeric operator<=(const CycleNumeric& _v){
        return this->_num_val <= _v._num_val;
    }

    inline CycleNumeric operator++(int){
        this->_num_val = cycle(this->_num_val + 1, this->_num_min, this->_num_max);
        return *this;
    }
    inline CycleNumeric operator--(int){
        this->_num_val = cycle(this->_num_val - 1, this->_num_min, this->_num_max);
        return *this;
    }
    inline CycleNumeric operator+=(const CycleNumeric& _v){
        this->_num_val = cycle(this->_num_val + _v._num_val, this->_num_min, this->_num_max);
        return *this;
    }
    inline CycleNumeric operator-=(const CycleNumeric& _v){
        this->_num_val = cycle(this->_num_val - _v._num_val, this->_num_min, this->_num_max);
        return *this;
    }

    inline std::string to_str(){
        return std::to_string(this->_num_val);
    }
    inline T get(){
        return _num_val;
    }
};

}


#endif