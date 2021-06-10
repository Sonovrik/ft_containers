#pragma once

#include "ReverseIterator.hpp"

namespace ft{


	template<typename T, typename NoneConstPointer>
	class VectorIterator {
	public:
		typedef typename iterator_traits<T>::iterator_category			iterator_category;
		typedef typename iterator_traits<T>::value_type					value_type;
		typedef typename iterator_traits<T>::difference_type			difference_type;
		typedef typename iterator_traits<T>::pointer					pointer;
		typedef typename iterator_traits<T>::reference					reference;

	private:
		pointer _ptr;

	public:
		VectorIterator(): _ptr(NULL) {}

		VectorIterator(VectorIterator const &other): _ptr(other._ptr){}

		template <class Tm>
		VectorIterator(VectorIterator<Tm, NoneConstPointer> const &other,
					   typename ft::check_if_the_same<Tm, NoneConstPointer>* = NULL):
			_ptr(other.operator->()) {}

		VectorIterator(pointer ptr): _ptr(ptr){}

		virtual ~VectorIterator(){}

		VectorIterator	&operator=(VectorIterator const &other){
			if (this != &other)
				this->_ptr = other._ptr;
			return *this;
		}

		VectorIterator &operator++() {
			++this->_ptr;
			return *this;
		}

		VectorIterator operator++(int) {
			VectorIterator tmp(*this);
			++this->_ptr;
			return tmp;
		}

		VectorIterator &operator--() {
			--this->_ptr;
			return *this;
		}

		VectorIterator operator--(int) {
			VectorIterator tmp(*this);
			--this->_ptr;
			return tmp;
		}

		bool	operator==(VectorIterator const &other) const{
			return (this->_ptr == other._ptr);
		}

		bool	operator!=(VectorIterator const &other) const{
			return (this->_ptr != other._ptr);
		}

		reference 	operator*(){
			return *(this->_ptr);
		}

		pointer operator->(){
			return this->_ptr;
		}

		pointer base(){
			return this->_ptr;
		}

		pointer operator->() const{
			return this->_ptr;
		}

		VectorIterator operator+(difference_type n) const{
			VectorIterator tmp(*this);
			tmp += n;
			return tmp;
		}

		VectorIterator operator-(difference_type n) const{
			VectorIterator tmp(*this);
			tmp -= n;
			return tmp;
		}

		difference_type operator-(VectorIterator const &other) const{
			return (this->_ptr - other._ptr);
		}

		bool 	operator<(VectorIterator const &other) const{
			return (this->_ptr < other._ptr);
		}

		bool 	operator>(VectorIterator const &other) const{
			return (this->_ptr > other._ptr);
		}

		bool 	operator<=(VectorIterator const &other) const{
			return (this->_ptr <= other._ptr);
		}

		bool 	operator>=(VectorIterator const &other) const{
			return (this->_ptr <= other._ptr);
		}

		VectorIterator &operator+=(difference_type n){
			this->_ptr += n;
			return *this;
		}

		VectorIterator &operator-=(difference_type n){
			this->_ptr -= n;
			return *this;
		}

		reference operator[](difference_type n){
			return (this->_ptr[n]);
		}

	};


}