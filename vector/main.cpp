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
#define STR_FAIL	std::string(CLR_ERROR) + "failed test" + CLR_RESET

void		error_exception(const std::string& hint = "")
{
	std::string	msg(CLR_ERROR);	msg = msg + "failed test" + CLR_RESET;
	if (!hint.empty())
		msg = msg + ":\n" + CLR_ERROR + hint + CLR_RESET;
	throw std::runtime_error(msg);
}

template <class T>
std::string	ft_tostring(T val) { std::ostringstream	oss; oss << val; return (oss.str()); }
bool		intpredicate(int x)	{ return (x >= 666); }
bool		sizetpredicate(int x)	{ return (x >= 666 && x <= 66666); }
bool		binpredicate(int& x, int& y)
{	return (x == 420 || y == 420 || x == 666 || y == 666);	}
bool		doublecomp(double first, double second) { return (int(first) < int(second)); }
bool		reversecomp(const std::string& first, const std::string& second)
{	return (first > second);	}

template <class Container1, class Container2>
void		printrelationaloperators(const Container1& scont0, const Container1& scont1,
									 const Container2& fcont0, const Container2& fcont1)
{
	std::cout << "relational ops" << std::endl;
	bool	e0, e1, ne0, ne1, l0, l1, le0, le1, g0, g1, ge0, ge1;
	e0	= (scont0 ==	scont1);	e1	= (fcont0 ==	fcont1);
	ne0	= (scont0 !=	scont1);	ne1	= (fcont0 !=	fcont1);
	l0	= (scont0 <		scont1);	l1	= (fcont0 <		fcont1);
	le0	= (scont0 <=	scont1);	le1	= (fcont0 <=	fcont1);
	g0	= (scont0 >		scont1);	g1	= (fcont0 >		fcont1);
	ge0	= (scont0 >=	scont1);	ge1	= (fcont0 >=	fcont1);
	if (e0 != e1 || ne0 != ne1 || l0 != l1 || le0 != le1 || g0 != g1 || ge0 != ge1)
		error_exception("relational operators");
	std::cout << "== " << e0	<< e1	<< std::endl;
	std::cout << "!= " << ne0	<< ne1	<< std::endl;
	std::cout << "<  " << l0	<< l1	<< std::endl;
	std::cout << "<= " << le0	<< le1	<< std::endl;
	std::cout << ">  " << g0	<< g1	<< std::endl;
	std::cout << ">= " << ge0	<< ge1	<< std::endl;
}

