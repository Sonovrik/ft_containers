#include "stack.hpp"
#include <stack>
#include <iostream>
#define	CLR_GOOD	"\033[1;32m"
#define	CLR_ERROR	"\033[41;30m"
#define	CLR_WARN	"\033[48;5;202m\033[38;5;0m"
#define	CLR_RESET	"\033[0m"

void		error_exception() {
	std::string	msg;
	msg.append(CLR_ERROR);
	msg.append("FAIL!!!");
	msg.append(CLR_RESET);
	msg.push_back('\n');
	throw std::runtime_error(msg);
}

void 	stack_tests(){
	std::cout << CLR_WARN << "LIST TESTS <<<<<<<<<<<<<<<<<<<<<<<<<<<                              " << CLR_RESET << std::endl;
	std::cout << "\nTEST 1 " << std::endl;
	{
		ft::stack<int> fs;
		std::stack<int> ss;

		if (!fs.empty())
			error_exception();
		if (!ss.empty())
			error_exception();

		for (int i = 0; i < 10; ++i) {
			fs.push(i);
			ss.push(i);
		}

		if (fs.empty())
			error_exception();
		if (ss.empty())
			error_exception();

		std::cout << "std: " << "top : " << ss.top() << std::endl;
		std::cout << "ft:  " << "top : " << fs.top() << std::endl;

		const int a = ss.top();
		const int b = fs.top();
		std::cout << "const items: " << std::endl;
		std::cout << "std: " << "top : " << a << std::endl;
		std::cout << "ft:  " << "top : " << b << std::endl;

		std::cout << "std size:  " << ss.size() << std::endl;
		std::cout << "ft  size:  " << fs.size() << std::endl;

		for (int i = 0; i < 4; i++) {
			fs.pop();
			ss.pop();
		}
		std::cout << "std size:  " << ss.size() << std::endl;
		std::cout << "ft  size:  " << fs.size() << std::endl;
		std::cout << "std: " << "top : " << ss.top() << std::endl;
		std::cout << "ft:  " << "top : " << fs.top() << std::endl;
	}
	std::cout << "\nTEST 2 OPERATIONS" << std::endl;
	{
		std::stack <int> a;
		std::stack <int> aa;
		ft::stack <int> b;
		ft::stack <int> bb;


		for (int i = 1; i < 7; i++){
			a.push(i * 10);
			aa.push(i * 10);
			b.push(i * 10);
			bb.push(i * 10);
		}
		std::cout << "std::stack: == " << (a == aa) << std::endl;
		std::cout << "ft::stack:  == " << (a == aa) << std::endl;
		std::cout << "std::stack: >  " << (a > aa) << std::endl;
		std::cout << "ft::stack:  >  " << (a > aa) << std::endl;
		std::cout << "std::stack: >= " << (a >= aa) << std::endl;
		std::cout << "ft::stack:  >= " << (a >= aa) << std::endl;
		std::cout << "std::stack: <  " << (a < aa) << std::endl;
		std::cout << "ft::stack:  <  " << (a < aa) << std::endl;
		std::cout << "std::stack: <= " << (a <= aa) << std::endl;
		std::cout << "ft::stack:  <= " << (a <= aa) << std::endl;
		std::cout << "std::stack: != " << (a != aa) << std::endl;
		std::cout << "ft::stack:  != " << (a != aa) << std::endl;
	}
	std::cout << CLR_WARN << "LIST TESTS DONE <<<<<<<<<<<<<<<<<<<<<<<<<<<                              " << CLR_RESET << std::endl;
}


int 	main(){

	stack_tests();

	return 0;
}