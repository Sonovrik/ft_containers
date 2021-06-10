#include "vector.hpp"
#include <vector>

int	main() {

	ft::vector<int> vec1;
	std::vector<int> vec2;

	for (int i = 0; i < 10; i++){
		vec1.push_back(i);
		vec2.push_back(i);
	}

	ft::vector<int>::iterator it1 = vec1.begin();
	std::vector<int>::iterator it2 = vec2.begin();


	ft::vector<int>::const_iterator it3 = vec1.begin();
	std::vector<int>::const_iterator it4 = vec2.begin();

	ft::vector<int>::reverse_iterator it5 = vec1.rbegin();
	std::vector<int>::reverse_iterator it6 = vec2.rbegin();


	ft::vector<int>::const_reverse_iterator it7 = vec1.rbegin();
	std::vector<int>::const_reverse_iterator it8 = vec2.rbegin();


	it7 = it5;

	for (; it7 != vec1.rend(); ++it7){
		std::cout << *it7 << "  ";
	}
	std::cout << std::endl;

	for (; it8 < vec2.rend(); ++it8){
		std::cout << *it8 << "  ";
	}
	std::cout << std::endl;

	return 0;
}