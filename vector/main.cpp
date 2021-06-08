#include "vector.hpp"
#include <vector>

int	main(){
		ft::vector<int> asd;
		asd.push_back(2);
		ft::vector<int> asd2;
		asd2.push_back(2);
		for (int i = 0; i < 10; ++i)
			asd2.push_back(i);

		ft::vector<int>::reverse_iterator it = asd2.rbegin();

//		for (int i = 0; i < 11; i++){
//			std::cout << *it << std::endl;
//			it++;
//		}
		ft::vector<int>::reverse_iterator it2 = asd2.rbegin();

		if (it == it2)
			std::cout << "asd" << std::endl;



}