template <class Container>
void		printcontainer(const std::string& containername, const Container& container)
{
	std::cout << containername << " contains:";
	for (typename Container::const_iterator it = container.begin(); it != container.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;
}

template <class Container>
void		printmap(const std::string& containername, const Container& container)
{
	std::cout << containername << " contains:\n";
	for (typename Container::const_iterator it = container.begin(); it != container.end(); ++it)
		std::cout << it->first << " => " << it->second << std::endl;
}

template <class Container1, class Container2>
void		are_equal_print(const Container1& scont, const Container2& fcont, size_t i = 0)
{
	if (scont.size() == fcont.size() &&
		std::equal(scont.begin(), scont.end(), fcont.begin()) &&
		std::equal(fcont.begin(), fcont.end(), scont.begin()))
	{
		std::cout << CLR_GOOD << "containers are equal" << CLR_RESET;
		if (!i)
			std::cout << std::endl;
		else
			std::cout << CLR_GOOD << " x" << i << CLR_RESET << "\r";
	}
	else
	{
		std::cerr << CLR_ERROR << "containers are not equal" << CLR_RESET << std::endl;
		if (scont.size() != fcont.size())
			std::cerr << CLR_ERROR << "wrong size" << CLR_RESET << std::endl;
		error_exception();
	}
}

template <class Container1, class Container2>
void		printbothdirs(const Container1& scont, const Container2& fcont)
{
	std::cout << "forward:" << std::endl;
	{
		typename Container1::const_iterator sit = scont.begin();
		typename Container2::const_iterator fit = fcont.begin();
		std::cout << "scont contains: ";
		while (sit != scont.end())
			std::cout << " " << *sit++;

		std::cout << std::endl << "fcont contains: ";
		while (fit != fcont.end())
			std::cout << " " << *fit++;
		std::cout << std::endl;
	}
	std::cout << "reverse:" << std::endl;
	{
		typename Container1::const_reverse_iterator sit = scont.rbegin();
		typename Container2::const_reverse_iterator fit = fcont.rbegin();
		std::cout << "scont contains: ";
		while (sit != scont.rend())
			std::cout << " " << *sit++;

		std::cout << std::endl << "fcont contains: ";
		while (fit != fcont.rend())
			std::cout << " " << *fit++;
		std::cout << std::endl;
	}
}

void		ft_vector_tests(int ac, char **av)
{
	std::cout << CLR_WARN << "VECTOR TESTS <<<<<<<<<<<<<<<<<<<<<<<<<<<                              " << CLR_RESET << std::endl;
	{
		std::vector<std::string>	svect;
		ft::vector<std::string>		fvect;
		std::cout << svect.size() << " = " << fvect.size() << std::endl;
		std::cout << svect.capacity() << " = " << fvect.capacity() << std::endl;
		std::cout << svect.max_size() << " = " << fvect.max_size() << std::endl;

		std::vector<int>	svectint;
		ft::vector<int>		fvectint;
		std::cout << svectint.size() << " = " << fvectint.size() << std::endl;
		std::cout << svectint.capacity() << " = " << fvectint.capacity() << std::endl;
		std::cout << svectint.max_size() << " = " << fvectint.max_size() << std::endl;

	}

	{
		std::vector<std::string>	svect(av, av + ac);
		ft::vector<std::string>		fvect(av, av + ac);

		printcontainer("svect", svect);
		printcontainer("fvect", fvect);

		std::cout << svect.size() << " = " << fvect.size() << std::endl;
	}

	{
		std::cout << "-------------" << std::endl;
		std::vector<std::string> svect(7, "hello");
		ft::vector<std::string> fvect(7, "hello");
		std::cout << svect.size() << " = " << fvect.size() << std::endl;
		std::cout << svect.capacity() << " = " << fvect.capacity() << std::endl;
		std::cout << svect.max_size() << " = " << fvect.max_size() << std::endl;


		{
			std::vector<std::string> svect2(svect);
			ft::vector<std::string> fvect2(fvect);
			std::cout << svect2.size() << " = " << fvect2.size() << std::endl;
			std::cout << svect2.capacity() << " = " << fvect2.capacity() << std::endl;
			std::cout << svect2.max_size() << " = " << fvect2.max_size() << std::endl;
			are_equal_print(svect2, fvect2);

			svect2.clear();
			fvect2.clear();
			std::cout << svect2.size() << " = " << fvect2.size() << std::endl;
			std::cout << svect2.capacity() << " = " << fvect2.capacity() << std::endl;
			std::cout << svect2.max_size() << " = " << fvect2.max_size() << std::endl;
			are_equal_print(svect2, fvect2);

			std::vector<std::string> svect3(7, "hello");
			ft::vector<std::string> fvect3(7, "hello");
			svect2 = svect3;
			fvect2 = fvect3;

			std::cout << svect2.size() << " = " << fvect2.size() << std::endl;
			std::cout << svect2.capacity() << " = " << fvect2.capacity() << std::endl;
			std::cout << svect2.max_size() << " = " << fvect2.max_size() << std::endl;
			are_equal_print(svect2, fvect2);
			svect2.reserve(100);
			fvect2.reserve(100);
			std::cout << svect2.size() << " = " << fvect2.size() << std::endl;
			std::cout << svect2.capacity() << " = " << fvect2.capacity() << std::endl;
			std::cout << svect2.max_size() << " = " << fvect2.max_size() << std::endl;
			are_equal_print(svect2, fvect2);
		}
		printbothdirs(svect, fvect);

		std::cout << "front and back change" << std::endl;
		svect.front() = "front";
		svect.back() = "back";
		fvect.front() = "front";
		fvect.back() = "back";

		std::vector<std::string>::iterator sit = svect.begin();
		ft::vector<std::string>::iterator fit = fvect.begin();

		for (size_t i = 1; sit != svect.end() && fit != fvect.end(); ++i) {
			*sit++ += ft_tostring(i);
			*fit++ += ft_tostring(i);
		}

		printbothdirs(svect, fvect);

		sit = svect.begin();
		fit = fvect.begin();


		while (sit != svect.end() && fit != fvect.end())
		{
			std::ptrdiff_t	sdist = std::distance(sit, svect.begin());
			std::ptrdiff_t	fdist = std::distance(fit, fvect.begin());
			std::cout << sdist << "\t" << fdist << std::endl;
			sit = 1 + sit;
			fit = 1 + fit;
			sit = sit - 1;
			fit = fit - 1;
			sit = sit + 1;
			fit = fit + 1;
		}
	}

	{
		/*		this block is full of crap			*/
		std::cout << "-------------" << std::endl;
		std::vector<std::string>	svect(7, "hello");
		ft::vector<std::string>		fvect(7, "hello");
		std::vector<std::string>::reverse_iterator	sit = svect.rbegin();
		ft::vector<std::string>::reverse_iterator	fit = fvect.rbegin();

		std::vector<std::string>::const_reverse_iterator	sit2 = sit;
		ft::vector<std::string>::const_reverse_iterator		fit2 = fit;

		/*		this it the most painfull part		*/
		std::cout << sit2 - sit <<" == " << fit2 - fit << std::endl;
		if (sit <= sit2)
			std::cout << "allo == ";
		if (fit <= fit2)
			std::cout << "allo\n";

		while (sit != svect.rend() && fit != fvect.rend())
		{
			std::ptrdiff_t	sdist = std::distance(sit, svect.rbegin());
			std::ptrdiff_t	fdist = std::distance(fit, fvect.rbegin());
			std::cout << sdist << "\t" << fdist << std::endl;
			++sit;
			fit = 1 + fit;
		}
		/*		i hate this part really much		*/
	}

	{
		std::cout << "-------------" << std::endl;
		std::cout << "swapster" << std::endl;
		std::vector<int> sfoo(2, 100);   // two ints with a value of 100
		ft::vector<int> ffoo(2, 100);   // two ints with a value of 100
		std::vector<int> sbar(4, 200);   // four ints with a value of 200
		ft::vector<int> fbar(4, 200);   // four ints with a value of 200

		printcontainer("sfoo", sfoo);
		printcontainer("ffoo", ffoo);
		printcontainer("sbar", sbar);
		printcontainer("fbar", fbar);
		are_equal_print(sfoo, ffoo);
		are_equal_print(sbar, fbar);

		std::vector<int>::iterator sit1 = sfoo.begin();
		ft::vector<int>::iterator fit1 = ffoo.begin();
		std::vector<int>::iterator sit2 = sbar.begin();
		ft::vector<int>::iterator fit2 = fbar.begin();
		std::cout << sfoo.capacity() << " = " << ffoo.capacity() << std::endl;
		std::cout << sbar.capacity() << " = " << fbar.capacity() << std::endl;
		std::cout << *sit1 << " " << *sit2 << std::endl;
		std::cout << *fit1 << " " << *fit2 << std::endl;

		sfoo.swap(sbar);
		ffoo.swap(fbar);

		printcontainer("sfoo", sfoo);
		printcontainer("ffoo", ffoo);
		printcontainer("sbar", sbar);
		printcontainer("fbar", fbar);
		are_equal_print(sfoo, ffoo);
		are_equal_print(sbar, fbar);

		std::cout << sfoo.capacity() << " = " << ffoo.capacity() << std::endl;
		std::cout << sbar.capacity() << " = " << fbar.capacity() << std::endl;

		std::cout << *sit1 << " " << *sit2 << std::endl;
		std::cout << *fit1 << " " << *fit2 << std::endl;

		try								{	sfoo.at(2378);	}
		catch (const std::exception& e)	{	std::cerr << e.what() << std::endl;	}
		try								{	ffoo.at(2378);	}
		catch (const std::exception& e)	{	std::cerr << e.what() << std::endl;	}
		try								{	sfoo.resize(sfoo.max_size() + 1);	}
		catch (const std::exception& e)	{	std::cerr << e.what() << std::endl;	}
		try								{	ffoo.resize(ffoo.max_size() + 1);	}
		catch (const std::exception& e)	{	std::cerr << e.what() << std::endl;	}
		are_equal_print(sfoo, ffoo);
		are_equal_print(sbar, fbar);

		std::cout << "-------------" << std::endl;
		std::cout << "assignster" << std::endl;
		sfoo.assign(200, 666);
		ffoo.assign(200, 666);
		std::cout << sfoo.size() << " = " << ffoo.size() << std::endl;
		std::cout << sfoo.capacity() << " = " << ffoo.capacity() << std::endl;
		are_equal_print(sfoo, ffoo);

		sfoo.assign(sbar.begin(), sbar.end());
		ffoo.assign(fbar.begin(), fbar.end());
		std::cout << sfoo.size() << " = " << ffoo.size() << std::endl;
		std::cout << sfoo.capacity() << " = " << ffoo.capacity() << std::endl;
		are_equal_print(sfoo, ffoo);

		sbar.assign(400, 666);
		fbar.assign(400, 666);
		sfoo.assign(sbar.begin(), sbar.end());
		ffoo.assign(fbar.begin(), fbar.end());
		std::cout << sfoo.size() << " = " << ffoo.size() << std::endl;
		std::cout << sfoo.capacity() << " = " << ffoo.capacity() << std::endl;
		are_equal_print(sfoo, ffoo);
	}

	{
		std::cout << "-------------" << std::endl;
		std::vector<int>::size_type	ssz;	std::vector<int>	sfoo;
		ft::vector<int>::size_type	fsz;	ft::vector<int>		ffoo;
		ssz = sfoo.capacity();				fsz = ffoo.capacity();
		std::cout << "making foo grow:\n";

		for (int i = 0; i < 100; ++i)
		{
			sfoo.push_back(i);
			ffoo.push_back(i);
			if (ssz != sfoo.capacity() || fsz != ffoo.capacity())
			{
				ssz = sfoo.capacity();
				fsz = ffoo.capacity();
				std::cout << "capacity changed: " << ssz << "\t" << fsz << '\n';
			}
		}
		are_equal_print(sfoo, ffoo);

		std::cout << "making foo smaller:\n";
		for (int i = 0; i < 64; ++i)
		{
			sfoo.pop_back();
			ffoo.pop_back();
			if (ssz != sfoo.capacity() || fsz != ffoo.capacity())
			{
				ssz = sfoo.capacity();
				fsz = ffoo.capacity();
				std::cout << "capacity changed: " << ssz << "\t" << fsz << '\n';
			}
		}
		std::cout << "sizes changed: " << sfoo.size() << "\t" << ffoo.size() << '\n';
		are_equal_print(sfoo, ffoo);
	}

	{
		std::cout << "-------------" << std::endl;
		std::vector<int>	sfoo;	ft::vector<int>		ffoo;

		// set some initial content:
		for (int i = 1; i < 10; i++)
		{
			sfoo.push_back(i);		ffoo.push_back(i);
		}

		sfoo.resize(5);				ffoo.resize(5);
		std::cout << sfoo.capacity() << " = " << ffoo.capacity() << std::endl;
		are_equal_print(sfoo, ffoo);

		sfoo.resize(8, 100);		ffoo.resize(8, 100);
		std::cout << sfoo.capacity() << " = " << ffoo.capacity() << std::endl;
		are_equal_print(sfoo, ffoo);

		sfoo.resize(12);			ffoo.resize(12);
		std::cout << sfoo.capacity() << " = " << ffoo.capacity() << std::endl;
		are_equal_print(sfoo, ffoo);

		sfoo.resize(0);				ffoo.resize(0);
		std::cout << sfoo.capacity() << " = " << ffoo.capacity() << std::endl;
		are_equal_print(sfoo, ffoo);

		sfoo.resize(20, 6);			ffoo.resize(20, 6);
		std::cout << sfoo.capacity() << " " << sfoo.size() << " = " << ffoo.capacity() << " " << ffoo.size()<< std::endl;
		are_equal_print(sfoo, ffoo);
		std::cout << "asdasdad" << std::endl;
		sfoo.resize(666, 666);		ffoo.resize(666, 666);
		std::cout << sfoo.capacity() << " = " << ffoo.capacity() << std::endl;
		are_equal_print(sfoo, ffoo);

		sfoo.resize(6, 6626);		ffoo.resize(6, 6626);
		std::cout << sfoo.capacity() << " = " << ffoo.capacity() << std::endl;
		are_equal_print(sfoo, ffoo);

		printcontainer("sfoo", sfoo);
		printcontainer("ffoo", ffoo);
	}
//
//	{
//		std::cout << "-------------\ninsertster (capacities may differ depending on platform)" << std::endl;
//		std::vector<int>	svect(3, 100);	ft::vector<int>		fvect(3, 100);
//		std::vector<int>::iterator sit;		ft::vector<int>::iterator	fit;
//		printcontainer("svect", svect);
//		printcontainer("fvect", fvect);
//		std::cout << svect.capacity() << " = " << fvect.capacity() << std::endl;
//		are_equal_print(svect, fvect);
//
//		sit = svect.begin();				fit = fvect.begin();
//		sit = svect.insert(sit, 200);
//		fit = fvect.insert(fit, 200);
//		printcontainer("svect", svect);
//		printcontainer("fvect", fvect);
//		std::cout << svect.capacity() << " = " << fvect.capacity() << std::endl;
//		are_equal_print(svect, fvect);
//
//		svect.insert(sit, 1, 300);
//		fvect.insert(fit, 1, 300);
//		printcontainer("svect", svect);
//		printcontainer("fvect", fvect);
//		std::cout << svect.capacity() << " = " << fvect.capacity() << std::endl;
//		are_equal_print(svect, fvect);
//
//		// "it" no longer valid, get a new one:
//		sit = svect.begin();				fit = fvect.begin();
//
//		std::vector<int>	svect2(4, 400);		ft::vector<int>	fvect2(4, 400);
//		svect.insert(sit + 2, svect2.begin(), svect2.end());
//		fvect.insert(fit + 2, fvect2.begin(), fvect2.end());
//		printcontainer("svect", svect);
//		printcontainer("fvect", fvect);
//		std::cout << svect.capacity() << " = " << fvect.capacity() << std::endl;
//		are_equal_print(svect, fvect);
//
//		int		myarray[] = { 501, 502, 503 };
//		svect.insert(svect.begin(), myarray, myarray + 3);
//		fvect.insert(fvect.begin(), myarray, myarray + 3);
//		printcontainer("svect", svect);
//		printcontainer("fvect", fvect);
//		std::cout << svect.capacity() << " = " << fvect.capacity() << std::endl;
//		are_equal_print(svect, fvect);
//
//		svect.insert(svect.begin(), svect.begin(), svect.end());
//		fvect.insert(fvect.begin(), fvect.begin(), fvect.end());
//		printcontainer("svect", svect);
//		printcontainer("fvect", fvect);
//		std::cout << svect.capacity() << " = " << fvect.capacity() << std::endl;
//		are_equal_print(svect, fvect);
//
//		svect.insert(svect.end(), svect.begin(), svect.end());
//		fvect.insert(fvect.end(), fvect.begin(), fvect.end());
//		printcontainer("svect", svect);
//		printcontainer("fvect", fvect);
//		std::cout << svect.capacity() << " = " << fvect.capacity() << std::endl;
//		are_equal_print(svect, fvect);
//
//		std::cout << "vector of vectors inserts" << std::endl;
//		std::vector< std::vector<int> >	svv;	ft::vector< ft::vector<int> >	fvv;
//		svv.push_back(svect);					fvv.push_back(fvect);
//		svv.push_back(svect2);					fvv.push_back(fvect2);
//
//		svv.insert(svv.begin(), svv.begin(), svv.end());
//		fvv.insert(fvv.begin(), fvv.begin(), fvv.end());
//#if (__cplusplus < 201103L)	//	tests below fail on linux with c++11 std
//		svv.insert(svv.end() - 1, svv.begin(), svv.end());
//		fvv.insert(fvv.end() - 1, fvv.begin(), fvv.end());
//		svv.insert(svv.end(), svv.begin(), svv.end());
//		fvv.insert(fvv.end(), fvv.begin(), fvv.end());
//#endif
//		svv.erase(svv.begin() + 1, svv.end() - 3);
//		fvv.erase(fvv.begin() + 1, fvv.end() - 3);
//
//		if (svv.size() != fvv.size())
//			error_exception();
//		size_t	cnt(0);
//		for (size_t i = 0; i < svv.size(); i++)
//			are_equal_print(svv.at(i), fvv.at(i), ++cnt);
//		std::cout << std::endl;
//	}
//
//	{
//		std::cout << "-------------" << std::endl;
//		std::vector<int>			svect;	ft::vector<int>				fvect;
//		std::vector<int>::iterator	sit;	ft::vector<int>::iterator	fit;
//
//		// set some values (from 1 to 10)
//		for (int i = 1; i <= 10; i++)
//		{	svect.push_back(i);		fvect.push_back(i);		}
//		printcontainer("svect", svect);
//		printcontainer("fvect", fvect);
//		std::cout << svect.capacity() << " = " << fvect.capacity() << std::endl;
//		are_equal_print(svect, fvect);
//
//		// erase the 6th element
//		sit = svect.erase(svect.begin() + 5);	fit = fvect.erase(fvect.begin() + 5);
//		if (*sit != *fit)
//			error_exception();
//		printcontainer("svect", svect);			printcontainer("fvect", fvect);
//		std::cout << svect.capacity() << " = " << fvect.capacity() << std::endl;
//		are_equal_print(svect, fvect);
//
//		// erase the first 3 elements:
//		svect.erase(svect.begin(), svect.begin() + 3);
//		fvect.erase(fvect.begin(), fvect.begin() + 3);
//		printcontainer("svect", svect);		printcontainer("fvect", fvect);
//		std::cout << svect.capacity() << " = " << fvect.capacity() << std::endl;
//		are_equal_print(svect, fvect);
//
//		svect.erase(svect.end() - 4, svect.end() - 1);
//		fvect.erase(fvect.end() - 4, fvect.end() - 1);
//		printcontainer("svect", svect);		printcontainer("fvect", fvect);
//		std::cout << svect.capacity() << " = " << fvect.capacity() << std::endl;
//		are_equal_print(svect, fvect);
//
//		svect.erase(svect.begin(), svect.end());
//		fvect.erase(fvect.begin(), fvect.end());
//		printcontainer("svect", svect);		printcontainer("fvect", fvect);
//		std::cout << svect.capacity() << " = " << fvect.capacity() << std::endl;
//		are_equal_print(svect, fvect);
//	}
//
//	{
//		std::cout << "--------------" << std::endl;
//		std::vector<std::string>	svect0;	ft::vector<std::string>	fvect0;
//		std::vector<std::string>	svect1;	ft::vector<std::string>	fvect1;
//		printrelationaloperators(svect0, svect1, fvect0, fvect1);
//
//		svect0.push_back("vector");		fvect0.push_back("vector");
//		printrelationaloperators(svect0, svect1, fvect0, fvect1);
//		are_equal_print(svect0, fvect0);
//
//		svect1.push_back("vector");		fvect1.push_back("vector");
//		printrelationaloperators(svect0, svect1, fvect0, fvect1);
//		are_equal_print(svect1, fvect1);
//
//		svect0.push_back("vector2");	fvect0.push_back("vector2");
//		printrelationaloperators(svect0, svect1, fvect0, fvect1);
//		are_equal_print(svect0, fvect0);
//
//		svect1.push_back("vector5");	fvect1.push_back("vector5");
//		printrelationaloperators(svect0, svect1, fvect0, fvect1);
//		are_equal_print(svect1, fvect1);
//
//		std::cout << "member swap:" << std::endl;
//		svect0.swap(svect1);			fvect0.swap(fvect1);
//		printrelationaloperators(svect0, svect1, fvect0, fvect1);
//		are_equal_print(svect0, fvect0);
//		are_equal_print(svect1, fvect1);
//
//		std::cout << "nonmember swap:" << std::endl;
//		swap(svect0, svect1);			swap(fvect0, fvect1);
//		printrelationaloperators(svect0, svect1, fvect0, fvect1);
//		are_equal_print(svect0, fvect0);
//		are_equal_print(svect1, fvect1);
//	}
//
//	{
//		std::cout << "-------------" << std::endl << "vector of vectors" << std::endl;
//		std::vector< std::vector<size_t> >	svect;
//		ft::vector< ft::vector<size_t> >	fvect;
//
//		while (svect.size() < 20)
//		{
//			bool	a(rand() % 10000000);
//			svect.push_back(std::vector<size_t>(20, a));
//			fvect.push_back(ft::vector<size_t>(20, a));
//		}
//
//		svect.erase(svect.begin() + 6, svect.end() - 8);
//		fvect.erase(fvect.begin() + 6, fvect.end() - 8);
//
//		if (svect.size() != fvect.size())
//			error_exception();
//
//		size_t	cnt(0);
//		for (size_t i = 0; i < svect.size(); i++)
//			are_equal_print(svect[i], fvect[i], ++cnt);
//		std::cout << std::endl;
//	}

	std::cout << CLR_GOOD << "vector tests passed" << CLR_RESET << std::endl << std::endl;
}



int	main(int ac, char **av) {
	ft::vector<std::string>		ass;
	ft::vector<std::string>		as(ass);
	ft::vector<std::string>::reverse_iterator it1 = as.rbegin();
	ft::vector<std::string>::const_reverse_iterator it2 = ass.rbegin();




	ft_vector_tests(ac,av);



	return 0;
}