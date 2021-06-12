#pragma once
#include "../support_classes.hpp"

namespace ft{

	template<typename T, typename NoneConstPointer>
	class VectorIterator {
	public:
		typedef typename std::random_access_iterator_tag				iterator_category;
		typedef typename iterator_traits<T>::value_type					value_type;
		typedef typename iterator_traits<T>::difference_type			difference_type;
		typedef typename iterator_traits<T>::pointer					pointer;
		typedef typename iterator_traits<T>::reference					reference;

	private:
		pointer _ptr;

	public:
		VectorIterator(): _ptr(pointer()) {}

		VectorIterator(VectorIterator const &other): _ptr(other._ptr){}

		explicit VectorIterator(const pointer ptr): _ptr(ptr){}

		template <class Tm>
		VectorIterator(VectorIterator<Tm, NoneConstPointer> const &other,
					   typename ft::check_if_the_same<Tm, NoneConstPointer>::type * check = NULL):
			_ptr(other.base()) { (void)check;}

		virtual ~VectorIterator(){}

		VectorIterator	&operator=(VectorIterator const &other){
			if (this != &other)
				this->_ptr = other._ptr;
			return *this;
		}

		pointer base() const{
			return this->_ptr;
		}

		friend
		bool	operator==(VectorIterator const &x, VectorIterator const &y){
			return (x._ptr == y._ptr);
		}

		friend
		bool	operator!=(const VectorIterator  &x, const VectorIterator  &y){
			return (x._ptr != y._ptr);
		}

		reference	operator*() const{
			return *(this->_ptr);
		}

		reference	operator[](difference_type n) const{
			return this->_ptr[n];
		}

		pointer		operator->() const{
			return this->_ptr;
		}

		VectorIterator	&operator++(){
			++this->_ptr;
			return *this;
		}

		VectorIterator	operator++(int){
			VectorIterator tmp = *this;
			++(*this);
			return tmp;
		}

		VectorIterator	&operator--(){
			--this->_ptr;
			return *this;
		}

		VectorIterator	operator--(int){
			VectorIterator tmp = *this;
			--(*this);
			return tmp;
		}

//			a + n
		VectorIterator	operator+(difference_type n) const{
			return VectorIterator(this->_ptr + n);
		}

//			n + a
		friend
		VectorIterator	operator+(difference_type n, const VectorIterator &x) {
			return x + n;
		}

//			a - n
		VectorIterator	operator-(difference_type n) const{
			return VectorIterator(this->_ptr - n);
		}

//			a - b
		friend
		difference_type operator-(const VectorIterator &x, const VectorIterator &y){
			return x._ptr - y._ptr;
		}

//			a += n
		VectorIterator	&operator+=(difference_type n){
			this->_ptr += n;
			return *this;
		}

//			a -= n
		VectorIterator	&operator-=(difference_type n){
			this->_ptr -= n;
			return *this;
		}

		friend
		bool	operator<(const VectorIterator &x, const VectorIterator &y){
			return x._ptr < y._ptr;
		}

		friend
		bool	operator>(const VectorIterator &x, const VectorIterator &y){
			return x._ptr > y._ptr;
		}

		friend
		bool	operator<=(const VectorIterator &x, const VectorIterator &y){
			return x._ptr <= y._ptr;
		}

		friend
		bool	operator>=(const VectorIterator &x, const VectorIterator &y){
			return x._ptr >= y._ptr;
		}

	};


}