#ifndef DEC_VARIANT_LIMITED_NUMERIC
#define DEC_VARIANT_LIMITED_NUMERIC


#ifndef DEC_VARIANT_MAIN
    #define DEC_VARIANT_SUB
    #include <dec_variant.h>
#endif

#include <string>
#include <algorithm>
#include <assert.h>
#include <concepts>
namespace DecVar {

template<typename T>
concept arithmetic = std::integral<T> or std::floating_point<T>;

template<typename T>
requires arithmetic<T>
struct LimitedNumeric : public DecVariant {
    /////////////////////////////////////////////////////////////
    //  A Simple struct for a number which would out of range  //
    /////////////////////////////////////////////////////////////
public:
    LimitedNumeric(T _val ,T _min, T _max) 
    : DecVariant(DecVariantType::LIMITED_NUMERIC) 
    , _num_val(_val)
    , _num_max(_max)
    , _num_min(_min){
        // Check if input value fit
        assert(_max >= _min);
        assert(_val <= _max);
        assert(_val >= _min);
    }


    template<typename N>
    requires arithmetic<N>
    inline LimitedNumeric operator+(const N& _v){
        this->_num_val = std::clamp(this->_num_val + _v, this->_num_min, this->_num_max);
        return *this;
    }
    template<typename N>
    requires arithmetic<N>
    inline LimitedNumeric operator-(const N& _v){
        this->_num_val = std::clamp(this->_num_val - _v, this->_num_min, this->_num_max);
        return *this;
    }
    template<typename N>
    requires arithmetic<N>
    inline LimitedNumeric operator=(const N& _v){
        this->_num_val = std::clamp((T)_v, this->_num_min, this->_num_max);
        return *this;
    }
    template<typename N>
    requires arithmetic<N>
    inline LimitedNumeric operator*(const N& _v){
        this->_num_val = std::clamp(this->_num_val * _v, this->_num_min, this->_num_max);
        return *this;
    }
    template<typename N>
    requires arithmetic<N>
    inline LimitedNumeric operator/(const N& _v){
        this->_num_val = std::clamp(this->_num_val / _v, this->_num_min, this->_num_max);
        return *this;
    }
    template<typename N>
    requires arithmetic<N>
    inline LimitedNumeric operator==(const N& _v){
        return this->_num_val == _v;
    }
    template<typename N>
    requires arithmetic<N>
    inline LimitedNumeric operator!=(const N& _v){
        return this->_num_val != _v;
    }
    template<typename N>
    requires arithmetic<N>
    inline LimitedNumeric operator>=(const N& _v){
        return this->_num_val >= _v;
    }
    template<typename N>
    requires arithmetic<N>
    inline LimitedNumeric operator<=(const N& _v){
        return this->_num_val <= _v;
    }
    template<typename N>
    requires arithmetic<N>
    inline LimitedNumeric operator+=(const N& _v){
        this->_num_val = std::clamp(this->_num_val + _v, this->_num_min, this->_num_max);
        return *this;
    }
    template<typename N>
    requires arithmetic<N>
    inline LimitedNumeric operator-=(const N& _v){
        this->_num_val = std::clamp(this->_num_val - _v, this->_num_min, this->_num_max);
        return *this;
    }


    inline LimitedNumeric operator+(const LimitedNumeric& _v){
        this->_num_val = std::clamp(this->_num_val + _v._num_val, this->_num_min, this->_num_max);
        return *this;
    }
    inline LimitedNumeric operator-(const LimitedNumeric& _v){
        this->_num_val = std::clamp(this->_num_val - _v._num_val, this->_num_min, this->_num_max);
        return *this;
    }
    inline LimitedNumeric operator=(const LimitedNumeric& _v){
        this->_num_val = std::clamp((T)_v._num_val, this->_num_min, this->_num_max);
        return *this;
    }
    inline LimitedNumeric operator*(const LimitedNumeric& _v){
        this->_num_val = std::clamp(this->_num_val * _v._num_val, this->_num_min, this->_num_max);
        return *this;
    }
    inline LimitedNumeric operator/(const LimitedNumeric& _v){
        this->_num_val = std::clamp(this->_num_val / _v._num_val, this->_num_min, this->_num_max);
        return *this;
    }
    inline LimitedNumeric operator==(const LimitedNumeric& _v){
        return this->_num_val == _v._num_val;
    }
    inline LimitedNumeric operator!=(const LimitedNumeric& _v){
        return this->_num_val != _v._num_val;
    }
    inline LimitedNumeric operator>=(const LimitedNumeric& _v){
        return this->_num_val >= _v._num_val;
    }
    inline LimitedNumeric operator<=(const LimitedNumeric& _v){
        return this->_num_val <= _v._num_val;
    }

    inline LimitedNumeric operator++(int){
        this->_num_val = std::clamp(this->_num_val + 1, this->_num_min, this->_num_max);
        return *this;
    }
    inline LimitedNumeric operator--(int){
        this->_num_val = std::clamp(this->_num_val - 1, this->_num_min, this->_num_max);
        return *this;
    }
    inline LimitedNumeric operator+=(const LimitedNumeric& _v){
        this->_num_val = std::clamp(this->_num_val + _v._num_val, this->_num_min, this->_num_max);
        return *this;
    }
    inline LimitedNumeric operator-=(const LimitedNumeric& _v){
        this->_num_val = std::clamp(this->_num_val - _v._num_val, this->_num_min, this->_num_max);
        return *this;
    }

    inline std::string to_str(){
        return std::to_string(this->_num_val);
    }
private:
    T _num_max;
    T _num_min;
    T _num_val;
};


}


namespace std {
    template<typename T>
    concept arithmetic = std::integral<T> or std::floating_point<T>;
    template<typename T>
    requires arithmetic<T>
    inline std::string to_string(DecVar::LimitedNumeric<T> const &_ln) {
        return _ln.to_str();
    }
}



#endif