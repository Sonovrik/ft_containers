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
		typedef VectorIterator<pointer, pointer>			iterator;
		typedef ReverseIterator<iterator>					reverse_iterator;
		typedef VectorIterator<const_pointer, pointer>		const_iterator;
		typedef ReverseIterator<const_iterator>				const_reverse_iterator;

		explicit vector(const allocator_type& alloc = allocator_type()):
			_allocator(alloc),
			_size(0),
			_guaranteed_capacity(0),
			_root(NULL) {}

		explicit vector(size_type n, const value_type& val = value_type(),
						 const allocator_type& alloc = allocator_type()):
						 _allocator(alloc),
						 _size(0),
						 _guaranteed_capacity(0),
						 _root(NULL){
			this->assign(n, val);
		}

		template <class InputIterator>
		vector(InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type(),
				typename enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type * = NULL):
				_allocator(alloc),
				_size(0),
				_guaranteed_capacity(0),
				_root(NULL){
			this->reserve(last - first);
			while (first != last){
				this->push_back(*first);
				++first;
			}
		}

		vector(const vector& x):
			_allocator(x._allocator),
			_size(0),
			_guaranteed_capacity(0),
			_root(nullptr){
			this->reserve(x._guaranteed_capacity);
			for (const_iterator it = x.begin(); it != x.end(); ++it)
				this->push_back(*it);
		}

		vector& operator=(const vector& x){
			if (this != &x) {
				this->clear();
				if (this->_guaranteed_capacity < x.size()){
					this->_allocator.deallocate(this->_root, this->_guaranteed_capacity);
					this->_root = this->_allocator.allocate(x.size());
					this->_guaranteed_capacity = x.size();
				}
				for (size_type i = 0; i < x.size(); ++i)
					push_back(x[i]);
			}
			return *this;
		}


		~vector(){
			if (this->_guaranteed_capacity != 0){
				for (size_type i = 0; i < this->_size; ++i)
					this->_allocator.destroy(&this->_root[i]);
				this->_allocator.deallocate(this->_root, this->_guaranteed_capacity);
			}
		}

		//Iterators
		iterator begin(){
			return iterator(&this->_root[0]);
		}

		const_iterator begin() const{
			return const_iterator(&this->_root[0]);
		}

		reverse_iterator rbegin(){
			return reverse_iterator(end());
		}

		const_reverse_iterator rbegin() const{
			return const_reverse_iterator(end());
		}

		iterator end(){
			return iterator(&this->_root[this->_size]);
		}

		const_iterator end() const{
			return const_iterator(&this->_root[this->_size]);
		}

		reverse_iterator rend(){
			return reverse_iterator(this->begin());
		}

		const_reverse_iterator rend() const{
			return const_reverse_iterator(this->begin());
		}

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
				throw std::length_error("vector::reserve");
			size_type newSize = n;
			pointer tmp = this->_allocator.allocate(newSize);

			for (size_type i = 0; i < this->_size; ++i){
				this->_allocator.construct(tmp + i, this->_root[i]);
				this->_allocator.destroy(&this->_root[i]);
			}
			this->_allocator.deallocate(this->_root, this->_size);
			this->_root = tmp;
			this->_guaranteed_capacity = newSize;
		}

		void resize(size_type n, value_type val = value_type()){
			if (n > this->_size){
				if (n > this->max_size())
					throw std::bad_array_new_length();
				if (n > this->_guaranteed_capacity)
					reserve(n);
				for (size_type i = this->_size; i < n; ++i)
					this->push_back(val);
			}
			else if (n < this->size()){
				for (size_type i = this->size(); i > n; --i)
					pop_back();
			}
		}


		//Element access
		reference operator[](size_type n){
			return this->_root[n];
		}

		const_reference operator[](size_type n) const{
			return this->_root[n];
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
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last,
					typename enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type * = NULL){
			clear();
			this->reserve(last - first);
			while (first != last){
				push_back(*first);
				++first;
			}
		}

		void assign(size_type n, const value_type& val){
			clear();
			this->reserve(n);
			for (size_type i = 0; i < n; ++i)
				push_back(val);
		}

		void push_back(const value_type& val){
			if (this->_size == this->_guaranteed_capacity){
				if (!this->_guaranteed_capacity)
					this->reserve(1);
				else{
					if (this->_guaranteed_capacity * 2 > this->max_size())
						throw std::bad_array_new_length();
					this->reserve(this->_guaranteed_capacity * 2);
				}
			}
			this->_allocator.construct(this->_root + this->_size, val);
			++this->_size;
		}

		void pop_back(){
			if (this->_size){
				this->_allocator.destroy(&this->_root[this->size() - 1]);
				--this->_size;
			}
		}

		iterator insert(iterator position, const value_type& val){
			return this->__insert(position, 1, val);
		}

		void insert(iterator position, size_type n, const value_type& val){
			this->__insert(position, n, val);
		}

		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last){
			vector tmp(first, last);
			for (size_type i = 0; i < tmp.size(); ++i){
				position = this->__insert(position, 1, tmp.at(i));
				++position;
			}
		}

		iterator erase(iterator position){
			this->_allocator.destroy(position.base());

			iterator it = position;
			while (it != this->end()) {
				this->_allocator.construct(it.base(), *(it + 1));
				this->_allocator.destroy(it.base() + 1);
				++it;
			}
			--this->_size; // when position == end it's incorrect but it's UB
			return position;
		}

		iterator erase(iterator first, iterator last){
			difference_type range = last - first;
			if (range <= 0)
				return first;

			iterator it = first;
			while (it != last){
				this->_allocator.destroy(it.base());
				++it;
			}
			while (it != this->end()){
				this->_allocator.construct(((it - range).base()), *it);
				this->_allocator.destroy(it.base());
				++it;
			}
			this->_size -= range;
			return first;
		}

		void clear(){
			while (this->_size != 0)
				this->pop_back();
		}

		void swap(vector& x){
			size_type tmp_size = this->_size;
			size_type tmp_capacity = this->_guaranteed_capacity;
			pointer tmp_root = this->_root;

			this->_size = x._size;
			this->_guaranteed_capacity = x._guaranteed_capacity;
			this->_root = x._root;

			x._size = tmp_size;
			x._guaranteed_capacity = tmp_capacity;
			x._root = tmp_root;
		}

	private:
		allocator_type			_allocator;
		size_type				_size;
		size_type				_guaranteed_capacity;
		pointer					_root;

		iterator __insert(iterator position, size_type n, const value_type& val){
			if (n == 0)
				return position;
			iterator iter = position;
			size_type newSize = this->_size + n;
			if (this->_guaranteed_capacity < newSize) {
				if (this->_guaranteed_capacity * 2 > newSize)
					newSize = this->_guaranteed_capacity  * 2;
				vector tmp;
				tmp.reserve(newSize);
				iterator it = this->begin();
				while (it != position){
					tmp.push_back(*it);
					++it;
				}
				iter = tmp.end();
				for (size_type i = 0; i < n; ++i)
					tmp.push_back(val);
				while (it != this->end()){
					tmp.push_back(*it);
					++it;
				}
				this->swap(tmp);
			}
			else{
				iterator it = this->end();
				while (it != position){
					--it;
					this->_allocator.construct(it.base() + n, *it);
					this->_allocator.destroy(it.base());
				}
				for (size_type i = 0; i < n; ++i){
					this->_allocator.construct(it.base(), val);
					++it;
					++this->_size;
				}
			}
			return iter;
		}

	};

	template <class T, class Alloc>
	bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
		typename  vector<T, Alloc>::size_type sz = lhs.size();
		return (sz == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
		return !(lhs == rhs);
	}

	template <class T, class Alloc>
	bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
		return !(rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
		return !(lhs < rhs);
	}

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y){
		x.swap(y);
	}

}