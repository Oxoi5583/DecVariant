
#ifndef DEC_VARIANT_ONE_WAY_BOOL
#define DEC_VARIANT_ONE_WAY_BOOL

#include <string>

#ifndef DEC_VARIANT_MAIN
    #define DEC_VARIANT_SUB
    #include <dec_variant.h>
#endif

namespace DecVar {


struct OneWayBool : public DecVariant {
    //////////////////////////////////////////////////////////////////////
    //  A Simple struct which share the same behaviour with bool        //
    //  Yet if the class used as a condition, the val will be filped    //
    //  This struct was design for a one-way-checker                    //
    //////////////////////////////////////////////////////////////////////
public:
    OneWayBool(bool _nv = false) 
        : DecVariant(DecVariantType::ONE_WAY_BOOL) 
        , _origin_val(_nv){

        this->_val = _nv;
    }
    ~OneWayBool(){}
    inline OneWayBool operator=(bool& _v){
        OneWayBool _new_b(_v);
        return  _new_b;
    }
    inline OneWayBool operator=(OneWayBool& _v){
        return  _v;
    }
    inline bool operator==(const OneWayBool& _bool){
        bool old_val = _bool._val;
        this->_val = !_bool._val;
        return _bool._val;
    }
    inline explicit operator bool(){
        bool old_val = this->_val;
        this->_val = !this->_val;
        return old_val;
    }

    inline DecVariant* cast_to_varint(){
        return static_cast<DecVariant*>(this);
    }

    inline bool get_val_without_val_change() const{
        return this->_val;
    }
private:
    bool _val;
    const bool _origin_val;

};

}

namespace std {
    inline std::string to_string(DecVar::OneWayBool const &ow_bool) {
        if(ow_bool.get_val_without_val_change()){
            return  "true";    
        }else {
            return "false";
        }
    }
}


#endif