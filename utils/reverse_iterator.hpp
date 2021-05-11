#include "utils.hpp"
#include <iostream>
#include "list.hpp"
#include <memory>

namespace ft{


	template <typename T>
	class ReverseListIterator: public bidirectional_iterator_tag {

	public:

		friend class list<T>;

		typedef T							value_type;
		typedef value_type&					reference;
		typedef const value_type&			const_reference;
		typedef Node<T>*					pointer;
		typedef Node<T> const *				const_pointer;
		typedef typename std::ptrdiff_t		difference_type;

		ReverseListIterator(): _ptr(NULL){}
		ReverseListIterator(ReverseListIterator const &other): _ptr(other._ptr){}
		ReverseListIterator(pointer ptr): _ptr(ptr){}
		~ReverseListIterator(){}

		ReverseListIterator	&operator=(ReverseListIterator const &other){
			if (this != &other)
				this->_ptr = other._ptr;
			return *this;
		}

		ReverseListIterator &operator++() {
			this->_ptr = this->_ptr->_prev;
			return *this;
		}

		ReverseListIterator operator++(int) {
			ReverseListIterator tmp(*this);
			this->_ptr = this->_ptr->_prev;
			return tmp;
		}

		ReverseListIterator &operator--() {
			this->_ptr = this->_ptr->_next;
			return *this;
		}

		ReverseListIterator operator--(int) {
			ReverseListIterator tmp(*this);
			this->_ptr = this->_ptr->_next;
			return tmp;
		}

		bool	operator==(ReverseListIterator const &other) const{
			return (this->_ptr == other._ptr);
		}

		bool	operator!=(ReverseListIterator const &other) const{
			return (this->_ptr != other._ptr);
		}

		reference 	operator*(){
			return this->_ptr->_value;
		}

		pointer operator->(){
			return this->_ptr;
		}

		pointer operator->() const{
			return this->_ptr;
		}


	private:
		pointer _ptr;
	};
}