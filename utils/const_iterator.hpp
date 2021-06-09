
#include <iostream>
#include "./utils.hpp"
#include "list.hpp"
#include <memory>

namespace ft {


	template<typename T>
	class ConstListIterator : public bidirectional_iterator_tag {

	public:

		friend class list<T>;

		typedef const T					value_type;
		typedef value_type&				reference;
		typedef const value_type&		const_reference;
		typedef Node<T>*				pointer;
		typedef Node<T>const *			const_pointer;
		typedef typename std::ptrdiff_t	difference_type;


	private:
		pointer		_ptr;


	public:
		ConstListIterator(): _ptr(NULL){}
		ConstListIterator(const ListIterator<T>	&other): _ptr(other.operator->()){}
		ConstListIterator(const ConstListIterator		&other): _ptr(other._ptr){}
		ConstListIterator(pointer ptr): _ptr(ptr){}
		~ConstListIterator(){}

		ConstListIterator	&operator=(ConstListIterator const &other){
			if (this != &other)
				this->_ptr = other._ptr;
			return *this;
		}

		ConstListIterator &operator++() {
			this->_ptr = this->_ptr->_next;
			return *this;
		}

		ConstListIterator operator++(int) {
			ConstListIterator tmp(*this);
			this->_ptr = this->_ptr->_next;
			return tmp;
		}

		bool	operator==(ConstListIterator const &other) const{
			return (this->_ptr == other._ptr); // ???
		}

		bool	operator!=(ConstListIterator const &other) const{
			return (this->_ptr != other. _ptr); // ???
		}

		const_reference 	operator*() const{
			return (this->_ptr->_value);
		}

		ConstListIterator &operator--() {
			this->_ptr = this->_ptr->_prev;
			return *this;
		}

		ConstListIterator operator--(int) {
			ConstListIterator tmp(*this);
			this->_ptr = this->_ptr->_prev;
			return tmp;
		}

		bool	operator!=(ConstListIterator const &other){
			return (this->_ptr != other._ptr);
		}

		pointer operator->(){
			return this->_ptr;
		}

		pointer operator->() const{
			return this->_ptr;
		}

	};

};