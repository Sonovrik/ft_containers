#include <iostream>
#include "list.hpp"
#include <list>
#include <iostream>
#include <sstream>
#include <algorithm>

#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cmath>

#define    CLR_GOOD    "\033[1;32m"
#define    CLR_ERROR    "\033[41;30m"
#define    CLR_WARN    "\033[48;5;202m\033[38;5;0m"
#define    CLR_RESET    "\033[0m"

bool single_digit(const int &value) { return (value < 10); }

struct is_near {
	bool operator()(double first, double second) { return (fabs(first - second) < 5.0); }
};

template <typename T>
bool compare(const T &x, const T &y) {
	return (x < y);
}

template <class Iterator>
void print_container(const std::string &containername, Iterator first, Iterator last) {
	std::cout << containername << " contains:";
	while (first != last) {
		std::cout << ' ' << *first;
		++first;
	}
	std::cout << std::endl;
}

void print_4(std::list<int> &b, std::list<int> &bb, ft::list<int> &a, ft::list<int> &aa) {
	std::cout << "std::list: size(b) " << b.size() << std::endl;
	std::cout << "std::list: size(bb) " << bb.size() << std::endl;
	std::cout << "ft::list: size(a) " << a.size() << std::endl;
	std::cout << "ft::list: size(aa) " << aa.size() << std::endl;
	std::cout << "------------------" << std::endl;
	std::cout << "std::list: ";
	std::list<int>::iterator beg1 = b.begin();
	for (; beg1 != b.end(); beg1++)
		std::cout << *beg1 << " ";
	std::cout << std::endl;
	std::cout << "ft::list:  ";
	ft::list<int>::iterator beg2 = a.begin();
	for (; beg2 != a.end(); beg2++)
		std::cout << *beg2 << " ";
	std::cout << std::endl;
	std::cout << "std::list: ";
	std::list<int>::iterator beg3 = bb.begin();
	for (; beg3 != bb.end(); beg3++)
		std::cout << *beg3 << " ";
	std::cout << std::endl;
	std::cout << "ft::list:  ";
	ft::list<int>::iterator beg4 = aa.begin();
	for (; beg4 != aa.end(); beg4++)
		std::cout << *beg4 << " ";
	std::cout << std::endl;

	std::cout << "------------------" << std::endl;
}

template <class Container1, class Container2>
void print_containers_params(const Container1 &sv, const Container2 &fv) {
	std::cout << "size:     " << sv.size() << " = " << fv.size() << std::endl;
}

