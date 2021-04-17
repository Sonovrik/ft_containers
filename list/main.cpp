#include "list.hpp"
#include <unistd.h>

int main() {
    ft::list<int> list(10, 1234);

    list.push_back(12355253);
    std::cout << list.back() << std::endl;
    list.pop_back();
    std::cout << list.back() << std::endl;
    list.push_front(123456);
    std::cout << list.front() << std::endl;
    list.pop_front();
    std::cout << list.front() << std::endl;
    list.clear();
    std::cout << list.size() << std::endl;

}