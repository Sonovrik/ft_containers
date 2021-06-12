#include "vector.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

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
	std::cout << "capacity: " << sv.capacity() << " = " << fv.capacity() << std::endl;
}

template <class Container>
void		print_container(const std::string& containername, const Container& container) {
	std::cout << containername << " contains:";
	for (typename Container::const_iterator it = container.begin(); it != container.end(); ++it)
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

void 		vector_tests(){
	std::cout << CLR_WARN << "VECTOR TESTS <<<<<<<<<<<<<<<<<<<<<<<<<<<                              " << CLR_RESET << std::endl;

	std::cout << "\nTEST 1" << std::endl;
	{
		std::vector<int> sv;
		ft::vector<int> fv;
		print_containers_params(sv, fv);
	}
	std::cout << "\nTEST 2" << std::endl;
	{
		std::vector<std::string> sv;
		ft::vector<std::string> fv;
		print_containers_params(sv, fv);
	}
	std::cout << "\nTEST 3" << std::endl;
	{
		std::vector<std::vector<std::string> > sv;
		ft::vector<std::vector<std::string> > fv;
		print_containers_params(sv, fv);
	}
	std::cout << "\nTEST 4" << std::endl;
	{
		std::vector<int> sv(6, 100);
		ft::vector<int > fv(6, 100);
		print_containers_params(sv, fv);
		is_equal(sv, fv);
	}
	std::cout << "\nTEST 5" << std::endl;
	{
		try{		std::vector<int> sv(sv.max_size() + 1, 100); } catch(std::exception &e) {std::cerr << e.what() << std::endl;}
		try{		ft::vector<int> fv(fv.max_size() + 1, 100); } catch(std::exception &e) {std::cerr << e.what() << std::endl;}
	}
	std::cout << "\nTEST 6" << std::endl;
	{
		std::vector<int> sv1(6, 100);
		ft::vector<int > fv1(6, 100);
		print_containers_params(sv1, fv1);
		is_equal(sv1, fv1);

		std::vector<int> sv2(sv1);
		ft::vector<int > fv2(fv1);
		print_containers_params(sv2, fv2);
		print_container("std ", sv2);
		print_container("ft  ", fv2);
		is_equal(sv2, fv2);
	}
	std::cout << "\nTEST 7" << std::endl;
	{
		std::vector<int> sv1(6, 100);
		ft::vector<int > fv1(6, 100);

		sv1.clear();
		fv1.clear();

		is_equal(sv1, fv1);

		for (int i = 0; i < 10; i++){
			sv1.push_back(i * 10);
			fv1.push_back(i * 10);
		}

		print_containers_params(sv1, fv1);
		print_container("std ", sv1);
		print_container("ft  ", fv1);
		is_equal(sv1, fv1);

		sv1.erase(sv1.begin());
		fv1.erase(fv1.begin());
		print_containers_params(sv1, fv1);
		print_container("std ", sv1);
		print_container("ft  ", fv1);
		is_equal(sv1, fv1);

		sv1.erase(sv1.end() - 1);
		fv1.erase(fv1.end() - 1);
		print_containers_params(sv1, fv1);
		print_container("std ", sv1);
		print_container("ft  ", fv1);
		is_equal(sv1, fv1);

		sv1.erase(sv1.end() - 1);
		fv1.erase(fv1.end() - 1);
		print_containers_params(sv1, fv1);
		print_container("std ", sv1);
		print_container("ft  ", fv1);
		is_equal(sv1, fv1);

		sv1.clear();
		fv1.clear();
		print_containers_params(sv1, fv1);
		print_container("std ", sv1);
		print_container("ft  ", fv1);
		is_equal(sv1, fv1);
	}
	std::cout << "\nTEST 8" << std::endl;
	{
		std::vector<int> sv1(8, 2);
		ft::vector<int > fv1(8, 2);

		print_containers_params(sv1, fv1);
		print_container("std ", sv1);
		print_container("ft  ", fv1);
		is_equal(sv1, fv1);

		std::vector<int> sv2(13, 10);
		ft::vector<int > fv2(13, 10);

		sv1 = sv2;
		fv1 = fv2;
		print_containers_params(sv1, fv1);
		print_container("std ", sv1);
		print_container("ft  ", fv1);
		is_equal(sv1, fv1);

		sv1.reserve(1000);
		fv1.reserve(1000);
		print_containers_params(sv1, fv1);


		sv1.resize(100, 6);
		fv1.resize(100, 6);
		sv1.resize(30, 6);
		fv1.resize(30, 6);
		print_containers_params(sv1, fv1);
		is_equal(sv1, fv1);

		sv1.assign(10, 3);
		fv1.assign(10, 3);
		print_containers_params(sv1, fv1);
		is_equal(sv1, fv1);

		std::vector<int> sv3;
		ft::vector<int> fv3;

		sv3.swap(sv1);
		fv3.swap(fv1);
		is_equal(sv3, fv3);
	}
	std::cout << "\nTEST 9 operators" << std::endl;
	{
		std::vector<int> sv1(6, 100);
		std::vector<int > sv2(10, 40);
		ft::vector<int > fv1(6, 100);
		ft::vector<int > fv2(10, 40);

		if (sv1 < sv2)
			error_exception();

		if (fv1 < fv2)
			error_exception();

		if (sv1 == sv2)
			error_exception();

		if (fv1 == fv2)
			error_exception();

		if (!(sv1 != sv2))
			error_exception();

		if (!(fv1 != fv2))
			error_exception();

		if (!(sv1 > sv2))
			error_exception();

		if (!(fv1 > fv2))
			error_exception();

		if (!(sv1 >= sv2))
			error_exception();

		if (!(fv1 >= fv2))
			error_exception();

		if (sv1 <= sv2)
			error_exception();

		if (fv1 <= fv2)
			error_exception();

		std::cout << "operators done" << std::endl;
	}
	std::cout << "\nTEST 10 insert" << std::endl;
	{
		std::vector<std::string> sv1;
		std::vector<std::string> sv2;
		ft::vector<std::string> fv1;
		ft::vector<std::string> fv2;

		std::vector<std::string>::const_iterator sit = sv1.begin();
		ft::vector<std::string>::const_iterator fit = fv1.begin();
		sv1.insert(sit, "hello");
		fv1.insert(	fit, "hello");

		for (int i = 0; i < 4; i++){
			sv1.insert(sv1.begin(), "hello" + std::to_string(i));
			fv1.insert(fv1.begin(), "hello" + std::to_string(i));
		}

		print_containers_params(sv1, fv1);
		print_container("std ", sv1);
		print_container("ft  ", fv1);
		is_equal(sv1, fv1);
	}
	std::cout << "\nTEST 11 iterators" << std::endl;
	{
		std::vector<int> sv1(6, 100);
		std::vector<int> sv2(10, 40);
		ft::vector<int> fv1(6, 100);
		ft::vector<int> fv2(10, 40);


		std::vector<int>::iterator sit = sv1.begin();
		ft::vector<int>::iterator fit = fv1.begin();


		std::vector<int>::const_iterator csit = sv1.begin();
		ft::vector<int>::const_iterator cfit = fv1.begin();

		csit = sit;
		cfit = fit;

		while (fit != fv1.end()){
			++fit;
		}

		while (sit != sv1.end()){
			++sit;
		}

		while (cfit != fv1.end()){
			++cfit;
		}

		while (csit != sv1.end()){
			++csit;
		}

		sit = sv1.begin();
		fit = fv1.begin();

		if (fit[3] != sit[3])
			error_exception();

		if (*fit != *sit)
			error_exception();

		std::vector<int>::iterator it3;
		ft::vector<int>::iterator it4;

		it3 = sv1.end();
		it4 = fv1.end();

		if (it3 != sv1.end())
			error_exception();

		if (it4 != fv1.end())
			error_exception();


		std::cout << it3.base() << std::endl;
		std::cout << it4.base() << std::endl;

		print_container("std ", sv1);
		print_container("ft  ", fv1);

		for (size_t i = 0; i < sv1.size(); i++){
			sv1.at(i) = 123;
		}

		for (size_t i = 0; i < fv1.size(); i++){
			fv1.at(i) = 123;
		}

		print_container("std ", sv1);
		print_container("ft  ", fv1);
		is_equal(sv1, fv1);

	}
	std::cout << "\nTEST 12 reverse iterators" << std::endl;
	{
		std::vector<int> sv1;
		std::vector<int> sv2;
		ft::vector<int> fv1;
		ft::vector<int> fv2;


		for (int i = 0; i < 10; i++){
			sv1.push_back(i);
			fv1.push_back(i);
			sv2.push_back(i);
			fv2.push_back(i);
		}

		ft::vector<int>::reverse_iterator fit = fv1.rbegin();
		std::vector<int>::reverse_iterator sit = sv1.rbegin();

		ft::vector<int>::const_reverse_iterator cfit = fit;
		std::vector<int>::const_reverse_iterator csit = sit;

		std::cout << "reverse fv:  ";
		for (; cfit != fv1.rend(); cfit++){
			std::cout << ' ' << *cfit;
		}
		std::cout << std::endl;

		std::cout << "reverse std:  ";
		for (; csit != sv1.rend(); csit++){
			std::cout << ' ' << *csit;
		}
		std::cout << std::endl;
		is_equal(sv1, fv1);
	}

	std::cout << CLR_WARN << "VECTOR TESTS DONE <<<<<<<<<<<<<<<<<<<<<<<<<<<                              " << CLR_RESET << std::endl;
}

int	main() {
	ft::vector<std::string>		ass;
	ft::vector<std::string>		as(ass);
	ft::vector<std::string>::reverse_iterator it1 = as.rbegin();
	ft::vector<std::string>::const_reverse_iterator it2 = ass.rbegin();


	vector_tests();



	return 0;
}