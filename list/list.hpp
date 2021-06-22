#pragma once

#include <iostream>
#include "../support_classes.hpp"
#include "ListIterator.hpp"
#include "../ReverseIterator.hpp"

namespace ft {

	template <class T, class Alloc = std::allocator<T> >
	class list {
	public:
		typedef Alloc allocator_type;
		typedef T value_type;
		typedef typename allocator_type::size_type							size_type;
		typedef typename allocator_type::reference							reference;
		typedef typename allocator_type::const_reference					const_reference;
		typedef typename allocator_type::pointer							pointer;
		typedef typename allocator_type::const_pointer						const_pointer;
		typedef node<value_type>											list_node;
		typedef list_node *													list_node_pointer;
		typedef typename allocator_type::template rebind<node<T> >::other	node_allocator;

		typedef ListIterator<value_type, pointer, reference>				iterator;
		typedef ReverseIterator<iterator>									reverse_iterator;
		typedef ListIterator<value_type, const_pointer, const_reference>	const_iterator;
		typedef ReverseIterator<const_iterator>								const_reverse_iterator;


	private:
		allocator_type _allocator;
		node_allocator _nodeAllocator;
		list_node *_root;
		size_type _size;

	public:
		explicit list(const allocator_type &alloc = allocator_type()) :
				_allocator(alloc),
				_root(NULL),
				_size(0) { _insetBeginning(); }

		explicit list(size_type n, const value_type &val = value_type(),
					  const allocator_type &alloc = allocator_type()) :
				_allocator(alloc),
				_root(NULL),
				_size(0) {
			_insetBeginning();
			for (size_type i = 0; i < n; ++i)
				push_back(val);
		}

		template <class InputIterator>
		list(InputIterator first, InputIterator last,
			 const allocator_type &alloc = allocator_type(),
			 typename enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type * = NULL):
				_allocator(alloc),
				_root(NULL),
				_size(0) {
			_insetBeginning();
			while (first != last) {
				push_back(*first);
				++first;
			}
		}

		list(const list &x) :
				_allocator(x._allocator),
				_nodeAllocator(x._nodeAllocator),
				_size(0),
				_root(NULL) {
			_insetBeginning();
			iterator it = x.begin();
			while (it != x.end()) {
				push_back(*it);
				++it;
			}
		}

		~list() {
			clear();
			_nodeAllocator.deallocate(_root, 1);
		}

		list &operator=(const list &x) {
			if (this != &x)
				assign(x.begin(), x.end());
			return *this;
		}

		// Iterators
		iterator begin() {
			return iterator(_root->_next);
		}

		const_iterator begin() const {
			return const_iterator(_root->_next);
		}

		iterator end() {
			return iterator(_root);
		}

		const_iterator end() const {
			return const_iterator(_root);
		}

		reverse_iterator rbegin() {
			return reverse_iterator(end());
		}

		const_reverse_iterator rbegin() const {
			return const_reverse_iterator(end());
		}

		reverse_iterator rend() {
			return reverse_iterator(begin());
		}

		const_reverse_iterator rend() const {
			return const_reverse_iterator(begin());
		}

		// Capacity
		bool empty() {
			return !_size;
		}

		size_type size() const {
			return _size;
		}

		size_type max_size() const {
			return (size_type(-1) / sizeof(value_type));
		}

		// Element access
		reference front() {
			return _root->_next->_value;
		}

		const_reference front() const {
			return _root->_next->_value;
		}

		reference back() {
			return _root->_prev->_value;
		}

		const_reference back() const {
			return _root->_prev->_value;
		}

		// Modifiers
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last,
					typename enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type * = NULL) {
			clear();
			while (first != last) {
				push_back(*first);
				++first;
			}
		}

		void assign(size_type n, const value_type &val) {
			clear();
			for (size_type i = 0; i < n; ++i)
				push_back(val);
		}

		void push_back(const value_type &val) {
			list_node *newNode = _createNode(val);
			newNode->_prev = _root->_prev;
			_root->_prev->_next = newNode;

			newNode->_next = _root;
			_root->_prev = newNode;
			++_size;
		}

		void pop_back() {
			if (empty())
				return;
			list_node *tmp = _root->_prev;
			tmp->_prev->_next = _root;
			_root->_prev = tmp->_prev;
			--_size;
			_destroyNode(tmp);
		}

		void push_front(const value_type &val) {
			list_node *newNode = _createNode(val);
			newNode->_next = _root->_next;
			_root->_next->_prev = newNode;

			newNode->_prev = _root;
			_root->_next = newNode;
			++_size;
		}

		void pop_front() {
			if (empty())
				return;
			list_node *tmp = _root->_next;
			tmp->_next->_prev = _root;
			_root->_next = tmp->_next;
			--_size;
			_destroyNode(tmp);
		}

		iterator insert(iterator position, const value_type &val) {
			list_node *newNode = _createNode(val);
			list_node *pos = position._ptr;
			pos->_prev->_next = newNode;
			newNode->_prev = pos->_prev;

			newNode->_next = pos;
			pos->_prev = newNode;
			++_size;
			return iterator(newNode);
		}

