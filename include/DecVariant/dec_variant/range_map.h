
#ifndef DEC_VARIANT_RANGE_MAP
#define DEC_VARIANT_RANGE_MAP

#include <algorithm>
#include <limits>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <memory>

#ifndef DEC_VARIANT_MAIN
    #define DEC_VARIANT_SUB
    #include <DecVariant/dec_variant.h>
#endif

namespace DecVar {


template<typename T>
class RangeMap{
private:
    template<typename F>
    class RangeMapNode{
    public:
        int _fm;
        int _to;
        F _val;
        RangeMapNode<F>* left_child = nullptr;
        RangeMapNode<F>* right_child = nullptr;


        inline bool emplace_child_node(RangeMapNode* _node){
            bool _is_smaller    = _is_node_smaller(_node);
            bool _is_bigger     = _is_node_bigger(_node);
            bool _is_intersect  = _is_node_intersect(_node);
            
            if(_is_intersect){
                
                throw std::invalid_argument( "[RangeMapNode] Two Range of Nodes should not intersect.");
            }
            if(_is_smaller){
                if(left_child == nullptr){
                    left_child = _node;
                }else{
                    left_child->emplace_child_node(_node);
                }
            }
            if(_is_bigger){
                if(right_child == nullptr){
                    right_child = _node;
                }else{
                    right_child->emplace_child_node(_node);
                }
            }
            return true;
        }

        inline bool _is_node_bigger(RangeMapNode<F>* _node) const{
            return _node->_fm >= this->_to;
        }
        inline bool _is_node_intersect(RangeMapNode<F>* _node) const{
            return std::max(this->_fm, _node->_fm) < std::min(this->_to, _node->_to);
        }
        inline bool _is_node_smaller(RangeMapNode<F>* _node) const{
            return _node->_to <= this->_fm;
        }
        
        inline bool _is_key_bigger(int _k) const{
            return _k > _to;
        }
        inline bool _is_key_intersect(int _k) const{
            return _fm <= _k && _k <= _to;
        }
        inline bool _is_key_smaller(int _k) const{
            return _k < _fm;
        }

        RangeMapNode(int _f, int _t, F _v)
        : _fm(_f)
        , _to(_t)
        , _val(_v) 
        , left_child(nullptr)
        , right_child(nullptr){
            if(_fm > _to){
                throw std::invalid_argument( "[RangeMapNode] From Value have to be bigger than To Value.");
            }
        }
        RangeMapNode(RangeMapNode<F>& _another)
        : _fm(_another._fm)
        , _to(_another._to)
        , _val(_another._val) 
        , left_child(_another.left_child)
        , right_child(_another.right_child){}
    };

    std::vector<std::unique_ptr<RangeMapNode<T>>> _range_map_nodes;
    inline RangeMapNode<T>* _get_last_map_node_ptr(){
        return _range_map_nodes.back().get();
    }
    
    RangeMapNode<T>* _root_node = nullptr;

    int _min_range = std::numeric_limits<int>::max();
    int _max_range = std::numeric_limits<int>::min();

    std::unordered_map<int, T*> _cache_result;
public:
    inline void emplace(int _fm, int _to, T _val){
        if(_fm < _min_range){
            _min_range = _fm;
        }
        if(_to > _max_range){
            _max_range = _to;
        }
        
        if(_range_map_nodes.empty()){
            _range_map_nodes.push_back((std::make_unique<RangeMapNode<T>>(_fm,_to,_val)));
            _root_node = _get_last_map_node_ptr();
        }else{
            _range_map_nodes.push_back((std::make_unique<RangeMapNode<T>>(_fm,_to,_val)));
            _root_node->emplace_child_node(_get_last_map_node_ptr());
        }
        clear_result_cache();
    }
    inline int size(){
        return _range_map_nodes.size();
    }

    inline T* lookup_ptr(int _k){
        if(_cache_result.contains(_k)){
            return _cache_result[_k];
        }

        T* ret = &_root_node->_val;

        RangeMapNode<T>* ptr = _root_node;
        while(true){
            bool _is_bigger     = ptr->_is_key_bigger(_k);
            bool _is_intersect  = ptr->_is_key_intersect(_k);
            bool _is_smaller    = ptr->_is_key_smaller(_k);
            bool _is_left_exists = ptr->left_child != nullptr;
            bool _is_right_exists = ptr->right_child != nullptr;

            if(_is_intersect){
                ret = &ptr->_val;
                break;
            }else{
                if(_is_bigger){
                    if(_is_right_exists){
                        ptr = ptr->right_child;
                    }else{
                        ret = &ptr->_val;
                        break;
                    }
                }else{
                    if(_is_left_exists){
                        ptr = ptr->left_child;
                    }else{
                        ret = &ptr->_val;
                        break;
                    }
                }
            }
        }
        
        _cache_result.emplace(_k, ret);
        return ret;
    }
    inline T lookup(int _k){
        return *lookup_ptr(_k);
    }

    inline void compute_result_cache(){
        for(int i =_min_range; i <= _max_range; i++){
            T* ret = lookup_ptr(i);
            _cache_result.emplace(i, ret);
        }
    }
    inline void compute_result_cache(int _start, int _end){
        for(int i =_start; i <= _end; i++){
            T* ret = lookup_ptr(i);
            _cache_result.emplace(i, ret);
        }
    }
    inline void clear_result_cache(){
        _cache_result.clear();
    }
};


}

#endif