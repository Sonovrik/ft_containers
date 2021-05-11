
#include <iostream>
#include "./utils.hpp"
#include "list.hpp"
#include <memory>

namespace ft {

	template<typename T>
	class ConstReverseListIterator : public bidirectional_iterator_tag {

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
		ConstReverseListIterator(): _ptr(NULL){}
		ConstReverseListIterator(const ReverseListIterator<T>	&other): _ptr(other.operator->()){}
		ConstReverseListIterator(const ConstReverseListIterator		&other): _ptr(other._ptr){}
		ConstReverseListIterator(pointer ptr): _ptr(ptr){}
		~ConstReverseListIterator(){}

		ConstReverseListIterator	&operator=(ConstReverseListIterator const &other){
			if (this != &other)
				this->_ptr = other._ptr;
			return *this;
		}

		ConstReverseListIterator &operator++() {
			this->_ptr = this->_ptr->_prev;
			return *this;
		}

		ConstReverseListIterator operator++(int) {
			ConstReverseListIterator tmp(*this);
			this->_ptr = this->_ptr->_prev;
			return tmp;
		}

		bool	operator==(ConstReverseListIterator const &other) const{
			return (this->_ptr == other._ptr); // ???
		}

		bool	operator!=(ConstReverseListIterator const &other) const{
			return (this->_ptr != other._ptr); // ???
		}

		const_reference 	operator*() const{
			return *(this->_ptr->_value);
		}

		ConstReverseListIterator &operator--() {
			this->_ptr = this->_ptr->_next;
			return *this;
		}

		ConstReverseListIterator operator--(int) {
			ConstReverseListIterator tmp(*this);
			this->_ptr = this->_ptr->_next;
			return tmp;
		}

		bool	operator!=(ConstReverseListIterator const &other){
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