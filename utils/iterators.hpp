
#include <iostream>
#include "./utils.hpp"

namespace ft {


	class bidirectional_iterator_tag { };

	template<typename T>
	class ListIterator : public bidirectional_iterator_tag {

	public:
		typedef T					value_type;
		typedef value_type*			pointer;
		typedef value_type const *	const_pointer;
		typedef value_type &		reference;
		typedef value_type const &	const_reference;
		typedef Node<T>				node;
		typedef node*				node_pointer;


	private:
		node_pointer	_ptr;


	public:
		ListIterator(): _ptr(NULL){}
		ListIterator(ListIterator const &other): _ptr(other._ptr){}
		~ListIterator(){}

		ListIterator	&operator=(ListIterator const &other){
			if (this != &other)
				this->_ptr = other._ptr;
			return NULL;
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

		bool	operator==(ListIterator const &other){
			return (this->_ptr == other._ptr); // ???
		}

		bool	operator!=(ListIterator<T> const &other){
			return (this->_ptr != other._ptr); // ???
		}

		bool 	operator*(ListIterator<T> const &other){}

	};



};