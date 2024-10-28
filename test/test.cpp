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
    DecVar::SafePtr<int> int_ptr = DecVar::SafePtr<int>::New(50);

    test(int_ptr);
    auto str_ptr = test2();
    
    std::cout << *int_ptr << std::endl;
    std::cout << *int_ptr << std::endl;
    std::cout << DecVar::SafePtrServer<int>::get_singleton()->get_ptr_count() << std::endl;
    
    return 0;
}