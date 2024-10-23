#ifndef DEC_VARIANT_RANDOM_CODE
#define DEC_VARIANT_RANDOM_CODE


#include <string>
#ifndef DEC_VARIANT_MAIN
    #define DEC_VARIANT_SUB
    #include <dec_variant.h>
#endif

#ifndef DEC_VARIANT_RANDOM_SERVER
    #include <dec_variant/random_server.h>
#endif

namespace DecVar {

struct RandomCode : public DecVariant {
    ///////////////////////////////////////////////////////////////////////////////////////////
    //  A Simple struct which will get a new Random String with number and UpperCase Char    //
    //  This struct was design for a Simple UID                                              //                         
    ///////////////////////////////////////////////////////////////////////////////////////////
private:
    const length _len;
    const std::string _val ;
public:
    inline RandomCode(length _l = 20) 
    : DecVariant(DecVariantType::RANDOM_CODE) 
    , _len(_l) 
    , _val(RandomServer::get_singleton()->get_randow_code(_l)){};
    inline ~RandomCode(){};


    inline std::string get(){
        return _val;
    }
    inline bool operator==(const RandomCode& _rc){
        return this->_val == _rc._val;
    }
};

}

#endif