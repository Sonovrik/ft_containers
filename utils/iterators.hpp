#pragma once

#include <iostream>
#include "utils.hpp"
#include "list.hpp"
#include <memory>

namespace ft {


	template<typename T>
	class ListIterator : public bidirectional_iterator_tag {

	public:

		friend class list<T>;

		typedef T							value_type;
		typedef value_type&					reference;
		typedef const value_type&			const_reference;
		typedef Node<T>*					pointer;
		typedef Node<T> const *				const_pointer;
		typedef typename std::ptrdiff_t		difference_type;

	private:
		pointer	_ptr;


	public:
		ListIterator(): _ptr(NULL){}
		ListIterator(ListIterator const &other): _ptr(other._ptr){}
		ListIterator(pointer ptr): _ptr(ptr){}
		~ListIterator(){}

		ListIterator	&operator=(ListIterator const &other){
			if (this != &other)
				this->_ptr = other._ptr;
			return *this;
		}

		ListIterator &operator++() {
			this->_ptr = this->_ptr->_next;
			return *this;
		}

		ListIterator operator++(int) {
			ListIterator tmp(*this);
			this->_ptr = this->_ptr->_next;
			return tmp;
		}

		ListIterator &operator--() {
			this->_ptr = this->_ptr->_prev;
			return *this;
		}

		ListIterator operator--(int) {
			ListIterator tmp(*this);
			this->_ptr = this->_ptr->_prev;
			return tmp;
		}

		bool	operator==(ListIterator const &other) const{
			return (this->_ptr == other._ptr);
		}

		bool	operator!=(ListIterator const &other) const{
			return (this->_ptr != other._ptr);
		}

		reference 	operator*(){
			return this->_ptr->_value;
		}

		pointer operator->(){
			return this->_ptr;
		}

		const_reference	operator*() const{
			return *this->_ptr;
		}

		pointer operator->() const{
			return this->_ptr;
		}
	};



};