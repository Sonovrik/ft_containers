#include "list.hpp"
#include <unistd.h>
//#include "../utils/utils.hpp"
//#include "../utils/iterators.hpp"

#include <list>
bool single_digit (const int& value) { return (value>10); }
bool same_integral_part (int first, int second)
{ return ( int(first)>int(second) ); }
int main() {
//	ft::list<int> list(5, 1234);
//	ft::list<int>::iterator itr;
//	list.push_back(-1);
//	list.begin();
//	std::cout << list.size() << std::endl;
//	ft::list<int> list2(list.begin(), list.end());
//
//	std::cout << list2.size() << std::endl;
////	ft::list<int>::iterator it = list2.begin();
////	while (it != list2.end()){
////		std::cout << *it << std::endl;
////		it++;
////	}
//
//	ft::list<int> lis(list2);
//
//	ft::list<int>::iterator it = lis.begin();
//	while (it != lis.end()){
//		std::cout << *it << std::endl;
//		it++;
//	}
//	std::cout << lis.size() << std::endl;
//
//
//	ft::list<int> kl = lis;
//
//	kl.push_front(10);
//	ft::list<int>::iterator i = kl.begin();
//	while (i != kl.end()){
//		std::cout << *i << std::endl;
//		i++;
//	}
//	std::cout << kl.size() << std::endl;
//
//
//	kl.assign(3, 0);
//
//	i = kl.begin();
//	while (i != kl.end()){
//		std::cout << *i << std::endl;
//		i++;
//	}
//	std::cout << kl.size() << std::endl;
//
//
//	kl.assign(list2.begin(), list2.end());
//	i = kl.begin();
//	while (i != kl.end()){
//		std::cout << *i << std::endl;
//		i++;
//	}
//
//	std::cout << "START" << std::endl;
//	i = kl.begin();
//	kl.insert(kl.end(), -12);
//	i = kl.begin();
//	while (i != kl.end()){
//		std::cout << *i << std::endl;
//		i++;
//	}
//	std::cout << kl.size() << std::endl;
//
//
//	std::cout << "START" << std::endl;
//	kl.clear();
//	kl.insert(kl.begin(), 10, -5);
//	i = kl.begin();
//	while (i != kl.end()){
//		std::cout << *i << std::endl;
//		i++;
//	}
//	std::cout << kl.size() << std::endl;
//
//	ft::list<int> mr;
//	for (int i = 0; i < 5; i++){
//		mr.push_back(i);
//	}
//
//
//	std::cout << "START" << std::endl;
//	kl.insert(kl.begin(), mr.begin(), mr.end());
//	i = kl.begin();
//	while (i != kl.end()){
//		std::cout << *i << std::endl;
//		i++;
//	}
//	std::cout << kl.size() << std::endl;
//
//
//
//	std::cout << "START" << std::endl;
//	ft::list<int> re = kl;
//	i = re.begin();
//	while (i != re.end()){
//		std::cout << *i << std::endl;
//		i++;
//	}
//
//	std::cout << "START" << std::endl;
//	kl.clear();
//	kl.insert(kl.end(), re.begin(), re.end());
//	std::cout << "OK" << std::endl;
//	i = kl.begin();
//	while (i != kl.end()){
//		std::cout << *i << std::endl;
//		i++;
//	}
//	std::cout << kl.size() << std::endl;
//
//
//	i = kl.erase(kl.begin());
//	std::cout << *i << std::endl;
//
//	std::cout << "START" << std::endl;
//	i = kl.begin();
//	while (i != kl.end()){
//		std::cout << *i << std::endl;
//		i++;
//	}
//	std::cout << kl.size() << std::endl;
//
//	std::cout << "START" << std::endl;
//	i = kl.begin();
//	i++;
//	i++;
//	i++;
//	i = kl.erase(kl.begin(), i);
//	std::cout << *i << std::endl;
//	i = kl.begin();
//	while (i != kl.end()){
//		std::cout << *i << std::endl;
//		i++;
//	}
//	std::cout << kl.size() << std::endl;

	ft::list<int> mylist1, mylist2;
	ft::list<int>::iterator it;

	// set some initial values:
	for (int i=1; i<=4; ++i)
		mylist1.push_back(i);      // mylist1: 1 2 3 4

	for (int i=1; i<=3; ++i)
		mylist2.push_back(i*10);   // mylist2: 10 20 30
	for (int i=1; i<=3; ++i)
		mylist2.push_back(i*10);
	for (int i=1; i<=3; ++i)
		mylist2.push_back(i*10);
//	it = mylist1.begin();
//	++it;                         // points to 2

	// mylist1: 1 10 20 30 3 4
//	mylist1.splice (it, mylist2);
//	for (ft::list<int>::iterator it2 = mylist1.begin(); it2 != mylist1.end(); it2++){
//		std::cout << *it2 << " ";
//	}
//	std::cout << std::endl;
//
//	std::cout << mylist2.size() << " ";
//	if (mylist2.begin() == mylist2.end())
//		std::cout << "SAD";
//	mylist2.splice (mylist2.begin(),mylist1, it);
//	for (ft::list<int>::iterator it2 = mylist2.begin(); it2 != mylist2.end(); it2++){
//		std::cout << *it2 << " ";
//	}
//	std::cout << std::endl;

	mylist2.reverse();
	for (ft::list<int>::iterator it2 = mylist2.begin(); it2 != mylist2.end(); it2++){
		std::cout << *it2 << " ";
	}
	std::cout << std::endl;
	mylist2.remove(10);
	for (ft::list<int>::iterator it2 = mylist2.begin(); it2 != mylist2.end(); it2++){
		std::cout << *it2 << " ";
	}
	std::cout << std::endl;

//	mylist2.remove_if(single_digit);
//	for (ft::list<int>::iterator it2 = mylist2.begin(); it2 != mylist2.end(); it2++){
//		std::cout << *it2 << " ";
//	}

	for (int i = 0; i < 3; i++)
		mylist2.push_back(1);
	for (int i = 0; i < 3; i++)
		mylist2.push_back(2);
	for (ft::list<int>::iterator it2 = mylist2.begin(); it2 != mylist2.end(); it2++){
		std::cout << *it2 << " ";
	}
	std::cout << std::endl;
	mylist2.unique(same_integral_part);
	for (ft::list<int>::iterator it2 = mylist2.begin(); it2 != mylist2.end(); it2++){
		std::cout << *it2 << " ";
	}
	std::cout << std::endl;


	std::list<int> lst;
	for (int i = 3; i > 1; i--)
		lst.push_back(i * 10);
	for (int i = 3; i > 1; i--)
		lst.push_back(i * 10);
	for (int i = 3; i > 1; i--)
		lst.push_back(i * 10);
	for (int i = 0; i < 3; i++)
		lst.push_back(1);
	for (int i = 0; i < 3; i++)
		lst.push_back(2);

	for (std::list<int>::iterator it2 = lst.begin(); it2 != lst.end(); it2++){
		std::cout << *it2 << " ";
	}
	std::cout << std::endl;

	lst.unique(same_integral_part);
	for (std::list<int>::iterator it2 = lst.begin(); it2 != lst.end(); it2++){
		std::cout << *it2 << " ";
	}
	std::cout << std::endl;
}
