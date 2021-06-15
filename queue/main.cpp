#include <iostream>
#include <queue>
#include "queue.hpp"

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


void 	queue_tests() {
	std::cout << CLR_WARN << "QUEUE TESTS <<<<<<<<<<<<<<<<<<<<<<<<<<<                              " << CLR_RESET
			  << std::endl;
	std::cout << "\nTEST 1 " << std::endl;
	{
		std::queue <int> sq;
		ft::queue <int> fq;

		if (!fq.empty())
			error_exception();
		if (!sq.empty())
			error_exception();

		for (int  i = 0; i < 10; i++){
			sq.push(i);
			fq.push(i);
		}

		if (fq.empty())
			error_exception();
		if (sq.empty())
			error_exception();

		std::cout << "std size:  " << sq.size() << std::endl;
		std::cout << "ft  size:  " << fq.size() << std::endl;

		std::cout << "std: " << "front : " << sq.front() << std::endl;
		std::cout << "ft:  " << "front : " << fq.front() << std::endl;

		std::cout << "std: " << "back : " << sq.back() << std::endl;
		std::cout << "ft:  " << "back : " << fq.back() << std::endl;

		for (int i = 0; i > 3; i++){
			fq.pop();
			sq.pop();
		}
		std::cout << "std size:  " << sq.size() << std::endl;
		std::cout << "ft  size:  " << fq.size() << std::endl;

		std::cout << "std: " << "front : " << sq.front() << std::endl;
		std::cout << "ft:  " << "front : " << fq.front() << std::endl;

		std::cout << "std: " << "back : " << sq.back() << std::endl;
		std::cout << "ft:  " << "back : " << fq.back() << std::endl;


		while (fq.size() != 0 && sq.size() != 0){
			sq.pop();
			fq.pop();
			std::cout << "std size:  " << sq.size() << std::endl;
			std::cout << "ft  size:  " << fq.size() << std::endl;

			std::cout << "std: " << "front : " << sq.front() << std::endl;
			std::cout << "ft:  " << "front : " << fq.front() << std::endl;

			std::cout << "std: " << "back : " << sq.back() << std::endl;
			std::cout << "ft:  " << "back : " << fq.back() << std::endl;
		}

	}
	std::cout << "\nTEST 2 OPERATIONS" << std::endl;
	{
		std::queue<int> a;
		std::queue <int> aa;
		ft::queue <int> b;
		ft::queue <int> bb;


		for (int i = 1; i < 7; i++){
			a.push(i * 10);
			aa.push(i * 10);
			b.push(i * 10);
			bb.push(i * 10);
		}
		std::cout << "std::queue: == " << (a == aa) << std::endl;
		std::cout << "ft::queue:  == " << (a == aa) << std::endl;
		std::cout << "std::queue: >  " << (a > aa) << std::endl;
		std::cout << "ft::queue:  >  " << (a > aa) << std::endl;
		std::cout << "std::queue: >= " << (a >= aa) << std::endl;
		std::cout << "ft::queue:  >= " << (a >= aa) << std::endl;
		std::cout << "std::queue: <  " << (a < aa) << std::endl;
		std::cout << "ft::queue:  <  " << (a < aa) << std::endl;
		std::cout << "std::queue: <= " << (a <= aa) << std::endl;
		std::cout << "ft::queue:  <= " << (a <= aa) << std::endl;
		std::cout << "std::queue: != " << (a != aa) << std::endl;
		std::cout << "ft::queue:  != " << (a != aa) << std::endl;
	}
	std::cout << CLR_WARN << "QUEUE TESTS DONE <<<<<<<<<<<<<<<<<<<<<<<<<<<                              " << CLR_RESET;
}


int 	main(){
	queue_tests();
	return 0;
}