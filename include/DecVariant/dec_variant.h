#pragma once

namespace DecVar {


enum class DecVariantType{
    ONE_WAY_BOOL,
    UNIQUE_ID,
    LIMITED_NUMERIC,
    RANDOM_CODE,
    RANDOM_NUM,
    CYCLE_VECTOR,
    CYCLE_NUMERIC,
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

#include <DecVariant/dec_variant_ext/arithmetic.h>

#define DEC_VARIANT_MAIN
#ifndef DEC_VARIANT_SUB

#include <DecVariant/dec_variant/one_way_bool.h>
#include <DecVariant/dec_variant/unique_id.h>
#include <DecVariant/dec_variant/limited_numeric.h>
#include <DecVariant/dec_variant/random_server.h>
#include <DecVariant/dec_variant/random_code.h>
#include <DecVariant/dec_variant/random_num.h>
#include <DecVariant/dec_variant/cycle_numeric.h>
#include <DecVariant/dec_variant/cycle_vector.h>

#endif