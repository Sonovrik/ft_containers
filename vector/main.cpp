#include "vector.hpp"
#include <vector>

int	main(){
		ft::vector<int> first;
		first.reserve(100);


		for (int i = 0; i < 10; i++)
			first.push_back(i);

		for (int i = 0; i < first.size(); i++)
			std::cout << first[i] << "  ";

		std::vector<int> a;
		for (int i = 0; i < 10; i++)
			a.push_back(i);
		std::vector<int>::reverse_iterator j = a.rbegin();
		for (; j != a.rend(); j++){
			std::cout << "asd" << std::endl;
		}
//		ft::vector<int>::reverse_iterator it = first.rbegin();
//
//		for (; it != first.rend(); it++)
//			std::cout << *it << std::endl;
//		std::cout << std::endl;
//		std::cout << it[3] << std::endl;
//		for (int i = 0; i < first.size(); i++)
//			std::cout << first[i] << "  ";

}