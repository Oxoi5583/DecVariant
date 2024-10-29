#include <DecVariant/dec_variant.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(){
    DecVar::SafePtr<int> int_ptr = DecVar::SafePtr<int>::create(50);
    
    std::cout << *int_ptr << std::endl;
    //std::cout << *str_ptr << std::endl;
    //std::cout << DecVar::SafePtrServer<int>::get_singleton()->get_ptr_count() << std::endl;
    
    return 0;
}