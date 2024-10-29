
#ifndef DEC_VARIANT_SAFE_PTR
#define DEC_VARIANT_SAFE_PTR

#include <sys/stat.h>
#ifndef DEC_VARIANT_MAIN
    #define DEC_VARIANT_SUB
    #include <DecVariant/dec_variant.h>
    #include <DecVariant/dec_variant/unique_id.h>
#endif

#include <iostream>
#include <unordered_map>

namespace DecVar {

    ///////////////////////////////////////////////////////////////////////////////////
    //  A Simple Smart Pointer which was centralized managed by SafePtrServer        //
    //  This Smart Pointer var will only be deleted after all copy was destructed.   //
    //  The design of this smart pointer is for ensure the existence of the pointer  //
    //  and prevent the illegal access.                                              //
    //  Not thread-safe supported yet.                                                         //
    ///////////////////////////////////////////////////////////////////////////////////

template<typename  T>
class SafePtrServer {
public:
    inline static SafePtrServer<T>* get_singleton(){
        if(ptr == nullptr){
            ptr = new SafePtrServer<T>();
        }
        return ptr;
    };

    inline void register_ptr(UniqueId& _uid,T* _ptr){
        if(_ptr_map.contains(_uid)){
            _ptr_ref[_uid]++;
        }else{
            _ptr_map.emplace(_uid , _ptr);
            _ptr_ref.emplace(_uid , 1);
        }
    }
    inline void register_ptr(UniqueId& _uid){
        _ptr_ref[_uid]++;
    }
    inline void release_ptr(UniqueId& _uid){
        _ptr_ref[_uid]--;
        if(_ptr_ref[_uid] <= 0){
            T* _ptr  = _ptr_map[_uid];
            delete _ptr;
            
            auto iter1 = _ptr_ref.find(_uid);
            _ptr_ref.erase(iter1);
            auto iter2 = _ptr_map.find(_uid);
            _ptr_map.erase(iter2);
        }
    }

    inline int get_ptr_count() const{
        return  _ptr_map.size();
    }
    inline int get_ref(UniqueId& _uid){
        return  _ptr_ref[_uid];
    }
private:
    inline static SafePtrServer<T>* ptr = nullptr;

    std::unordered_map<UniqueId, T*> _ptr_map;
    std::unordered_map<UniqueId, int> _ptr_ref;
};

template<typename  T>
class SafePtr {
private:
    SafePtrServer<T>* _server;
    UniqueId _uid;
    T* _ptr;
public:
    SafePtr(T _val)
    : _server(SafePtrServer<T>::get_singleton())
    , _uid(UniqueId())
    , _ptr(new T(_val)){
        _server->register_ptr(_uid, _ptr);
    }
    SafePtr(const SafePtr<T>& _another)
    : _server(_another._server)
    , _uid(_another._uid)
    , _ptr(_another._ptr){
        _server->register_ptr(_uid, _ptr);
    }
    static SafePtr New(T _val){
        return SafePtr<T>(_val);
    }

    ~SafePtr(){
        _server->release_ptr(_uid);
    }


    inline int get_ref(){
        return _server->get_ref(_uid);
    }
    inline SafePtr& operator=(const SafePtr& _another){
        if(this != &_another){
            _server->release_ptr(_uid);
            this->_server = _another._server;
            this->_ptr = _another._ptr;
            this->_uid = _another._uid;
            _server->register_ptr(_uid);
        }
        return *this;
    }
    inline T& operator*(){
        return *_ptr;
    }
    inline T* operator->() const{
        return _ptr;
    }
    inline bool operator==(const SafePtr& _r_ptr){
        return this->_ptr == _r_ptr._ptr;
    }
    friend class SafePtrServer<T>;
};


}

/*
Example : 

int main(){
    DecVar::SafePtr<int> int_ptr = DecVar::SafePtr<int>::New(50);

    test(int_ptr);
    auto str_ptr = test2();
    
    //std::cout << *int_ptr << std::endl;
    //std::cout << *str_ptr << std::endl;
    //std::cout << DecVar::SafePtrServer<int>::get_singleton()->get_ptr_count() << std::endl;
    
    return 0;
}

*/



#endif