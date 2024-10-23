#ifndef DEC_VARIANT_RANDOM_SERVER
#define DEC_VARIANT_RANDOM_SERVER

#ifndef DEC_VARIANT_MAIN
    #define DEC_VARIANT_SUB
    #include <DecVariant/dec_variant.h>
#endif

#include <cstddef>
#include <string>
#include <random>
#include <ctime>
#include <map>

namespace DecVar {

typedef unsigned int length;

class RandomGenerator {
private:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> distr;
public:
    RandomGenerator(int min, int max)
        : rd(), gen(rd()), distr(min, max){};
    ~RandomGenerator();
    inline int get_rand(){
        return distr(gen);
    }
};

typedef std::map<std::pair<int,int>,RandomGenerator*> GeneratorDict;

class RandomServer {
private:
    inline static RandomServer* ptr;
    GeneratorDict g_dict = GeneratorDict();
    RandomGenerator* rand_char_gen = new RandomGenerator(0,35);
    RandomServer(){};
public:
    ~RandomServer(){};

    inline static RandomServer* get_singleton(){
        if(ptr == nullptr){
            ptr = new RandomServer();
        }
        return ptr;
    }
    inline int get_random_int(int _min, int _max){
        std::pair range = std::make_pair(_min,_max);
        if(g_dict.contains(range)){
            RandomGenerator& _rg = *g_dict[range];
            return _rg.get_rand();
        }else{
            RandomGenerator* new_generator = new RandomGenerator(_min,_max);
            g_dict.insert_or_assign(range,new_generator);
            return new_generator->get_rand();
        }
        return 0;
    }
    inline char get_random_char(){
        int ret_r = rand_char_gen->get_rand();
        char ret;
        if (ret_r < 10){
            ret =  '0' + ret_r;
        }else{
            ret = 'A' + ret_r - 10;
        }
        return ret;
    }
    inline std::string get_randow_code(const length& _l = 10){
        std::string ret = "";
        for(size_t i = 0; i < _l; i++){
            ret += get_random_char();
        }
        return  ret;
    }
};

inline static RandomServer* ptr = nullptr;

}

#endif