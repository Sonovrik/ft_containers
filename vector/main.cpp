#include "vector.hpp"
#include <vector>

int	main() {

	ft::vector<int> vec1;
	std::vector<int> vec2;

	for (int i = 0; i < 10; i++){
		vec1.push_back(i * 23);
		vec2.push_back(i * 23);
	}

	std::cout << vec1.capacity() << vec1.size() << std::endl;

	ft::vector<int>::const_reverse_iterator it7 = vec1.rbegin();


	vec1.insert(vec1.begin(), 10, 0);
	it7 = vec1.rbegin();


	for (; it7 != vec1.rend(); ++it7) {
		std::cout << *it7 << "  ";
	}
	std::cout << std::endl;

//	for (; it8 < vec2.rend(); ++it8){
//		std::cout << *it8 << "  ";
//	}
	std::cout << std::endl;

	return 0;
}