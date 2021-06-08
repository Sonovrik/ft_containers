#pragma once
#include <iostream>
#include "VectorIterator.hpp"
#include "ReverseIterator.hpp"

namespace ft{

	template < class T, class Alloc = std::allocator<T> >
	class vector{
	public:
		typedef T											value_type;
		typedef size_t										size_type;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename std::ptrdiff_t						difference_type;
		typedef VectorIterator<T>							iterator;
		typedef ReverseIterator<iterator>					reverse_iterator;
//		typedef const VectorIterator<T>  const_iterator;
//		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

		explicit vector(const allocator_type& alloc = allocator_type()):
			_allocator(alloc),
			_size(0),
			_guaranteed_capacity(1),
			_root(nullptr){
			this->_root = this->_allocator.allocate(this->_guaranteed_capacity);
		}

		vector& operator=(const vector& x){
			this->clear();
			this->_allocator = x._allocator;
			this->_size = x._size;
			this->_guaranteed_capacity = x._guaranteed_capacity;
			this->_root = this->_allocator.allocate(this->_guaranteed_capacity);
			for (size_type i = 0; i < this->size(); ++i)
				this->_root[i] = x._root[i];
		}


		~vector(){
			if (!this->empty()){
				for (size_type i = 0; i < this->_size; ++i)
					this->_allocator.destroy(&this->_root[i]);
				this->_allocator.deallocate(this->_root, this->_size);
			}
		}

		//Iterators
		iterator begin(){
			return iterator(&this->_root[0]);
		}

//		const_iterator begin() const{
//			return const_iterator(&this->_root[0]);
//		}

		reverse_iterator rbegin(){
			return reverse_iterator(iterator(&this->_root[this->_size - 1]));
		}

//		const_iterator rbegin() const{
//			return const_iterator(&this->_root[0]);
//		}


		iterator end(){
			return iterator(this->_root[this->_size - 1]);
		}

//		const_iterator end() const{
//			return const_iterator(this->_root[this->_size - 1]);
//		}

		reverse_iterator rend(){
			return reverse_iterator(iterator(this->_root[0]));
		}

//		reverse_iterator rend() const{
//			return const_iterator(this->_root[this->_size - 1]);
//		}

		//Capacity
		size_type max_size() const{
			return (size_type(-1) / sizeof(value_type));
		}

		size_type size() const{
			return this->_size;
		}

		size_type capacity() const{
			return this->_guaranteed_capacity;
		}

		bool empty() const{
			return !this->_size;
		}

		void reserve(size_type n){
			if (n <= this->_guaranteed_capacity)
				return;
			if (n > this->max_size())
				throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
			size_type newSize = n;
			pointer tmp = this->_allocator.allocate(newSize);

			for (size_type i = 0; i < this->_size; ++i){
				tmp[i] = this->_root[i];
				this->_allocator.destroy(&this->_root[i]);
			}
			this->_allocator.deallocate(this->_root, this->_size);
			this->_root = tmp;
			this->_guaranteed_capacity = newSize;
		}

		void resize(size_type n, value_type val = value_type()){
			if (n > this->_size){
				this->reserve(n);
				for (size_type i = this->_size; i < n; i++)
					this->push_back(val);
			}
			else if (n < this->size()){
				for (size_type i = this->size(); i > n; --i)
					pop_back();
			}
		}


		//Element access
		reference operator[](size_type n){
			return (this->_root[n]);
		}

		const_reference operator[](size_type n) const{
			return (this->_root[n]);
		}


		reference at(size_type n){
			if (n >= this->_size)
				throw std::out_of_range("vector");
			return this->_root[n];
		}

		const_reference at(size_type n) const{
			if (n >= this->_size)
				throw std::out_of_range("vector");
			return this->_root[n];
		}

		reference front(){
			return this->_root[0];
		}

		const_reference front() const{
			return this->_root[0];
		}

		reference back(){
			return this->_root[this->_size - 1];
		}

		const_reference back() const{
			return this->_root[this->_size - 1];
		}

		// Modifiers
		void push_back(const value_type& val){
			if (this->_size < this->_guaranteed_capacity){
				this->_allocator.construct(&this->_root[this->_size], val);
				++this->_size;
			}
			else {
				size_type newSize = this->_guaranteed_capacity * 2;
				if (this->max_size() < newSize)
					throw std::bad_array_new_length();

				pointer tmp = this->_allocator.allocate(newSize);

				for (size_type i = 0; i < this->_size; ++i){
					tmp[i] = this->_root[i];
					this->_allocator.destroy(&this->_root[i]);
				}
				tmp[this->_size] = val;
				this->_allocator.deallocate(this->_root, this->_size);
				this->_root = tmp;
				++this->_size;
				this->_guaranteed_capacity = newSize;
			}
		}

		void pop_back(){
			this->_allocator.destroy(&this->_root[this->size() - 1]);
			--this->_size;
		}

		void clear(){
			if (!this->empty()){
				for (size_type i = 0; i < this->_size; ++i)
					this->_allocator.destroy(&this->_root[i]);
				this->_allocator.deallocate(this->_root, this->_size);
				this->_size = 0;
			}
		}

		void swap(vector& x){
			pointer tmp = this->_root;
			this->_root = x._root;
			x._root = tmp;
		}

		void assign(size_type n, const value_type& val){
			this->clear();
			this->resize(n, val);
		}

		//		template <class InputIterator>
//		void assign (InputIterator first, InputIterator last);

//		iterator insert (iterator position, const value_type& val);

//		void insert (iterator position, size_type n, const value_type& val);

//		template <class InputIterator>
//				void insert (iterator position, InputIterator first, InputIterator last);

//		iterator erase (iterator position);

//		iterator erase (iterator first, iterator last);

	private:
		allocator_type _allocator;
		size_type _size;
		size_type _guaranteed_capacity;
		pointer _root;
	};

}