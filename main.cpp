#include <iostream>
#include <string>
#include "persistent_set.h"

using namespace std;
using namespace bezborodov;

template<typename T, template<typename> class smart_ptr>
void check() {
    smart_ptr<T> ptr1; // default ctor
    smart_ptr<T> ptr2(ptr1); // copy ctor
    smart_ptr<T> ptr3(std::move(ptr1)); // move ctor
    ptr3 = ptr2; // copy assign
    ptr3 = std::move(ptr1); // move assign
    smart_ptr<T> ptr4(new T);
    ptr4.reset(new T);
}

int main() {
    check<int, pointers::shared_ptr>();
    check<std::string, pointers::shared_ptr>();
    return 0;
}
