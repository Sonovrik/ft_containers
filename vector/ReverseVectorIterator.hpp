
#include <iostream>
//#include "VectorIterator.hpp"
// inheritance VectorIterator
namespace ft{

	template<typename T>
	class ReverseVectorIterator {
	public:

		typedef T value_type;
		typedef size_t size_type;
		typedef  value_type& reference;
		typedef  const value_type& const_reference;
		typedef  value_type * pointer;
		typedef  value_type const * const_pointer;
		typedef typename std::ptrdiff_t difference_type;

	private:
		pointer _ptr;

	public:
		ReverseVectorIterator(): _ptr(NULL) {}

		ReverseVectorIterator(ReverseVectorIterator const &other): _ptr(other._ptr){}

		ReverseVectorIterator(pointer ptr): _ptr(ptr){}

		virtual ~ReverseVectorIterator(){}

		reference 	operator*(){
			return *this->_ptr;
		}

		const_reference	operator*() const{
			return *this->_ptr;
		}

		ReverseVectorIterator operator+(difference_type n) const{
			ReverseVectorIterator tmp(*this);
			tmp -= n;
			return tmp;
		}

		ReverseVectorIterator operator-(difference_type n) const{
			ReverseVectorIterator tmp(*this);
			tmp += n;
			return tmp;
		}

		ReverseVectorIterator &operator++() {
			this->_ptr--;
			return *this;
		}

		ReverseVectorIterator operator++(int) {
			ReverseVectorIterator tmp(*this);
			this->_ptr--;
			return tmp;
		}

		ReverseVectorIterator &operator--() {
			this->_ptr++;
			return *this;
		}

		ReverseVectorIterator operator--(int) {
			ReverseVectorIterator tmp(*this);
			this->_ptr++;
			return tmp;
		}

		ReverseVectorIterator &operator+=(difference_type n){
			this->_ptr -= n;
			return *this;
		}

		ReverseVectorIterator &operator-=(difference_type n){
			this->_ptr += n;
			return *this;
		}

		pointer operator->(){
			return this->_ptr;
		}

		const_pointer operator->() const{
			return this->_ptr;
		}

		reference operator[](difference_type n){
			return *(this->_ptr - n);
		}

		const_reference operator[](difference_type n) const{
			return *(this->_ptr - n);
		}
	};


}