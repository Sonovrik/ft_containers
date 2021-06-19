#pragma once

#include <iostream>

namespace ft{

	// iterator traits. It needs for types iterators ( const or simple )
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


	// check types ( const of non const ). Need it for vector iterator. For others it doesn't work.
	template <class, class>
	struct check_if_the_same {};

	template <class T>
	struct check_if_the_same<T, T>{
		typedef T type;
	};

	// Need it for ambiguous methods
	template <bool B, class T = void>
	struct enable_if { };

	template <class T>
	struct enable_if<true, T> { typedef T type; };


	// Rule that creates a typedefs
	template <class Arg1, class Arg2, class Result>
	struct binary_function {
		typedef Arg1	first_argument_type;
		typedef Arg2	second_argument_type;
		typedef Result	result_type;
	};


	// Rule that compares which type is the smallest
	template <class T1, class T2>
	struct _less_twotypes	: binary_function<T1, T2, bool> {
		bool	operator()(const T1& x, const T2& y) const
		{	return (x < y);		}
	};

	// Rule that compares which value is the smallest
	template <class T>
	struct _less_compration : binary_function<T, T, bool> {
		bool	operator()(const T& x, const T& y) const
		{	return (x < y);		}
	};

	// Rule that compares whether they are equal
	template <class T>
	struct _equal_compration : binary_function<T, T, bool> {
		bool	operator()(const T& x, const T& y) const
		{	return (x == y);		}
	};

	// Rule that check equality comparison for
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
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred) {
		while (first1 != last1){
			if (!pred(*first1, *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
		typedef typename ft::iterator_traits<InputIterator1>::value_type type1;
		typedef typename ft::iterator_traits<InputIterator2>::value_type type2;
		return (ft::equal(first1, last1, first2, ft::_equal_twotypes<type1, type2>()));
	}

	template< typename S >
	void	itemswap(S& var1, S& var2) {
		S tmpvar = var1;
		var1 = var2;
		var2 = tmpvar;
	}

	template <class T>
	struct node {
		T				_value;
		node			*_next;
		node			*_prev;
	};

	template <class Key, class T>
	struct __base{
	private:
		typedef std::pair<const Key, T>						value_type;
		typedef __base<Key, T>						map_node;

		__base(): parent(NULL), left(NULL), right(NULL), isRed(false) {}

	public:
		value_type		data;
		map_node		*parent;
		map_node		*left;
		map_node		*right;
		bool 			isRed;

		__base(map_node* nill, const value_type& data):
		data(data),
		parent(nill),
		left(nill),
		right(nill),
		isRed(false) {}
	};

	template <class K, class T>
	__base<K, T>* 	get_min(__base<K, T>* node, const __base<K, T>* nill){
		while (node != nill && node->left != nill)
			node = node->left;
		return node;
	}

	template <class K, class T>
	__base<K, T>* 	get_max(__base<K, T>* node, const __base<K, T>* nill){
		while (node != nill && node->right != nill)
			node = node->right;
		return node;
	}
}


