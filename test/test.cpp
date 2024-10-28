#include <DecVariant/dec_variant.h>
#include <DecVariant/dec_variant/safe_ptr.h>
#include <iostream>
#include <string>

using namespace std;

void test(DecVar::SafePtr<int>& _p){
    _p = DecVar::SafePtr<int>::New(5000);
}

DecVar::SafePtr<string> test2(){
    auto _ret = DecVar::SafePtr<string>::New("TEST");
    return _ret;
}

int main(){
    auto _p = LOCK_KEY_GENERATOR->create_pair_of_lock_key();
    DecVar::Lock _l = _p.first;
    DecVar::Key _k = _p.second;

    _l << _k;


    if (_l) {
        std::cout << "Lock was opened." << std::endl;
    }

    return 0;
}
