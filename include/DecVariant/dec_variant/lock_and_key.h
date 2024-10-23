#ifndef DEC_VARIANT_LOCK_AND_KEY
#define DEC_VARIANT_LOCK_AND_KEY


#include <ios>
#include <utility>
#ifndef DEC_VARIANT_MAIN
    #define DEC_VARIANT_SUB
    #include <DecVariant/dec_variant.h>
    #include "DecVariant/dec_variant/random_server.h"
    #include <DecVariant/dec_variant/random_code.h>
#endif



namespace DecVar {

typedef std::string Code;

struct Key{
private:
    const Code _password;
    inline Key(const Code& _pw = "")
    : _password(_pw){}

public:
    inline ~Key(){}
    friend struct Lock;
    friend class LockAndKeyGenerator;
};

struct Lock{
private:
    const Code _password;
    inline Lock(const Code& _pw = "")
    : _password(_pw){}


    bool locked;
public:
    inline ~Lock(){}
    inline void open(const Key& _key){
        if(_key._password == this->_password){
            locked = false;
        }
    }
    inline void lock(){
        locked = true;
    }

    inline bool is_locked(){
        return locked;
    }

    inline explicit operator bool(){
        return !locked;
    }
    inline Lock* operator<<(Key& _key){
        this->open(_key);
        return this;
    }

    friend struct Key;
    friend class LockAndKeyGenerator;
};

class LockAndKeyGenerator{
private:
    inline static LockAndKeyGenerator* ptr = nullptr;

    int _password_length = 20;
public:
    inline static LockAndKeyGenerator* get_singleton(){
        if(ptr == nullptr){
            ptr = new LockAndKeyGenerator();
        }
        return ptr;
    }

    inline std::pair<Lock, Key> create_pair_of_lock_key(){
        Code _gen_pw = RandomCode(_password_length).get();
        Lock _l = Lock(_gen_pw);
        Key _k = Key(_gen_pw);
        std::pair<Lock, Key> _ret = std::make_pair(_l,_k);
        return _ret;
    }

};


}

#define LOCK_KEY_GENERATOR DecVar::LockAndKeyGenerator::get_singleton()

#endif