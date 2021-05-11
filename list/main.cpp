#include "list.hpp"
#include <unistd.h>
//#include "../utils/utils.hpp"
//#include "../utils/iterators.hpp"

#include <list>

int main() {
	ft::list<int> list(5, 1234);
	ft::list<int>::iterator itr;
	list.push_back(-1);
	list.begin();
	std::cout << list.size() << std::endl;
	ft::list<int> list2(list.begin(), list.end());

	std::cout << list2.size() << std::endl;
//	ft::list<int>::iterator it = list2.begin();
//	while (it != list2.end()){
//		std::cout << *it << std::endl;
//		it++;
//	}

	ft::list<int> lis(list2);

	ft::list<int>::iterator it = lis.begin();
	while (it != lis.end()){
		std::cout << *it << std::endl;
		it++;
	}
	std::cout << lis.size() << std::endl;


	ft::list<int> kl = lis;

	kl.push_front(10);
	ft::list<int>::iterator i = kl.begin();
	while (i != kl.end()){
		std::cout << *i << std::endl;
		i++;
	}
	std::cout << kl.size() << std::endl;


	kl.assign(3, 0);

	i = kl.begin();
	while (i != kl.end()){
		std::cout << *i << std::endl;
		i++;
	}
	std::cout << kl.size() << std::endl;


	kl.assign(list2.begin(), list2.end());
	i = kl.begin();
	while (i != kl.end()){
		std::cout << *i << std::endl;
		i++;
	}

	std::cout << "START" << std::endl;
	i = kl.begin();
	kl.insert(kl.end(), -12);
	i = kl.begin();
	while (i != kl.end()){
		std::cout << *i << std::endl;
		i++;
	}
	std::cout << kl.size() << std::endl;


	std::cout << "START" << std::endl;
	kl.clear();
	kl.insert(kl.begin(), 10, -5);
	i = kl.begin();
	while (i != kl.end()){
		std::cout << *i << std::endl;
		i++;
	}
	std::cout << kl.size() << std::endl;

	ft::list<int> mr;
	for (int i = 0; i < 5; i++){
		mr.push_back(i);
	}


	std::cout << "START" << std::endl;
	kl.insert(kl.begin(), mr.begin(), mr.end());
	i = kl.begin();
	while (i != kl.end()){
		std::cout << *i << std::endl;
		i++;
	}
	std::cout << kl.size() << std::endl;



	std::cout << "START" << std::endl;
	ft::list<int> re = kl;
	i = re.begin();
	while (i != re.end()){
		std::cout << *i << std::endl;
		i++;
	}

	std::cout << "START" << std::endl;
	kl.clear();
	kl.insert(kl.end(), re.begin(), re.end());
	std::cout << "OK" << std::endl;
	i = kl.begin();
	while (i != kl.end()){
		std::cout << *i << std::endl;
		i++;
	}
	std::cout << kl.size() << std::endl;


	i = kl.erase(kl.begin());
	std::cout << *i << std::endl;

	std::cout << "START" << std::endl;
	i = kl.begin();
	while (i != kl.end()){
		std::cout << *i << std::endl;
		i++;
	}
	std::cout << kl.size() << std::endl;

	std::cout << "START" << std::endl;
	i = kl.begin();
	i++;
	i++;
	i++;
	i = kl.erase(kl.begin(), i);
	std::cout << *i << std::endl;
	i = kl.begin();
	while (i != kl.end()){
		std::cout << *i << std::endl;
		i++;
	}
	std::cout << kl.size() << std::endl;
}
