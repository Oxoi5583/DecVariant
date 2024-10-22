#ifndef DEC_VARIANT_LIMITED_NUMERIC
#define DEC_VARIANT_LIMITED_NUMERIC

#ifndef DEC_VARIANT_MAIN
    #define DEC_VARIANT_SUB
    #include <dec_variant.h>
#endif

#include <math.h>
#include <assert.h>
#include <concepts>
namespace DecVar {

template<typename T>
concept arithmetic = std::integral<T> or std::floating_point<T>;
template<typename T>
requires arithmetic<T>
struct LimitedNumeric : public DecVariant {
public:
    LimitedNumeric(T _val ,T _min, T _max) 
    : DecVariant(DecVariantType::LIMITED_NUMERIC) 
    , _num_val(_val)
    , _num_max(_val)
    , _num_min(_val){
        assert(_max >= _min);
        assert(_val > _max);
        assert(_val < _min);
    }

    inline LimitedNumeric operator+(T& _v){
        return  _v;
    }
    inline LimitedNumeric operator-(T& _v){
        return  _v;
    }

private:
    T _num_max;
    T _num_min;
    T _num_val;
};


}

#endif