		void insert(iterator position, size_type n, const value_type &val) {
			for (size_type i = 0; i < n; ++i) {
				position = insert(position, val);
			}
		}

		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last,
					typename enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type * = NULL) {
			while (first != last) {
				position = ++insert(position, *first);
				++first;
			}
		}

		iterator erase(iterator position) {
			if (position == _root)
				return position;
			list_node *tmp = position._ptr;
			tmp->_prev->_next = tmp->_next;
			tmp->_next->_prev = tmp->_prev;
			iterator it(tmp->_next);
			_destroyNode(tmp);
			--_size;
			return it;
		}

		iterator erase(iterator first, iterator last) {
			while (first != last)
				first = erase(first);
			return first;
		}

		void swap(list &x) {
			itemswap(this->_root, x._root);
			itemswap(this->_allocator, x._allocator);
			itemswap(this->_nodeAllocator, x._nodeAllocator);
			itemswap(this->_size, x._size);
		}

		void resize(size_type n, value_type val = value_type()) {
			if (n > _size) {
				for (size_type i = _size; i < n; ++i)
					push_back(val);
			} else if (n < _size) {
				for (size_type i = _size; i > n; --i)
					pop_back();
			}
		}

		void clear() {
			while (_size)
				pop_back();
		}

		// Operations
		void remove(const value_type &val) {
			iterator it = begin();
			while (it != end()) {
				if (*it == val)
					it = erase(it);
				else
					++it;
			}
		}

		template <class Predicate>
		void remove_if(Predicate pred) {
			iterator it = begin();
			while (it != end()) {
				if (pred(*it))
					it = erase(it);
				else
					++it;
			}
		}

		void unique() {
			unique(ft::_equal_compration<value_type>());
		}

		template <class BinaryPredicate>
		void unique(BinaryPredicate binary_pred) {
			iterator it = begin();
			value_type val;
			while (it != end()) {
				val = *it;
				++it;
				while (it != end() && binary_pred(val, *it))
					it = erase(it);
			}
		}

		void reverse() {
			if (_size > 1) {
				iterator it = begin();
				list_node *tmp = _root->_prev;
				_root->_prev = _root->_next;
				_root->_next = tmp;
				while (it != end()) {
					itemswap(it._ptr->_prev, it._ptr->_next);
					--it;
				}
			}
		}

		void splice(iterator position, list &x) {
			if (x.empty() || &x == this)
				return;
			list_node *pos_prev = position._ptr->_prev;
			pos_prev->_next = x._root->_next;
			x._root->_next->_prev = pos_prev;
			position._ptr->_prev = x._root->_prev;
			x._root->_prev->_next = position._ptr;
			_size += x._size;

			x._root->_next = x._root;
			x._root->_prev = x._root;
			x._size = 0;
		}

		void splice(iterator position, list &x, iterator i) {
			if (x.empty() || &x == this || position == i)
				return;
			list_node *pos_prev = position._ptr->_prev;
			list_node *x_pos = i._ptr;

			x_pos->_prev->_next = x_pos->_next;
			x_pos->_next->_prev = x_pos->_prev;

			x_pos->_prev = pos_prev;
			x_pos->_next = position._ptr;


			pos_prev->_next = x_pos;
			position._ptr->_prev = x_pos;
			++_size;
			--x._size;
		}

		void splice(iterator position, list &x, iterator first, iterator last) {
			if (x.empty() || first == x.end())
				return;
			iterator it = first;
			while (first != last) {
				++it;
				splice(position, x, first);
				first = it;
			}
		}

		void merge(list &x) {
			merge(x, ft::_less_compration<value_type>());
		}

		template <class Compare>
		void merge(list &x, Compare comp) {
			if (x.empty() || &x == this)
				return;
			iterator xit = x.begin();
			iterator it = begin();
			while (xit != x.end() && it != end()) {
				if (comp(*xit, *it)) {
					iterator tmp = xit;
					++xit;
					splice(it, x, tmp);
				} else
					++it;
			}
			if (xit != x.end())
				splice(end(), x);
		}

		void sort() {
			sort(ft::_less_compration<value_type>());
		}

		template <class Compare>
		void sort(Compare comp) {
			if (_size < 2)
				return;
			iterator it = begin();
			size_t i = 0;
			while ((i * 2 < _size) && (it != end())) {
				++it;
				++i;
			}
			list half;
			half.splice(half.begin(), *this, it, this->end());

			this->sort(comp);
			half.sort(comp);

			this->merge(half, comp);
		}

	private:

		void _destroyNode(list_node *node) {
			_allocator.destroy(&(node->_value));
			_nodeAllocator.deallocate(node, 1);
		}

		void _insetBeginning() {
			_root = _nodeAllocator.allocate(1);
			_root->_next = _root;
			_root->_prev = _root;
		}

		list_node *_createNode(const value_type &val) {
			list_node *tmp = _nodeAllocator.allocate(1);
			tmp->_next = tmp;
			tmp->_prev = tmp;
			_allocator.construct(&tmp->_value, val);
			return tmp;
		}
	};

	template <class T, class Alloc>
	bool operator==(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) {
		typename list<T, Alloc>::size_type sz = lhs.size();
		return (sz == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool operator!=(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) {
		return !(lhs == rhs);
	}

	template <class T, class Alloc>
	bool operator<(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator<=(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) {
		return !(rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) {
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>=(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) {
		return !(lhs < rhs);
	}

	template <class T, class Alloc>
	void swap(list<T, Alloc> &x, list<T, Alloc> &y) {
		x.swap(y);
	}
}




