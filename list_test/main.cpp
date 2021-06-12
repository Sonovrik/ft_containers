#include <iostream>
#include "list.hpp"
#include <list>

int 	main(){
	ft::list<int> asd;
	for (int i = 0; i < 10; i++)
		asd.push_back(1);
	asd.pop_back();
}