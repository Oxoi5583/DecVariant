#ifndef DEC_VARIANT_RANDOM_SERVER
#define DEC_VARIANT_RANDOM_SERVER

#include <numeric>
#include <vector>
#ifndef DEC_VARIANT_MAIN
    #define DEC_VARIANT_SUB
    #include <DecVariant/dec_variant.h>
#endif

#include <algorithm>
#include <cstddef>
#include <string>
#include <random>
#include <ctime>
#include <map>
#include <iostream>

namespace DecVar {

typedef unsigned int length;

class UniformRandomGenerator {
private:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> distr;
public:
    UniformRandomGenerator(int min, int max)
        : rd(), gen(rd())
        , distr(min, max){};
    ~UniformRandomGenerator();
    inline int generate(){
        return distr(gen);
    }
};
class NormalRandomGenerator {
private:
    std::random_device rd;
    std::mt19937 gen;
    std::normal_distribution<> distr;
public:
    NormalRandomGenerator(double _mean, double _sigma)
        : rd(), gen(rd())
        , distr(_mean, _sigma){};
    ~NormalRandomGenerator();
    inline double generate(){
        return distr(gen);
    }
};

typedef std::map<std::pair<int,int>     ,UniformRandomGenerator*>    UniformGeneratorDict;
typedef std::map<std::pair<float,float> ,NormalRandomGenerator*>     NormalGeneratorDict;


class RandomServer {
private:
    inline static RandomServer* ptr;
    UniformGeneratorDict ug_dict = UniformGeneratorDict();
    NormalGeneratorDict  ng_dict = NormalGeneratorDict();
    UniformRandomGenerator* rand_char_gen = new UniformRandomGenerator(0,35);
    RandomServer(){};
public:
    ~RandomServer(){};

    inline static RandomServer* get_singleton(){
        if(ptr == nullptr){
            ptr = new RandomServer();
        }
        return ptr;
    }
    inline int get_uniform_distr_random_int(int _min, int _max){
        std::pair range = std::make_pair(_min,_max);
        if(ug_dict.contains(range)){
            UniformRandomGenerator& _rg = *ug_dict[range];
            return _rg.generate();
        }else{
            UniformRandomGenerator* new_generator = new UniformRandomGenerator(_min,_max);
            ug_dict.insert_or_assign(range,new_generator);
            return new_generator->generate();
        }
        return 0;
    }
    inline int get_normal_distr_random_int(double _mean, double _sigma){
        std::pair range = std::make_pair(_mean,_sigma);
        if(ng_dict.contains(range)){
            NormalRandomGenerator& _rg = *ng_dict[range];
            return std::round(_rg.generate());
        }else{
            NormalRandomGenerator* new_generator = new NormalRandomGenerator(_mean,_sigma);
            ng_dict.insert_or_assign(range,new_generator);
            return std::round(new_generator->generate());
        }
        return 0;
    }
    inline double get_normal_distr_random_float(double _mean, double _sigma){
        std::pair range = std::make_pair(_mean,_sigma);
        if(ng_dict.contains(range)){
            NormalRandomGenerator& _rg = *ng_dict[range];
            return _rg.generate();
        }else{
            NormalRandomGenerator* new_generator = new NormalRandomGenerator(_mean,_sigma);
            ng_dict.insert_or_assign(range,new_generator);
            return new_generator->generate();
        }
        return 0;
    }
    inline char get_uniform_distr_random_char(){
        int ret_r = rand_char_gen->generate();
        char ret;
        if (ret_r < 10){
            ret =  '0' + ret_r;
        }else{
            ret = 'A' + ret_r - 10;
        }
        return ret;
    }
    inline std::string get_uniform_distr_random_code(const length& _l = 10){
        std::string ret = "";
        for(size_t i = 0; i < _l; i++){
            ret += get_uniform_distr_random_char();
        }
        return  ret;
    }
};

inline static RandomServer* ptr = nullptr;

}

#endif