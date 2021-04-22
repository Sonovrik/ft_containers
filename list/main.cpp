#include "list.hpp"
#include <unistd.h>
//#include "../utils/utils.hpp"
//#include "../utils/iterators.hpp"
#include <list>

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

//    std::string::iterator it()
	ft::list<int>::iterator it;
	ft::list<int>::iterator it2(it);

	ft::list<char>::iterator it3;
	if (it == it3){
		std::cout << "Hello" << std::endl;
	}
	//    ft::ListIterator<int> asd(ft::ListIterator<std::string>);
}