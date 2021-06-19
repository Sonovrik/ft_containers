#include "map.hpp"
#include <map>






int 	main(){
	ft::map<int, int> asd2;

	for (int i = 0; i < 5; i++)
		asd2.insert(std::make_pair(i, i * 10));

	ft::map<int, int>::iterator it = asd2.begin();

	while (it != asd2.end()){
		std::cout << (*it).second << std::endl;
		++it;
	}

	ft::map<int, int>::iterator it2 = --asd2.end();

	while (it2 != asd2.begin()){
		std::cout << (*it2).second << std::endl;
		--it2;
	}
	std::cout << (*it2).second << std::endl;
	asd2.erase(1);

	it = asd2.begin();
	while (it != asd2.end()){
		std::cout << (*it).second << std::endl;
		++it;
	}

}