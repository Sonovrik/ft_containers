#include <iostream>
#include "list.hpp"
#include <list>
#include <iostream>
#include <sstream>
#include <algorithm>

#include <cstdlib>
#include <ctime>
#include <iomanip>

#define	CLR_GOOD	"\033[1;32m"
#define	CLR_ERROR	"\033[41;30m"
#define	CLR_WARN	"\033[48;5;202m\033[38;5;0m"
#define	CLR_RESET	"\033[0m"

template <class Iterator>
void		print_container(const std::string& containername, Iterator first, Iterator last) {
	std::cout << containername << " contains:";
	while (first != last){
		std::cout << ' ' << *first;
		++first;
	}
	std::cout << std::endl;
}

template <class Container1, class Container2>
void		print_containers_params(const Container1& sv, const Container2& fv) {
	std::cout << "size:     " << sv.size() << " = " << fv.size() << std::endl;
}

template <class Container>
void		print_container(const std::string& containername, Container& container) {
	std::cout << containername << " contains:";
	for (typename Container::iterator it = container.begin(); it != container.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;
}

void		error_exception() {
	std::string	msg;
	msg.append(CLR_ERROR);
	msg.append("FAIL!!!");
	msg.append(CLR_RESET);
	msg.push_back('\n');
	throw std::runtime_error(msg);
}

template <class Container1, class Container2>
void		is_equal(const Container1& sc, const Container2& fc, size_t i = 0)
{
	if (sc.size() == fc.size() && std::equal(sc.begin(), sc.end(), fc.begin()) &&
		std::equal(fc.begin(), fc.end(), sc.begin())) {
		std::cout << CLR_GOOD << "containers are equal" << CLR_RESET << std::endl;
	}
	else {
		std::cerr << CLR_ERROR << "containers are not equal" << CLR_RESET << std::endl;
		error_exception();
	}
}
void	list_tests(){
	std::cout << CLR_WARN << "LIST TESTS <<<<<<<<<<<<<<<<<<<<<<<<<<<                              " << CLR_RESET << std::endl;

	std::cout << "\nTEST 1" << std::endl;
	{
		ft::list<int> flis;
		std::list<int> slis;
		for (int i = 0; i < 10; ++i){
			flis.push_back(i * 11);
			slis.push_back(i * 11);
		}
		print_containers_params(slis, flis);
		print_container("std: ", slis);
		print_container("ft:  ", flis);
		is_equal(slis, flis);

		for (int i = 0; i < 5; ++i){
			flis.pop_back();
			slis.pop_back();
		}
		print_containers_params(slis, flis);
		print_container("std: ", slis);
		print_container("ft:  ", flis);
		is_equal(slis, flis);

		for (int i = 0; i < 5; ++i){
			flis.push_front(i);
			slis.push_front(i);
		}
		print_containers_params(slis, flis);
		print_container("std: ", slis);
		print_container("ft:  ", flis);
		is_equal(slis, flis);

		for (int i = 0; i < 5; ++i){
			flis.pop_front();
			slis.pop_front();
		}
		print_containers_params(slis, flis);
		print_container("std: ", slis);
		print_container("ft:  ", flis);
		is_equal(slis, flis);

		flis.clear();
		slis.clear();
		print_containers_params(slis, flis);
		print_container("std: ", slis);
		print_container("ft:  ", flis);
		is_equal(slis, flis);
	}
	std::cout << "\nTEST 2" << std::endl;
	{

	}


}


int 	main(){

	list_tests();

}