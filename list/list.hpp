#pragma once

#include <iostream>
#include "utils.hpp"

namespace ft {

	template<class T>
	class ListIterator;
	template<class T>
	class ConstListIterator;
	template<class T>
	class ReverseListIterator;
	template<class T>
	class ConstReverseListIterator;

	template <bool B, class T = void>
	struct enable_if { };

	template <class T>
	struct enable_if<true, T> { typedef T type; };

	template <class T, class Alloc = std::allocator<T> >
	class list {
	public:

		typedef Alloc allocator_type;
		typedef T value_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef ListIterator<T> iterator;
		typedef ConstListIterator<T> const_iterator;
		typedef ReverseListIterator<T> reverse_iterator;
		typedef ConstReverseListIterator<T> const_reverse_iterator;
		typedef typename std::ptrdiff_t difference_type;
		typedef size_t size_type;

		typedef std::allocator<Node<value_type> > nodeAllocator_t;

		explicit list(const allocator_type &alloc = allocator_type()) :
				_allocator(alloc),
				_size(0) {
			this->_root = this->_nodeAllocator.allocate(1);
			this->_root->_next = NULL;
			this->_root->_prev = NULL;
		}

		explicit list(size_type n, const value_type &val = value_type(),
					  const allocator_type &alloc = allocator_type()) :
				_allocator(alloc),
				_size(0) {
			this->_root = this->_nodeAllocator.allocate(1);
			this->_root->_next = NULL;
			this->_root->_prev = NULL;
			for (size_t i = 0; i < n; ++i)
				push_back(val);
		}

		template <class InputIterator>
		list(InputIterator first, InputIterator last,
			 const allocator_type &alloc = allocator_type(),
			 typename enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type * = 0) :
			 _allocator(alloc),
			 _size(0){
			this->_root = this->_nodeAllocator.allocate(1);
			this->_root->_next = NULL;
			this->_root->_prev = NULL;
			iterator it = first;
			while (it != last) {
				push_back(*it);
				it++;
			}
		}

		list(const list &x) :
			_allocator(x._allocator),
			_size(0) {
			this->_root = this->_nodeAllocator.allocate(1);
			this->_root->_next = NULL;
			this->_root->_prev = NULL;
			const_iterator it = x.begin();
			while (it != x.end()){
				push_back(*it);
				it++;
			}
		}

		~list() {
			clear();
			delete this->_root;
		}

		 list &operator=(const list &x) {
			if (this != &x){
				clear();
				this->_allocator = x._allocator;
				this->_root = this->_nodeAllocator.allocate(1);
				this->_root->_next = NULL;
				this->_root->_prev = NULL;
				const_iterator it = x.begin();
				while (it != x.end()){
					push_back(*it);
					it++;
				}
			}
			return *this;
		}

		//		Iterators
		iterator begin() {
			if (empty())
				return (iterator (this->_root));
			return (iterator (this->_root->_next));
		}

		const_iterator begin() const {
			if (empty())
				return (const_iterator (this->_root));
			return (const_iterator (this->_root->_next));
		}

		iterator end() {
			iterator tmp(this->_root);
			return tmp;
		}

		const_iterator end() const {
			const_iterator tmp(this->_root);
			return tmp;
		}

		reverse_iterator rbegin() {
			if (empty())
				return (reverse_iterator (this->_root));
			return (reverse_iterator (this->_root->_prev));
		}

		const_reverse_iterator rbegin() const {
			if (empty())
				return (const_reverse_iterator (this->_root));
			return (const_reverse_iterator (this->_root->_prev));
		}

		reverse_iterator rend() {
			reverse_iterator tmp(this->_root);
			return tmp;
		}

		const_reverse_iterator rend() const {
			const_reverse_iterator tmp(this->_root);
			return tmp;
		}


		// Capacity
		bool empty() const {
			if (!this->_size)
				return true;
			return false;
		}

		size_type size() const {
			return this->_size;
		}

		size_type max_size() const {
			return size_type(-1) / sizeof(value_type);
		}

		// Element access
		reference front() {
			return this->_root->_next->_value;
		}

		const_reference front() const {
			return this->_root->_next->_value;
		}

		reference back() {
			return this->_root->_prev->_value;
		}

		const_reference back() const {
			return this->_root->_prev->_value;
		}

		// Modifiers
		void push_back(const value_type &val) {
			if (this->_size == 0)
				_insertBeginning(val);
			else {
				Node<value_type> *newNode = _createNode(val);
				newNode->_prev = this->_root->_prev;
				this->_root->_prev->_next = newNode;

				newNode->_next = this->_root;
				this->_root->_prev = newNode;
				this->_size++;
			}
		}

		void push_front(const value_type &val) {
			if (this->_size == 0)
				_insertBeginning(val);
			else {
				Node<value_type> *newNode = _createNode(val);
				newNode->_next = this->_root->_next;
				this->_root->_next->_prev = newNode;

				newNode->_prev = this->_root;
				this->_root->_next = newNode;
				this->_size++;
			}
		}

		void pop_front() {
			Node<value_type> *tmp = this->_root->_next;
			tmp->_next->_prev = this->_root;
			this->_root->_next = tmp->_next;
			this->_size--;
			delete tmp;
		}

		void pop_back() {
			Node<value_type> *tmp = this->_root->_prev;
			tmp->_prev->_next = this->_root;
			this->_root->_prev = tmp->_prev;
			this->_size--;
			delete tmp;
		}

		 iterator insert(iterator position, const value_type& val){
			if (this->_size == 0){
				_insertBeginning(val);
				return this->begin();
			}
			else{
				Node<value_type> *newNode = _createNode(val);
				position._ptr->_prev->_next = newNode;
				newNode->_prev = position._ptr->_prev;
				newNode->_next = position._ptr;
				position._ptr->_prev = newNode;
				iterator it(newNode);
				this->_size++;
				return it;
			}
		}

