#ifndef DEC_VARIANT_UNIQUE_ID
#define DEC_VARIANT_UNIQUE_ID

#include <functional>
#ifndef DEC_VARIANT_MAIN
    #define DEC_VARIANT_SUB
    #include <DecVariant/dec_variant.h>
#endif

#include <stdint.h>
#include <algorithm>
#include <limits.h>
#include <string>

namespace DecVar {

typedef unsigned long long LONGUINT;

struct UniqueId : public DecVariant {
    //////////////////////////////////////////////////////////////////////////////
    //  A Simple struct which will get a new const 64bit incremental int value  //
    //  This struct was design for a Simple UID                                 //
    //////////////////////////////////////////////////////////////////////////////
private:
    inline static LONGUINT next_id = 0;
    inline static LONGUINT get_new_id(){
        LONGUINT ret = next_id;
        if (next_id == std::numeric_limits<unsigned int>::max()) {
            next_id = 0;
        }
        next_id++;
        return ret;
    }

    LONGUINT _id;
public:
    UniqueId() : DecVariant(DecVariantType::UNIQUE_ID) ,
                 _id(UniqueId::get_new_id()) {}
    ~UniqueId(){};


    inline const std::string to_str() const{
        return std::to_string(_id);
    } 

    inline const LONGUINT get_val() const{
        return _id;
    }

    inline bool operator==(const UniqueId& _r) const{
        return this->_id == _r._id;
    }
    inline UniqueId& operator=(const UniqueId& _another){
        this->_id = _another._id;
        return *this;
    }
    inline DecVariant* cast_to_varint(){
        return static_cast<DecVariant*>(this);
    }
};

}

namespace std {
    inline std::string to_string(DecVar::UniqueId const &uid) {
        return uid.to_str();
    }
    template <> 
    struct hash<DecVar::UniqueId>
    {
        inline size_t operator()(const DecVar::UniqueId & x) const
        {
            return  std::hash<DecVar::LONGUINT>()(x.get_val());
        }
    };
}


#endif