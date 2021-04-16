#include "list.hpp"
#include <unistd.h>
int			main(){
	ft::list<int> list(10, 1234);
	list.push_back(10);
	std::cout << list.back() << std::endl;
	list.pop_back();
	std::cout << list.back() << std::endl;
	list.clear();
	std::cout << list.back() << std::endl;
	std::cout << list.size() << std::endl;
	std::cout << list.max_size() << std::endl;

	sleep(1000);
}