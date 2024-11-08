#ifndef DEC_VARIANT_CYCLE_VECTOR
#define DEC_VARIANT_CYCLE_VECTOR

#ifndef DEC_VARIANT_MAIN
    #define DEC_VARIANT_SUB
    #include <DecVariant/dec_variant.h>
#endif

#include <vector>

namespace DecVar {

typedef unsigned int index;

template<typename T>
struct CycleVector : public DecVariant{
private:
    std::vector<T> _data;
    index _index = 0;
    index _size;
    T _val;
public:
    CycleVector() 
    : DecVariant(DecVariantType::CYCLE_VECTOR){}
    ~CycleVector(){}

    inline void push_back(T _ele){
        _data.push_back(_ele);
        _size = _data.size();
    }
    inline void pop_back(){
        _data.pop_back();
        _size = _data.size();
    }

    bool next(){
        if(_index >= _size - 1){
            _index = 0;
        }else{
            _index++;
        }
        _val = _data[_index];
        return true;
    }
    inline T get(){
        return _val;
    }
    inline int size(){
        return _size;
    }
};

}


#endif