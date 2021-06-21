#include "map.hpp"
#include <map>

#include <iostream>
#include <sstream>
#include <algorithm>

#include <cstdlib>
#include <ctime>
#include <iomanip>

#define    CLR_GOOD    "\033[1;32m"
#define    CLR_ERROR    "\033[41;30m"
#define    CLR_WARN    "\033[48;5;202m\033[38;5;0m"
#define    CLR_RESET    "\033[0m"

template <class Iterator>
void print_container(const std::string &containername, Iterator first, Iterator last) {
	std::cout << containername << " contains:";
	while (first != last) {
		std::cout << ' ' << first->first << ": " << first->second;
		++first;
	}
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

template <class Container1, class Container2>
void print_containers_params(const Container1 &sv, const Container2 &fv) {
	std::cout << "size:     " << sv.size() << " = " << fv.size() << std::endl;
}

template <class Container>
void print_container(const std::string &containername, const Container &container) {
	std::cout << containername << " contains:";
	for (typename Container::const_iterator it = container.begin(); it != container.end(); ++it)
		std::cout << ' ' << it->first;
	std::cout << std::endl;
}

template <typename Key, typename T>
bool check_maps(const std::map<Key, T> &sc, const ft::map<Key, T> &fc) {
	typename std::map<Key, T>::const_iterator sic = sc.begin();
	typename ft::map<Key, T>::const_iterator fic = fc.begin();

	while (sic != sc.end()) {
		if (sic->first != fic->first || sic->second != fic->second) {
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
void is_equal(Container1 &sc, Container2 &fc) {
	if (sc.size() == fc.size() && check_maps(sc, fc))
		std::cout << CLR_GOOD << "containers are equal" << CLR_RESET << std::endl;
	else {
		std::cerr << CLR_ERROR << "containers are not equal" << CLR_RESET << std::endl;
		error_exception();
	}
}


void map_tests() {
	std::cout << CLR_WARN << "MAP TESTS <<<<<<<<<<<<<<<<<<<<<<<<<<<                              " << CLR_RESET
			  << std::endl;
	std::cout << "\nTEST 1" << std::endl;
	{
		std::map<int, int> smap;
		ft::map<int, int> fmap;

		for (int i = 0; i < 10; ++i) {
			smap.insert(std::make_pair(i, i * 10));
			fmap.insert(std::make_pair(i, i * 10));
		}

		std::map<int, int>::iterator sit = smap.begin();
		ft::map<int, int>::iterator fit = fmap.begin();

		std::map<int, int>::const_iterator scit = smap.begin();
		ft::map<int, int>::const_iterator fcit = fmap.begin();

		std::map<int, int>::reverse_iterator srit = smap.rbegin();
		ft::map<int, int>::reverse_iterator frit = fmap.rbegin();

		std::map<int, int>::const_reverse_iterator srcit = smap.rbegin();
		ft::map<int, int>::const_reverse_iterator frcit = fmap.rbegin();

		if (scit != sit)
			error_exception();

		if (fcit != fit)
			error_exception();

		if (sit != scit)
			error_exception();

		if (fit != fcit)
			error_exception();

		if (srit != srcit)
			error_exception();

		if (frit != frcit)
			error_exception();

		if (srcit != srit)
			error_exception();

		if (frcit != frit)
			error_exception();

		scit = sit;
		fcit = fit;

		//		sit = scit;
		//		fit = fcit;

		srcit = srit;
		frcit = frit;

		//		srit = srcit;
		//		frit = frcit;

		sit++;
		fit++;

		++sit;
		++fit;

		scit++;
		fcit++;

		++scit;
		++fcit;

		srit++;
		frit++;

		srcit++;
		frcit++;

		++srit;
		++frit;

		++srcit;
		++frcit;


		//		fcit->first = 3;
		//		scit->first = 3;

		if (fcit->first == 3)
			error_exception();
		if (scit->first == 3)
			error_exception();

		if (scit->second == 3)
			error_exception();
		if (fcit->second == 3)
			error_exception();

		if (fit->first == 3)
			error_exception();
		if (sit->first == 3)
			error_exception();

		if (sit->second == 3)
			error_exception();
		if (fit->second == 3)
			error_exception();

		if (frcit->first == 3)
			error_exception();
		if (srcit->first == 3)
			error_exception();

		if (srcit->second == 3)
			error_exception();
		if (frcit->second == 3)
			error_exception();

		if (frit->first == 3)
			error_exception();
		if (srit->first == 3)
			error_exception();

		if (srit->second == 3)
			error_exception();
		if (frit->second == 3)
			error_exception();

		is_equal(smap, fmap);
	}
	std::cout << "\nTEST 2" << std::endl;
	{
		std::map<std::string, std::string> smap;
		ft::map<std::string, std::string> fmap;

		smap.insert(std::pair<std::string, std::string>("key1", "key1"));
		fmap.insert(std::pair<std::string, std::string>("key1", "key1"));

		smap.insert(std::pair<std::string, std::string>("key2", "val2"));
		fmap.insert(std::pair<std::string, std::string>("key2", "val2"));
		smap.insert(std::pair<std::string, std::string>("key3", "val3"));
		fmap.insert(std::pair<std::string, std::string>("key3", "val3"));
		smap.insert(std::pair<std::string, std::string>("key7", "val7"));
		fmap.insert(std::pair<std::string, std::string>("key7", "val7"));
		smap.insert(std::pair<std::string, std::string>("key4", "val4"));
		fmap.insert(std::pair<std::string, std::string>("key4", "val4"));
		smap.insert(std::pair<std::string, std::string>("key5", "val5"));
		fmap.insert(std::pair<std::string, std::string>("key5", "val5"));
		smap.insert(std::pair<std::string, std::string>("key6", "val6"));
		fmap.insert(std::pair<std::string, std::string>("key6", "val6"));
		smap.insert(std::pair<std::string, std::string>("key8", "val8"));
		fmap.insert(std::pair<std::string, std::string>("key8", "val8"));
		smap.insert(std::pair<std::string, std::string>("key9", "val9"));
		fmap.insert(std::pair<std::string, std::string>("key9", "val9"));
		smap.insert(std::pair<std::string, std::string>("key10", "val10"));
		fmap.insert(std::pair<std::string, std::string>("key10", "val10"));
		smap.insert(std::pair<std::string, std::string>("key11", "val11"));
		fmap.insert(std::pair<std::string, std::string>("key11", "val11"));
		smap.insert(std::pair<std::string, std::string>("key12", "val12"));
		fmap.insert(std::pair<std::string, std::string>("key12", "val12"));

		print_container("std: ", smap);
		print_container("ft:  ", fmap);
		is_equal(smap, fmap);

		smap["YA"] = "DA";
		fmap["YA"] = "DA";
		is_equal(smap, fmap);

		smap["NET"] = "NET";
		fmap["NET"] = "NET";
		smap["NET"] = "NET";
		fmap["NET"] = "NET";
		smap["NET"] = "NET";
		fmap["NET"] = "NET";

		smap["NET1"] = "NET1";
		fmap["NET1"] = "NET1";
		smap["NET2"] = "NET2";
		fmap["NET2"] = "NET2";
		smap["NET3"] = "NET3";
		fmap["NET3"] = "NET3";
		smap["NET4"] = "NET4";
		fmap["NET4"] = "NET4";
		smap["NET5"] = "NET5";
		fmap["NET5"] = "NET5";
		smap["NET6"] = "NET6";
		fmap["NET6"] = "NET6";
		smap["NET7"] = "NET7";
		fmap["NET7"] = "NET7";
		smap["NET8"] = "NET8";
		fmap["NET8"] = "NET8";
		smap["NET9"] = "NET9";
		fmap["NET9"] = "NET9";
		smap["NET10"] = "NET10";
		fmap["NET10"] = "NET10";
		is_equal(smap, fmap);

		print_container("std: ", smap);
		print_container("ft:  ", fmap);
		is_equal(smap, fmap);

		smap.erase("key4");
		fmap.erase("key4");
		smap.erase("key9");
		fmap.erase("key9");
		smap.erase("key1");
		fmap.erase("key1");
		smap.erase("key10");
		fmap.erase("key10");

		print_container("std: ", smap);
		print_container("ft:  ", fmap);
		is_equal(smap, fmap);

		std::cout << std::endl;
		for (ft::map<std::string, std::string>::const_iterator it = --fmap.end(); it != fmap.begin(); it--)
			std::cout << it->first << " ";
		std::cout << std::endl;

		for (std::map<std::string, std::string>::const_iterator it = --smap.end(); it != smap.begin(); it--)
			std::cout << it->first << " ";
		std::cout << std::endl;

		for (ft::map<std::string, std::string>::reverse_iterator it = --fmap.rend(); it != fmap.rbegin(); it--)
			std::cout << it->first << " ";
		std::cout << std::endl;

		for (std::map<std::string, std::string>::reverse_iterator it = --smap.rend(); it != smap.rbegin(); it--)
			std::cout << it->first << " ";
		std::cout << std::endl;
		for (ft::map<std::string, std::string>::const_reverse_iterator it = fmap.rbegin(); it != fmap.rend(); it++)
			std::cout << it->second << " ";
		std::cout << std::endl;

		for (std::map<std::string, std::string>::const_reverse_iterator it = smap.rbegin(); it != smap.rend(); it++)
			std::cout << it->second << " ";
		std::cout << std::endl;
	}
	std::cout << "\nTEST 3 SWAP" << std::endl;
	{
		std::map<int, int> smap;
		ft::map<int, int> fmap;

		for (int i = 0; i < 10; ++i) {
			smap.insert(std::make_pair(i, i * 10));
			fmap.insert(std::make_pair(i, i * 10));
		}

		std::map<int, int> smap2;
		ft::map<int, int> fmap2;

		smap2.swap(smap);
		fmap2.swap(fmap);

		is_equal(smap2, fmap2);
	}
	std::cout << "\nTEST 4 INSERT" << std::endl;
	{
		std::map<int, std::string> smap;
		ft::map<int, std::string> fmap;


		for (int i = 0; i < 4; ++i) {
			smap.insert(std::make_pair(i, "NET" + std::to_string(i)));
			fmap.insert(std::make_pair(i, "NET" + std::to_string(i)));
		}

		is_equal(smap, fmap);

		smap.insert(smap.begin(), std::make_pair(10, "NET" + std::to_string(10)));
		fmap.insert(fmap.begin(), std::make_pair(10, "NET" + std::to_string(10)));
		is_equal(smap, fmap);

		std::map<int, std::string> smap2;
		ft::map<int, std::string> fmap2;
		for (int i = 0; i < 4; ++i) {
			smap2.insert(std::make_pair(-i, "YES" + std::to_string(-i)));
			fmap2.insert(std::make_pair(-i, "YES" + std::to_string(-i)));
		}

		smap.insert(smap2.begin(), smap2.end());
		fmap.insert(fmap2.begin(), fmap2.end());
		is_equal(smap, fmap);

		if (!smap.empty())
			smap.clear();
		if (!fmap.empty())
			fmap.clear();
		is_equal(smap, fmap);
	}
	std::cout << "\nTEST 5 FIND, COUNT" << std::endl;
	{
		std::map<std::string, std::string> smap;
		ft::map<std::string, std::string> fmap;

		for (int i = 0; i < 4; ++i) {
			smap.insert(std::make_pair(std::to_string(i), "NET" + std::to_string(i)));
			fmap.insert(std::make_pair(std::to_string(i), "NET" + std::to_string(i)));
		}

		std::string key = "1";

		std::pair<std::string, std::string> sd;
		sd.first = "1";
		sd.second = "1";


		if (smap.find(sd.first) == smap.end())
			error_exception();
		if (fmap.find(sd.first) == fmap.end())
			error_exception();

		if (!(smap.find("7") == smap.end()))
			error_exception();
		if (!(fmap.find("7") == fmap.end()))
			error_exception();

		if (!smap.count(sd.first))
			error_exception();

		if (!fmap.count(sd.first))
			error_exception();

		if (smap.count("7"))
			error_exception();
		if (fmap.count("7"))
			error_exception();

		is_equal(smap, fmap);

	}
	std::cout << "\nTEST 6 OTHERS" << std::endl;
	{
		std::map<std::string, std::string> smap;
		ft::map<std::string, std::string> fmap;

		for (int i = 0; i < 4; ++i) {
			smap.insert(std::make_pair(std::to_string(i), "NET" + std::to_string(i)));
			fmap.insert(std::make_pair(std::to_string(i), "NET" + std::to_string(i)));
		}

		ft::map<std::string, std::string>::const_iterator fit;
		std::map<std::string, std::string>::const_iterator sit;

		smap.lower_bound("123");
		fmap.lower_bound("123");

		smap.lower_bound("1");
		fmap.lower_bound("1");

		sit = smap.lower_bound("123");
		fit = fmap.lower_bound("123");

		sit = smap.lower_bound("1");
		fit = fmap.lower_bound("1");

		smap.upper_bound("123");
		fmap.upper_bound("123");

		smap.upper_bound("1");
		fmap.upper_bound("1");

		sit = smap.upper_bound("123");
		fit = fmap.upper_bound("123");

		sit = smap.upper_bound("1");
		fit = fmap.upper_bound("1");

		std::pair<std::map<std::string, std::string>::const_iterator, std::map<std::string, std::string>::const_iterator> tmp1 = smap.equal_range(
				"2");
		std::pair<ft::map<std::string, std::string>::const_iterator, ft::map<std::string, std::string>::const_iterator> tmp2 = fmap.equal_range(
				"2");

		std::pair<std::map<std::string, std::string>::iterator, std::map<std::string, std::string>::iterator> tmp3 = smap.equal_range(
				"2");
		std::pair<ft::map<std::string, std::string>::iterator, ft::map<std::string, std::string>::iterator> tmp4 = fmap.equal_range(
				"2");

		smap.key_comp();
		fmap.key_comp();

		smap.value_comp();
		fmap.value_comp();
		is_equal(smap, fmap);
	}
	std::cout << "\nTEST 6 CONSTRUCTORS + ERASE" << std::endl;
	{
		std::map<std::string, std::string> smap;
		ft::map<std::string, std::string> fmap;

		for (int i = 0; i < 15; ++i) {
			smap.insert(std::make_pair(std::to_string(i), "NET" + std::to_string(i)));
			fmap.insert(std::make_pair(std::to_string(i), "NET" + std::to_string(i)));
		}
		for (int i = -15; i < 0; ++i) {
			smap.insert(std::make_pair(std::to_string(i), "NET" + std::to_string(i)));
			fmap.insert(std::make_pair(std::to_string(i), "NET" + std::to_string(i)));
		}
		is_equal(smap, fmap);
		std::map<std::string, std::string> smap2(smap);
		ft::map<std::string, std::string> fmap2(fmap);
		is_equal(smap2, fmap2);

		std::map<std::string, std::string> smap3(smap2.begin(), smap2.end());
		ft::map<std::string, std::string> fmap3(fmap2.begin(), fmap2.end());
		is_equal(smap2, fmap2);

		std::map<std::string, std::string> smap4 = smap3;
		ft::map<std::string, std::string> fmap4 = fmap3;
		print_containers_params(smap4, fmap4);
		print_container("std: ", smap4);
		print_container("ft:  ", fmap4);
		is_equal(smap2, fmap2);

		smap4.erase(smap4.begin());
		fmap4.erase(fmap4.begin());
		smap4.erase(smap4.begin());
		fmap4.erase(fmap4.begin());
		smap4.erase(smap4.begin());
		fmap4.erase(fmap4.begin());

		smap4.erase(++smap4.begin());
		fmap4.erase(++fmap4.begin());
		smap4.erase(++smap4.begin());
		fmap4.erase(++fmap4.begin());
		smap4.erase(++smap4.begin());
		fmap4.erase(++fmap4.begin());

		smap4.erase("10");
		fmap4.erase("10");
		is_equal(smap2, fmap2);

		smap4.erase(smap4.begin(), smap4.end());
		fmap4.erase(fmap4.begin(), fmap4.end());
		is_equal(smap2, fmap2);

		std::map<size_t, size_t> smap5;
		ft::map<size_t, size_t> fmap5;
		for (int i = 0; i < 1000; ++i) {
			long long tm = rand() % 10000;
			smap5.insert(std::make_pair(tm, i));
			fmap5.insert(std::make_pair(tm, i));
		}
		for (int i = -1000; i < 0; ++i) {
			long long tm = rand() % 10000 * (-1);
			smap5.insert(std::make_pair(tm, i));
			fmap5.insert(std::make_pair(tm, i));
		}

		for (int i = -1000; i < 0; ++i) {
			long long tm = rand() % 10000 * (-1);
			smap5.erase(tm);
			fmap5.erase(tm);
			smap5.erase(-tm);
			fmap5.erase(-tm);
		}
		is_equal(smap2, fmap2);
	}
	std::cout << CLR_WARN << "MAP TESTS DONE <<<<<<<<<<<<<<<<<<<<<<<<<<<                              " << CLR_RESET
			  << std::endl;
}


int main() {
	srand(time(NULL));
	map_tests();

	return 0;
}