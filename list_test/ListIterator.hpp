#pragma once
#include "../support_classes.hpp"
#include <iostream>
#include "list.hpp"

namespace ft{

	template <typename T>
	class ListIterator{
	public:
		typedef T											value_type;
		typedef T&											reference;
		typedef T*											pointer;
		typedef typename std::ptrdiff_t						difference_type;
		typedef node<value_type>							list_node;
		typedef typename std::bidirectional_iterator_tag	iterator_category;


		friend class list<T>;

	private:
		typedef list_node *									node_pointer;
		node_pointer _ptr;


	public:
		ListIterator(): _ptr() {}
		ListIterator(ListIterator const &other) { *this = other; }
		ListIterator(node_pointer node): _ptr(node) {}
		~ListIterator() {}

		ListIterator	&operator=(ListIterator const &other){
			_ptr = other._ptr;
			return *this;
		}

		reference	operator*(){
			return _ptr->_value;
		}

		node_pointer operator->(){
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

		bool	operator!=(ConstListIterator<T> const &other) const{
			return (_ptr != other.getNode());
		}

		node_pointer getNode() const{
			return _ptr;
		}
	};


	template <typename T>
	class ConstListIterator{
	public:
		typedef const T										value_type;
		typedef const T&									reference;
		typedef typename std::ptrdiff_t						difference_type;
		typedef node<value_type>							list_node;
		typedef list_node *									node_pointer;
		typedef typename std::bidirectional_iterator_tag	iterator_category;

	private:
		node_pointer _ptr;


	public:
		ConstListIterator(): _ptr() {}
		ConstListIterator(ConstListIterator const &other) { *this = other; }
		ConstListIterator(ListIterator<T> const &other): _ptr(other.getNode()) {}
		ConstListIterator(node_pointer node): _ptr(node) {}
		~ConstListIterator() {}

		ConstListIterator	&operator=(ConstListIterator const &other){
			if (this != &other)
				_ptr = other._ptr;
			return *this;
		}

		ConstListIterator	&operator=(ListIterator<T> const &other){
			_ptr = other.getNode();
			return *this;
		}

		reference	operator*() const{
			return _ptr->_value;
		}

		node_pointer operator->() const{
			return _ptr;
		}

		ConstListIterator &operator++() {
			_ptr = _ptr->_next;
			return *this;
		}

		ConstListIterator operator++(int) {
			ConstListIterator tmp(*this);
			_ptr = _ptr->_next;
			return tmp;
		}

		ConstListIterator &operator--() {
			_ptr = _ptr->_prev;
			return *this;
		}

		ConstListIterator operator--(int) {
			ConstListIterator tmp(*this);
			_ptr = _ptr->_prev;
			return tmp;
		}

		bool	operator==(ConstListIterator const &other) const{
			return (_ptr == other._ptr);
		}

		bool	operator!=(ConstListIterator const &other) const{
			return (_ptr != other._ptr);
		}

		node_pointer getNode() const{
			return _ptr;
		}
	};

}