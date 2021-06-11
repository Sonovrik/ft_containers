
#pragma once

namespace ft{



	template <class Iterator>
	class iterator_traits{
	public:
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template <class T>
	class iterator_traits <T*>{
	public:
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	template<class T>
	class iterator_traits<const T*> {
	public:
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template <class, class>
	class check_if_the_same {};

	template <class T>
	class check_if_the_same<T, T>{
		typedef T type;
	};

	template <bool B, class T = void>
	struct enable_if { };

	template <class T>
	struct enable_if<true, T> { typedef T type; };

	template <class Arg1, class Arg2, class Result>
	struct binary_function {
		typedef Arg1	first_argument_type;
		typedef Arg2	second_argument_type;
		typedef Result	result_type;
	};

	template <class T1, class T2>
	struct _less_twotypes	: binary_function<T1, T2, bool> {
		bool	operator()(const T1& x, const T2& y) const
		{	return (x < y);		}
	};

	template <class T1, class T2>
	struct _equal_twotypes	: binary_function<T1, T2, bool> {
		bool	operator()(const T1& x, const T2& y) const
		{	return (x == y);	}
	};

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								 InputIterator2 first2, InputIterator2 last2, Compare comp){
		while (first1 != last1){
			if (first2 == last2 || comp(*first2, *first1))
				return false;
			else if (comp(*first1, *first2))
				return true;
			++first1;
			++first2;
		}
		return first2 != last2;
	}

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								 InputIterator2 first2, InputIterator2 last2){
		typedef typename ft::iterator_traits<InputIterator1>::value_type type1;
		typedef typename ft::iterator_traits<InputIterator2>::value_type type2;
		return (ft::lexicographical_compare(first1, last1, first2, last2, _less_twotypes<type1, type2>()));
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1 != last1){
			if (!pred(*first1, *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		typedef typename ft::iterator_traits<InputIterator1>::value_type type1;
		typedef typename ft::iterator_traits<InputIterator2>::value_type type2;
		return (ft::equal(first1, last1, first2, ft::_equal_twotypes<type1, type2>()));
	}

}