template <class Container>
void print_container(const std::string &containername, Container &container) {
	std::cout << containername << " contains:";
	for (typename Container::iterator it = container.begin(); it != container.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;
}

void error_exception() {
	std::string msg;
	msg.append(CLR_ERROR);
	msg.append("FAIL!!!");
	msg.append(CLR_RESET);
	msg.push_back('\n');
	throw std::runtime_error(msg);
}

template <typename T>
bool check_lists(const std::list<T> &sc, const ft::list<T> &fc) {
	typename std::list<T>::const_iterator sic = sc.begin();
	typename ft::list<T>::const_iterator fic = fc.begin();

	while (sic != sc.end()) {
		if (*sic != *fic) {
			return false;
		}
		fic++;
		sic++;
	}
	if (fic != fc.end()) {
		return false;
	}
	return true;
}

template <class Container1, class Container2>
void is_equal(const Container1 &sc, const Container2 &fc) {
	if (check_lists(sc, fc))
		std::cout << CLR_GOOD << "containers are equal" << CLR_RESET << std::endl;
	else {
		std::cerr << CLR_ERROR << "containers are not equal" << CLR_RESET << std::endl;
		error_exception();
	}
}

void list_tests() {
	std::cout << CLR_WARN << "LIST TESTS <<<<<<<<<<<<<<<<<<<<<<<<<<<                              " << CLR_RESET
			  << std::endl;

	std::cout << "\nTEST 1" << std::endl;
	{
		ft::list<int> flis;
		std::list<int> slis;
		for (int i = 0; i < 10; ++i) {
			flis.push_back(i * 11);
			slis.push_back(i * 11);
		}
		print_containers_params(slis, flis);
		print_container("std: ", slis);
		print_container("ft:  ", flis);
		is_equal(slis, flis);

		for (int i = 0; i < 5; ++i) {
			flis.pop_back();
			slis.pop_back();
		}
		print_containers_params(slis, flis);
		print_container("std: ", slis);
		print_container("ft:  ", flis);
		is_equal(slis, flis);

		for (int i = 0; i < 5; ++i) {
			flis.push_front(i);
			slis.push_front(i);
		}
		print_containers_params(slis, flis);
		print_container("std: ", slis);
		print_container("ft:  ", flis);
		is_equal(slis, flis);

		for (int i = 0; i < 5; ++i) {
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
		ft::list<int> flis;
		std::list<int> slis;
		for (int i = 0; i < 10; ++i) {
			flis.push_back(i * 11);
			slis.push_back(i * 11);
		}
		ft::list<int>::const_iterator fit = flis.begin();
		ft::list<int>::iterator fit2 = flis.begin();
		std::list<int>::const_iterator sit = slis.begin();
		std::list<int>::iterator sit2 = slis.begin();


		fit = fit2;
		sit = sit2;

		if (fit != fit2)
			error_exception();

		if (sit != sit2)
			error_exception();

		if (fit2 != fit)
			error_exception();

		if (sit2 != sit)
			error_exception();

		print_containers_params(slis, flis);
		print_container("std: ", slis);
		print_container("ft:  ", flis);
		is_equal(slis, flis);

		ft::list<int>::const_iterator fit4(fit2);
		std::list<int>::const_iterator sit4(sit2);
	}
	std::cout << "\nTEST 3 Reverse iters" << std::endl;
	{
		ft::list<int> flis;
		std::list<int> slis;
		for (int i = 0; i < 10; ++i) {
			flis.push_back(i * 11);
			slis.push_back(i * 11);
		}
		ft::list<int>::const_reverse_iterator fit = flis.rbegin();
		ft::list<int>::reverse_iterator fit2 = flis.rbegin();
		std::list<int>::reverse_iterator sit2 = slis.rbegin();

		ft::list<int>::const_reverse_iterator fit3(fit2);
		std::list<int>::const_reverse_iterator sit3(sit2);


		print_containers_params(slis, flis);
		print_container("std: ", slis.rbegin(), slis.rend());
		print_container("ft:  ", flis.rbegin(), flis.rend());
		is_equal(slis, flis);
	}
	std::cout << "\nTEST 4 insert" << std::endl;
	{
		ft::list<int> flis;
		std::list<int> slis;
		for (int i = 0; i < 10; ++i) {
			flis.push_back(i);
			slis.push_back(i);
		}

		for (int i = 0; i < 3; ++i) {
			flis.insert(flis.end(), -2);
			slis.insert(slis.end(), -2);
		}

		flis.insert(++flis.begin(), 3, 10);
		slis.insert(++slis.begin(), 3, 10);
		print_containers_params(slis, flis);
		print_container("ft:  ", flis);
		print_container("std: ", slis);
		is_equal(slis, flis);

		ft::list<int> flis2;
		std::list<int> slis2;
		for (int i = 0; i < 10; ++i) {
			flis2.push_back(-i);
			slis2.push_back(-i);
		}
		std::cout << *flis2.begin() << " " << *slis2.begin() << std::endl;
		flis.insert(flis.begin(), flis2.begin(), flis2.end());
		slis.insert(slis.begin(), slis2.begin(), slis2.end());

		print_containers_params(slis, flis);
		print_container("ft:  ", flis);
		print_container("std: ", slis);
		is_equal(slis, flis);

		slis.clear();
		flis.clear();
		flis.insert(flis.begin(), flis2.begin(), flis2.end());
		slis.insert(slis.begin(), slis2.begin(), slis2.end());

		print_containers_params(slis, flis);
		print_container("ft:  ", flis);
		print_container("std: ", slis);
		is_equal(slis, flis);
	}
	std::cout << "\nTEST 5 erase" << std::endl;
	{
		ft::list<int> flis;
		std::list<int> slis;
		for (int i = 0; i < 10; ++i) {
			flis.push_back(i);
			slis.push_back(i);
		}

		std::cout << *flis.erase(flis.begin()) << std::endl;
		std::cout << *slis.erase(slis.begin()) << std::endl;

		flis.erase(++flis.begin());
		slis.erase(++slis.begin());

		flis.erase(--flis.end());
		slis.erase(--slis.end());

		print_containers_params(slis, flis);
		print_container("ft:  ", flis);
		print_container("std: ", slis);
		is_equal(slis, flis);

		ft::list<std::string> flis2;
		std::list<std::string> slis2;
		for (int i = 0; i < 10; ++i) {
			slis2.push_back("hello" + std::to_string(i));
			flis2.push_back("hello" + std::to_string(i));
		}

		ft::list<std::string>::iterator fit = flis2.begin();
		std::list<std::string>::iterator sit = slis2.begin();

		for (int i = 0; i < 4; ++i) {
			++fit;
			++sit;
		}

		slis2.erase(sit, slis2.end());
		flis2.erase(fit, flis2.end());

		print_containers_params(slis2, flis2);
		print_container("ft:  ", flis2);
		print_container("std: ", slis2);
		is_equal(slis2, flis2);

		std::list<std::string> as;
		ft::list<std::string> af;
		slis2.swap(as);
		flis2.swap(af);

		print_containers_params(slis2, flis2);
		print_container("ft:  ", flis2);
		print_container("std: ", slis2);
		is_equal(slis2, flis2);

	}
	std::cout << "\nTEST 6 resize" << std::endl;
	{
		ft::list<int> flis;
		std::list<int> slis;
		for (int i = 0; i < 10; ++i) {
			flis.push_back(i);
			slis.push_back(i);
		}

		flis.resize(1, -1);
		slis.resize(1, -1);

		print_containers_params(slis, flis);
		print_container("ft:  ", flis);
		print_container("std: ", slis);
		is_equal(slis, flis);

		flis.clear();
		slis.clear();

		flis.resize(1, -1);
		slis.resize(1, -1);

		print_containers_params(slis, flis);
		print_container("ft:  ", flis);
		print_container("std: ", slis);
		is_equal(slis, flis);

		flis.resize(11, 10);
		slis.resize(11, 10);

		print_containers_params(slis, flis);
		print_container("ft:  ", flis);
		print_container("std: ", slis);
		is_equal(slis, flis);
	}
	std::cout << "\nTEST 7 remove" << std::endl;
	{
		ft::list<int> flis;
		std::list<int> slis;
		for (int i = 0; i < 3; ++i) {
			flis.push_back(i);
			slis.push_back(i);
		}

		for (int i = 0; i < 3; ++i) {
			flis.push_back(i * 2);
			slis.push_back(i * 2);
		}

		for (int i = 0; i < 3; ++i) {
			flis.push_back(i);
			slis.push_back(i);
		}

		for (int i = 0; i < 3; ++i) {
			flis.push_back(i * 2);
			slis.push_back(i * 2);
		}

		flis.remove(0);
		slis.remove(0);

		flis.remove(2);
		slis.remove(2);

		flis.remove(3);
		slis.remove(3);

		print_containers_params(slis, flis);
		print_container("ft:  ", flis);
		print_container("std: ", slis);
		is_equal(slis, flis);

		flis.remove_if(single_digit);
		slis.remove_if(single_digit);

		flis.remove(0);
		slis.remove(0);

		print_containers_params(slis, flis);
		print_container("ft:  ", flis);
		print_container("std: ", slis);
		is_equal(slis, flis);
	}
	std::cout << "\nTEST 8 unique" << std::endl;
	{
		ft::list<int> flis;
		std::list<int> slis;
		for (int i = 0; i < 5; ++i) {
			flis.push_back(1);
			flis.push_back(2);
			slis.push_back(1);
			slis.push_back(2);
		}
		print_containers_params(slis, flis);
		print_container("ft:  ", flis);
		print_container("std: ", slis);

		flis.unique();
		slis.unique();

		for (int i = 0; i < 5; ++i) {
			flis.push_back(1);
			slis.push_back(1);
		}
		flis.unique();
		slis.unique();
		print_containers_params(slis, flis);
		print_container("ft:  ", flis);
		print_container("std: ", slis);
		is_equal(slis, flis);

		for (int i = 0; i < 5; ++i) {
			flis.push_back(66);
			slis.push_back(66);
		}
		print_containers_params(slis, flis);
		print_container("ft:  ", flis);
		print_container("std: ", slis);
		flis.unique();
		slis.unique();
		print_containers_params(slis, flis);
		print_container("ft:  ", flis);
		print_container("std: ", slis);
		is_equal(slis, flis);

		for (int i = 0; i < 5; ++i) {
			flis.push_front(77);
			slis.push_front(77);
		}
		print_containers_params(slis, flis);
		print_container("ft:  ", flis);
		print_container("std: ", slis);
		flis.unique(is_near());
		slis.unique(is_near());
		print_containers_params(slis, flis);
		print_container("ft:  ", flis);
		print_container("std: ", slis);
		is_equal(slis, flis);
	}
	std::cout << "\nTEST 9 reverse" << std::endl;
	{
		ft::list<int> flis;
		std::list<int> slis;

		flis.reverse();
		slis.reverse();
		print_containers_params(slis, flis);
		print_container("ft:  ", flis);
		print_container("std: ", slis);
		is_equal(slis, flis);

		for (int i = 0; i < 10; ++i) {
			flis.push_back(i);
			slis.push_back(i);
		}
		print_containers_params(slis, flis);
		print_container("ft:  ", flis);
		print_container("std: ", slis);

		flis.reverse();
		slis.reverse();
		print_containers_params(slis, flis);
		print_container("ft:  ", flis);
		print_container("std: ", slis);
		is_equal(slis, flis);
	}
	std::cout << "\nTEST 10 splice" << std::endl;
	{
		ft::list<int> flis;
		std::list<int> slis;
		std::list<int> sli2;
		ft::list<int> fli2;
		for (int i = 0; i < 10; ++i) {
			flis.push_back(i);
			sli2.push_back(-i);
			fli2.push_back(-i);
			slis.push_back(i);
		}

		slis.splice(slis.end(), sli2);
		flis.splice(flis.end(), fli2);
		print_container("std: ", slis);
		print_container("ft:  ", flis);
		print_containers_params(slis, flis);
		is_equal(slis, flis);

		flis.clear();
		slis.clear();
		for (int i = 0; i < 10; ++i) {
			sli2.push_back(-i);
			fli2.push_back(-i);
		}

		flis.splice(flis.begin(), fli2);
		slis.splice(slis.begin(), sli2);

		print_container("std: ", slis);
		print_container("ft:  ", flis);
		print_containers_params(slis, flis);
		is_equal(slis, flis);

		for (int i = 0; i < 10; ++i) {
			sli2.push_back(i * 20);
			fli2.push_back(i * 20);
		}

		flis.splice(flis.begin(), fli2, --fli2.end());
		slis.splice(slis.begin(), sli2, --sli2.end());
		print_container("std: ", slis);
		print_container("ft:  ", flis);
		print_containers_params(slis, flis);
		is_equal(slis, flis);

		flis.clear();
		slis.clear();
		for (int i = 0; i < 10; ++i) {
			sli2.push_back(i * 20);
			fli2.push_back(i * 20);
		}

		std::list<int>::iterator sit = sli2.begin();
		ft::list<int>::iterator fit = fli2.begin();
		for (int i = 0; i < 4; ++i) {
			sit++;
			fit++;
		}
		flis.splice(flis.begin(), fli2, fli2.begin(), fit);
		slis.splice(slis.begin(), sli2, sli2.begin(), sit);
		print_container("std: ", slis);
		print_container("ft:  ", flis);
		print_containers_params(slis, flis);
		is_equal(slis, flis);
	}
	std::cout << "\nTEST 11 splice" << std::endl;
	{
		ft::list<int> a;
		ft::list<int> aa;
		std::list<int> b;
		std::list<int> bb;

		aa.push_back(99);
		aa.push_back(87);
		aa.push_back(1015);
		aa.push_back(9999);
		aa.push_back(1);

		bb.push_back(99);
		bb.push_back(87);
		bb.push_back(1015);
		bb.push_back(9999);
		bb.push_back(1);

		a.push_back(1000);
		a.push_back(1500);
		a.push_back(2000);
		a.push_back(2500);
		a.push_back(3000);

		b.push_back(1000);
		b.push_back(1500);
		b.push_back(2000);
		b.push_back(2500);
		b.push_back(3000);


		std::cout << "До вызова: " << std::endl;

		std::cout << "std::list: size(b) " << b.size() << std::endl;
		std::cout << "std::list: size(bb) " << bb.size() << std::endl;
		std::cout << "ft::list: size(a) " << a.size() << std::endl;
		std::cout << "ft::list: size(aa) " << aa.size() << std::endl;

		std::cout << "------------------" << std::endl;
		std::cout << "std::list: ";
		std::list<int>::iterator beg1 = b.begin();
		for (; beg1 != b.end(); beg1++)
			std::cout << *beg1 << " ";
		std::cout << std::endl;
		std::cout << "ft::list:  ";
		ft::list<int>::iterator beg2 = a.begin();
		for (; beg2 != a.end(); beg2++)
			std::cout << *beg2 << " ";
		std::cout << std::endl;
		std::cout << "std::list: ";
		std::list<int>::iterator beg3 = bb.begin();
		for (; beg3 != bb.end(); beg3++)
			std::cout << *beg3 << " ";
		std::cout << std::endl;
		std::cout << "ft::list:  ";
		ft::list<int>::iterator beg4 = aa.begin();
		for (; beg4 != aa.end(); beg4++)
			std::cout << *beg4 << " ";
		std::cout << std::endl;

		std::cout << "------------------" << std::endl;

		beg1++;
		beg1++;
		beg2++;
		beg2++;

		b.splice(beg1, bb);
		a.splice(beg2, aa);

		std::cout << "После вызова: " << std::endl;
		print_4(b, bb, a, aa);
	}
	{
		ft::list<int> a;
		ft::list<int> aa;
		std::list<int> b;
		std::list<int> bb;

		aa.push_back(99);
		aa.push_back(87);
		aa.push_back(1015);
		aa.push_back(9999);
		aa.push_back(1);

		bb.push_back(99);
		bb.push_back(87);
		bb.push_back(1015);
		bb.push_back(9999);
		bb.push_back(1);

		a.push_back(1000);
		a.push_back(1500);
		a.push_back(2000);
		a.push_back(2500);
		a.push_back(3000);

		b.push_back(1000);
		b.push_back(1500);
		b.push_back(2000);
		b.push_back(2500);
		b.push_back(3000);


		std::cout << "До вызова: " << std::endl;

		std::cout << "std::list: size(b) " << b.size() << std::endl;
		std::cout << "std::list: size(bb) " << bb.size() << std::endl;
		std::cout << "ft::list: size(a) " << a.size() << std::endl;
		std::cout << "ft::list: size(aa) " << aa.size() << std::endl;

		std::cout << "------------------" << std::endl;
		std::cout << "std::list: ";
		std::list<int>::iterator beg1 = b.begin();
		for (; beg1 != b.end(); beg1++)
			std::cout << *beg1 << " ";
		std::cout << std::endl;
		std::cout << "ft::list:  ";
		ft::list<int>::iterator beg2 = a.begin();
		for (; beg2 != a.end(); beg2++)
			std::cout << *beg2 << " ";
		std::cout << std::endl;
		std::cout << "std::list: ";
		std::list<int>::iterator beg3 = bb.begin();
		for (; beg3 != bb.end(); beg3++)
			std::cout << *beg3 << " ";
		std::cout << std::endl;
		std::cout << "ft::list:  ";
		ft::list<int>::iterator beg4 = aa.begin();
		for (; beg4 != aa.end(); beg4++)
			std::cout << *beg4 << " ";
		std::cout << std::endl;

		std::cout << "------------------" << std::endl;

		beg1++;
		beg2++;
		beg3++;
		beg4++;

		b.splice(beg1, bb, beg3);
		a.splice(beg2, aa, beg4);

		std::cout << "После вызова: " << std::endl;
		print_4(b, bb, a, aa);
	}
	std::cout << "\nTEST 12 merge" << std::endl;
	{
		ft::list<int> flis;
		std::list<int> slis;
		ft::list<int> flis2;
		std::list<int> slis2;

		for (int i = 0; i < 10; ++i) {
			flis.push_back(i);
			slis.push_back(i);
			flis2.push_back(i * 10);
			slis2.push_back(i * 10);
		}
		flis.merge(flis2);
		slis.merge(slis2);
		print_container("std: ", slis);
		print_container("ft:  ", flis);
		print_containers_params(slis, flis);
		is_equal(slis, flis);

	}
	std::cout << "\nTEST 13 sort" << std::endl;
	{
		ft::list<int> flis;
		std::list<int> slis;
		for (int i = 0; i < 10; ++i) {
			flis.push_back(-i);
			slis.push_back(-i);
		}

		slis.sort();
		flis.sort();
		print_container("std: ", slis);
		print_container("ft:  ", flis);
		print_containers_params(slis, flis);
		is_equal(slis, flis);

	}
	{
		ft::list<int> a;
		ft::list<int> aa;
		std::list<int> b;
		std::list<int> bb;

		a.push_back(1);
		a.push_back(1);
		a.push_back(2);
		a.push_back(3);
		a.push_back(4);

		aa.push_back(1);
		aa.push_back(2);
		aa.push_back(3);
		aa.push_back(4);
		aa.push_back(5);

		b.push_back(1);
		b.push_back(1);
		b.push_back(2);
		b.push_back(3);
		b.push_back(4);

		bb.push_back(1);
		bb.push_back(2);
		bb.push_back(3);
		bb.push_back(4);
		bb.push_back(5);

		std::cout << "До вызова: " << std::endl;

		print_4(b, bb, a, aa);

		a.merge(aa);
		b.merge(bb);

		std::cout << "После вызова: " << std::endl;
		print_4(b, bb, a, aa);
	}
	{

		ft::list<int> a;
		ft::list<int> aa;
		std::list<int> b;
		std::list<int> bb;

		a.push_back(10);
		a.push_back(100);
		a.push_back(22);
		a.push_back(3);
		a.push_back(48);

		aa.push_back(99);
		aa.push_back(87);
		aa.push_back(1015);
		aa.push_back(9999);
		aa.push_back(1);

		b.push_back(10);
		b.push_back(100);
		b.push_back(22);
		b.push_back(3);
		b.push_back(48);

		bb.push_back(99);
		bb.push_back(87);
		bb.push_back(1015);
		bb.push_back(9999);
		bb.push_back(1);

		a.sort();
		aa.sort();
		b.sort();
		bb.sort();

		std::cout << "До вызова: " << std::endl;

		print_4(b, bb, a, aa);

		a.merge(aa, compare<int>);
		b.merge(bb, compare<int>);

		std::cout << "После вызова: " << std::endl;
		print_4(b, bb, a, aa);
	}
	std::cout << "\nTEST 14 operations" << std::endl;
	{
		ft::list<int> a;
		ft::list<int> aa;
		std::list<int> b;
		std::list<int> bb;

		print_4(b, bb, a, aa);

		std::cout << "------------------" << std::endl;
		std::cout << "ft::list  == " << (a == aa) << std::endl;
		std::cout << "std::list == " << (b == bb) << std::endl;
		std::cout << "ft::list  != " << (a != aa) << std::endl;
		std::cout << "std::list != " << (b != bb) << std::endl;
		std::cout << "ft::list  <  " << (a < aa) << std::endl;
		std::cout << "std::list <  " << (b < bb) << std::endl;
		std::cout << "ft::list  <= " << (a <= aa) << std::endl;
		std::cout << "std::list <= " << (b <= bb) << std::endl;
		std::cout << "ft::list  >  " << (a > aa) << std::endl;
		std::cout << "std::list >  " << (b > bb) << std::endl;
		std::cout << "ft::list  >= " << (a >= aa) << std::endl;
		std::cout << "std::list >= " << (b >= bb) << std::endl;
		std::cout << "------------------" << std::endl;

		a.push_back(10);
		a.push_back(10);

		b.push_back(10);
		b.push_back(10);

		aa.push_back(10);
		aa.push_back(10);

		bb.push_back(10);
		bb.push_back(10);

		print_4(b, bb, a, aa);

		std::cout << "------------------" << std::endl;
		std::cout << "ft::list  == " << (a == aa) << std::endl;
		std::cout << "std::list == " << (b == bb) << std::endl;
		std::cout << "ft::list  != " << (a != aa) << std::endl;
		std::cout << "std::list != " << (b != bb) << std::endl;
		std::cout << "ft::list  <  " << (a < aa) << std::endl;
		std::cout << "std::list <  " << (b < bb) << std::endl;
		std::cout << "ft::list  <= " << (a <= aa) << std::endl;
		std::cout << "std::list <= " << (b <= bb) << std::endl;
		std::cout << "ft::list  >  " << (a > aa) << std::endl;
		std::cout << "std::list >  " << (b > bb) << std::endl;
		std::cout << "ft::list  >= " << (a >= aa) << std::endl;
		std::cout << "std::list >= " << (b >= bb) << std::endl;
		std::cout << "------------------" << std::endl;

		a.clear();
		b.clear();
		aa.clear();
		bb.clear();
		a.push_back(10);
		a.push_back(10);
		a.push_back(10);

		b.push_back(10);
		b.push_back(10);
		b.push_back(10);

		aa.push_back(10);
		aa.push_back(10);

		bb.push_back(10);
		bb.push_back(10);

		print_4(b, bb, a, aa);

		std::cout << "------------------" << std::endl;
		std::cout << "ft::list  == " << (a == aa) << std::endl;
		std::cout << "std::list == " << (b == bb) << std::endl;
		std::cout << "ft::list  != " << (a != aa) << std::endl;
		std::cout << "std::list != " << (b != bb) << std::endl;
		std::cout << "ft::list  <  " << (a < aa) << std::endl;
		std::cout << "std::list <  " << (b < bb) << std::endl;
		std::cout << "ft::list  <= " << (a <= aa) << std::endl;
		std::cout << "std::list <= " << (b <= bb) << std::endl;
		std::cout << "ft::list  >  " << (a > aa) << std::endl;
		std::cout << "std::list >  " << (b > bb) << std::endl;
		std::cout << "ft::list  >= " << (a >= aa) << std::endl;
		std::cout << "std::list >= " << (b >= bb) << std::endl;
		std::cout << "------------------" << std::endl;
	}
	std::cout << CLR_WARN << "LIST TESTS DONE <<<<<<<<<<<<<<<<<<<<<<<<<<<                              " << CLR_RESET
			  << std::endl;
}


int main() {

	list_tests();
	return 0;

}