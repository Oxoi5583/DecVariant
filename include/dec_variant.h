#pragma once

namespace DecVar {


enum class DecVariantType{
    ONE_WAY_BOOL,
    UNIQUE_ID,
};

struct DecVariant {
    /////////////////////////////////////////
    //  The Base class for all DecVariant  //
    ////////////////////////////////////////
protected:
    DecVariantType var_type;
public:
    DecVariant(DecVariantType _nt) : var_type(_nt){}

    template <typename T>
    T* cast_to(){
        return static_cast<T*>(this);   
    }
};

}

#define DEC_VARIANT_MAIN
#ifndef DEC_VARIANT_SUB

#include <dec_variant/one_way_bool.h>
#include <dec_variant/unique_id.h>

#endif