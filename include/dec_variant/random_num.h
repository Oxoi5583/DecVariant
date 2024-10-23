#ifndef DEC_VARIANT_RANDOM_NUM
#define DEC_VARIANT_RANDOM_NUM

#ifndef DEC_VARIANT_MAIN
    #define DEC_VARIANT_SUB
    #include <dec_variant.h>
#endif

#ifndef DEC_VARIANT_RANDOM_SERVER
    #include <dec_variant/random_server.h>
#endif

namespace DecVar {

struct RandomNum : public DecVariant {
private:
    const int _min;
    const int _max;
    const int _val ;
public:
    inline RandomNum(int min_val = 0, int max_val = 50) 
    : DecVariant(DecVariantType::RANDOM_CODE) 
    , _min(min_val)
    , _max(max_val)
    , _val(RandomServer::get_singleton()->get_random_int(min_val, max_val)){
    };
    inline ~RandomNum(){};


    inline const int get(){
        return _val;
    }
    inline bool operator==(const RandomNum& _rc){
        return this->_val == _rc._val;
    }
};

}

#endif