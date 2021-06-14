#pragma once
#include "../support_classes.hpp"
#include <iostream>

namespace ft{

	template <typename T, typename Pointer, typename Reference>
	class ListIterator{
	public:
		typedef T											value_type;
		typedef Reference									reference;
		typedef Pointer										pointer;
		typedef typename std::ptrdiff_t						difference_type;
		typedef node<value_type>							list_node;

		typedef typename std::bidirectional_iterator_tag	iterator_category;

	private:
		list_node *_ptr;

	public:
		ListIterator(): _ptr() {}
		ListIterator(ListIterator const &other): _ptr(other._ptr) {}
		ListIterator(list_node *node): _ptr(node) {}
		~ListIterator() {}

		ListIterator	&operator=(ListIterator const &other){
			if (this != &other)
				_ptr = other._ptr;
			return *this;
		}

		reference	operator*(){
			return _ptr->_value;
		}

		list_node *operator->(){
			return _ptr;
		}

		ListIterator &operator++() {
			_ptr = _ptr->_next;
			return *this;
		}

		ListIterator operator++(int) {
			ListIterator tmp(*this);
			_ptr = _ptr->_next;
			return tmp;
		}

		ListIterator &operator--() {
			_ptr = _ptr->_prev;
			return *this;
		}

		ListIterator operator--(int) {
			ListIterator tmp(*this);
			_ptr = _ptr->_prev;
			return tmp;
		}

		bool	operator==(ListIterator const &other) const{
			return (_ptr == other._ptr);
		}

		bool	operator!=(ListIterator const &other) const{
			return (_ptr != other._ptr);
		}
	};
}