#pragma once
#include "../support_classes.hpp"
#include <iostream>
#include "list.hpp"

namespace ft{

	template <typename T, typename Pointer, typename Reference>
	class ListIterator {
	public:
		typedef T										value_type;
		typedef Pointer									pointer;
		typedef Reference								reference;
		typedef node<T>									list_node;
		typedef node<T>*								node_pointer;
		typedef ListIterator<T, T*, T&>					iterator;
		typedef typename std::bidirectional_iterator_tag	iterator_category;
		typedef typename std::ptrdiff_t						difference_type;


		node_pointer _ptr;

		ListIterator(): _ptr(NULL) {};

		ListIterator(const node_pointer ptr): _ptr(ptr) {}

		ListIterator(const iterator &other) { *this = other;}

		~ListIterator() {}

		ListIterator &operator=(const iterator &other) {
			_ptr = other._ptr;
			return *this;
		}

		reference operator*() const {
			return _ptr->_value;
		}

		ListIterator &operator++(){
			_ptr = _ptr->_next;
			return *this;
		}

		ListIterator  operator++(int) {
			ListIterator tmp = *this;
			_ptr = _ptr->_next;
			return tmp;
		}

		ListIterator &operator--() {
			_ptr = _ptr->_prev;
			return *this;
		}

		ListIterator  operator--(int) {
			ListIterator tmp = *this;
			_ptr = _ptr->_prev;
			return tmp;
		}

		pointer operator->() const {
			return &(_ptr->_value);
		}

		bool operator==(const ListIterator &other) const {
			return (_ptr == other._ptr);
		}

		bool operator!=(const ListIterator &other) const {
			return (_ptr != other._ptr);
		}

		template <class _T, class _Tp, class Tr>
		bool operator==(const ListIterator<_T, _Tp, Tr> &other) const {
			return (_ptr == other._ptr);
		}

		template <class _T, class _Tp, class Tr>
		bool operator!=(const ListIterator<_T, _Tp, Tr> &other) const {
			return _ptr != other._ptr;
		}

	};

}