		 void insert(iterator position, size_type n, const value_type& val){
			for (size_type i = 0; i < n; i++){
				position = insert(position, val);
				position++;
			}
		}

		 template <class InputIterator>
		 void insert(iterator position, InputIterator first, InputIterator last,
			   typename enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type * = 0){
			while (first != last){
				position = insert(position, *first);
				position++;
				first++;
			}
		}

		 iterator erase(iterator position){
			if (this->_size == 0)
				return this->end();
			iterator it = position;
			it++;
			position._ptr->_prev->_next = position._ptr->_next;
			position._ptr->_next->_prev = position._ptr->_prev;
			delete position._ptr;
			this->_size--;
			return it;
		}
		 iterator erase(iterator first, iterator last){
			iterator it;
			while(first != last){
				it = first;
				first++;
				erase(it);
			}
			return first;
		}

		void swap(list& x){
			pointer tmp = this->_root;
			size_type len = this->_size;
			this->_size = x._size;
			x._size = len;
			this->_root = x._root;
			x._root = tmp;
		}

		void resize (size_type n, value_type val = value_type()){
			if (n > this->_size){
				for (size_type i = this->_size; i < n; i++)
					push_back(val);
			}
			else if (n < this->_size()){
				for (size_type i = this->_size; i > n; i--)
					pop_back();
			}
		}


		void clear() {
			if (empty())
				return;
			Node<value_type> *tmp = this->_root->_next;
			Node<value_type> *tmp2;
			while (tmp != this->_root) {
				tmp2 = tmp;
				tmp = tmp->_next;
				delete tmp2;
				this->_size--;
			}
			this->_root->_next = NULL;
			this->_root->_prev = NULL;
		}


		 template <class InputIterator>
		 	void assign (InputIterator first, InputIterator last,
				 typename enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type * = 0){
			 clear();
			 const_iterator it = first;
			 while (it != last){
				 push_back(*it);
				 it++;
			 }
		}

		void assign(size_type n, const value_type &val) {
			clear();
			for (size_type i = 0; i < n; i++) {
				push_back(val);
			}
		}


		// Operations
//		void splice (iterator position, list& x){
//			if (!x.empty()){
//				Node<value_type> *tmp = position._ptr->_prev;
//				position._ptr->_prev = x._root->_prev;
//				x._root->_prev->_next = position._ptr;
//
//
//				tmp->_next = x._root->_next;
//				x._root->_next->_prev = tmp;
//
//				x._root->_next = NULL;
//				x._root->_prev = NULL;
//				this->_size += x._size;
//				x._size = 0;
//			}
//		}
//
//		void splice (iterator position, list& x, iterator i){
//			if (!x.empty()){
//
//
//
//				x._size--;
//				this->_size++;
//			}
//		}
//
//		void splice (iterator position, list& x, iterator first, iterator last){
//			while (first != last){
//
//				x._size--;
//				this->_size++;
//				first++;
//			}
//		}


		void reverse(){
			if (!empty()){
				iterator it = this->begin();
				Node<value_type> *tmp = this->_root->_prev;
				this->_root->_prev = this->_root->_next;
				this->_root->_next = tmp;
				while (it != this->end()){
					itemswap(it._ptr->_prev, it._ptr->_next);
					it--;
				}
			}
		}

		void remove (const value_type& val){
			iterator it = this->begin();
			while (it != this->end()){
				if (it._ptr->_value == val)
					it = _deleteOne(it);
				else
					it++;
			}
		}

		template <class Predicate>
		void remove_if (Predicate pred){
			iterator it = this->begin();
			while (it != this->end()){
				if (pred(*it))
					it = _deleteOne(it);
				else
					it++;
			}
		}

		void unique(){
			iterator it = this->begin();
			value_type val;
			while (it != this->end()){
				val = *it;
				it++;
				while (*it == val && it != this->end()){
					it = _deleteOne(it);
				}
			}
		}

		template <class BinaryPredicate>
		void unique (BinaryPredicate binary_pred){
			iterator it = this->begin();
			value_type val;
			while (it != this->end()){
				val = *it;
				it++;
				while (binary_pred(val, *it) && it != this->end()){
					it = _deleteOne(it);
				}
			}
		}

		void sort(){ // merge sort

			size_type leftSize = this->_size / 2;
			size_type rightSize = this->_size - leftSize;


		}

		template <class Compare>
			void sort (Compare comp){

		}

		//		void merge (list& x){
//
//		}


	private:
		nodeAllocator_t _nodeAllocator;
		allocator_type _allocator;
		Node<value_type> *_root;
		size_t _size;


		Node<value_type> *_createNode(const value_type &val = value_type()) {
			Node<value_type> *newNode = this->_nodeAllocator.allocate(1);
			newNode->_next = NULL;
			newNode->_prev = NULL;
			newNode->_value = val;
			return newNode;
		}

		void _insertBeginning(const value_type &val = value_type()) {
			Node<value_type> * tmp = _createNode(val);
			tmp->_next = this->_root;
			tmp->_prev = this->_root;
			this->_root->_next = tmp;
			this->_root->_prev = tmp;
			this->_size++;
		}

		iterator _deleteOne(iterator it){
			Node<value_type> *tmp = it._ptr->_next;
			it._ptr->_prev->_next = it._ptr->_next;
			it._ptr->_next->_prev = it._ptr->_prev;

			delete (it._ptr);
			this->_size--;
			return iterator(tmp);
		}
	};

}
#include "iterators.hpp"
#include "const_iterator.hpp"
#include "reverse_iterator.hpp"
#include "const_reverse_iterator.hpp"