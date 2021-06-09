#include "vector.hpp"
#include <vector>

int	main() {

	ft::vector<int> vec1;
	ft::vector<std::string> vec3;
	std::vector<int> vec2;
	for (int i = 0; i < 16; ++i){
		vec1.push_back(i);
		vec2.push_back(i);
	}


	ft::vector<int>::iterator it1 = vec1.begin();
	ft::vector<int>::iterator it5 = vec1.begin();
	std::vector<int>::iterator it2 = vec2.begin();
	ft::vector<int>::reverse_iterator l = vec1.rbegin();
	ft::vector<int>::const_reverse_iterator k = vec1.rbegin();

	std::vector<int>::const_iterator it4 = vec2.begin();

	ft::vector<int>::iterator it;
	ft::vector<int>::const_iterator it3 = vec1.begin();
//	it3 = it;

//	it2 = it4;
//	it3 = it;

	for(int i = 0; i < 10; ++i){
		std::cout << *it4 << "  ";
		it4++;
	}
	std::cout << std::endl;
	for(int i = 0; i < 10; ++i){
		std::cout << *it3 << "  ";
		it3++;
	}
	std::cout << std::endl;
//	it2 = it4;
//	it1 = it3;

	it4 = it2;
	it3 = it1;
//	*it4 = 0;
//	*it3 = 0;


	return 0;
}