#include "map.hpp"
#include <map>






int 	main(){
	ft::map<int, int> asd2;
	ft::map<int, int> asd3;

	for (int i = 0; i < 5; i++)
		asd2.insert(std::make_pair(i, i * 10));

	for (int i = 0; i < 5; i++)
		asd3.insert(std::make_pair(-i * 4, -i * 5));

	ft::map<int, int>::iterator it = asd2.begin();

	while (it != asd2.end()){
		std::cout << (*it).second << " ";
		++it;
	}
	std::cout << std::endl;

	asd2.erase(asd2.begin(), asd2.end());

	it = asd2.begin();
	while (it != asd2.end()){
		std::cout << (*it).second << " ";
		++it;
	}
	std::cout << std::endl;

	asd2.insert(asd3.begin(), asd3.end());
	it = asd2.begin();
	while (it != asd2.end()){
		std::cout << (*it).second << " ";
		++it;
	}
	std::cout << std::endl;


	ft::map<int, int>::reverse_iterator it2 = asd2.rbegin();
	while (it2 !=  asd2.rend()){
		std::cout << (*it2).second << " ";
		++it2;
	}
	std::cout << std::endl;

	ft::map<int, int> mp(asd2.begin(), asd2.end());
	it2 = mp.rbegin();
	while (it2 !=  mp.rend()){
		std::cout << (*it2).second << " ";
		++it2;
	}
	mp.clear();
	std::cout << std::endl;


}