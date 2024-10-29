#include <DecVariant/dec_variant.h>
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
    while (true){

        DecVar::SafePtr<int> int_ptr2 = int_ptr;
        DecVar::SafePtr<int> int_ptr3 = int_ptr;
        DecVar::SafePtr<int> int_ptr4 = int_ptr3;
        DecVar::SafePtr<int> int_ptr5 = int_ptr4;

        
        std::cout << *int_ptr << std::endl;
        std::cout << DecVar::SafePtrServer<int>::get_singleton()->get_ptr_count() << std::endl;
        std::cout << int_ptr5.get_ref() << std::endl;
        break;
    }
    std::cout << *int_ptr << std::endl;
    std::cout << DecVar::SafePtrServer<int>::get_singleton()->get_ptr_count() << std::endl;
    std::cout << int_ptr.get_ref() << std::endl;
    
    return 0;
}