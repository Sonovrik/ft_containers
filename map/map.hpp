#pragma once

#include "../support_classes.hpp"
#include <utility>
#include <iostream>
#include "MapIterator.hpp"
#include "../ReverseIterator.hpp"
#include "map_base.hpp"

namespace ft {

	template <class Key,                                  // map::key_type
			class T,                                       // map::mapped_type
			class Compare = _less_compration<Key>,                     // map::key_compare
			class Alloc = std::allocator<std::pair<const Key, T> >    // map::allocator_type
	>
	class map {
	public:
		typedef Key													key_type;
		typedef T													mapped_type;
		typedef Compare												key_compare;
		typedef Alloc												allocator_type;
		typedef typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::const_pointer				const_pointer;

		typedef typename allocator_type::difference_type			difference_type;
		typedef typename allocator_type::size_type					size_type;
		typedef std::pair<const key_type, mapped_type>				value_type;

		typedef MapIterator<Key, T>									iterator;
		typedef ConstMapIterator<Key, T>							const_iterator;
		typedef ReverseIterator<iterator>							reverse_iterator;
		typedef ReverseIterator<const_iterator>						const_reverse_iterator;

		// in C++98, it is required to inherit binary_function<value_type,value_type,bool>
		class value_compare : public binary_function<value_type, value_type, bool> {
		private:
			friend class map;

		protected:
			key_compare comp;

			value_compare(key_compare c) : comp(c) { }

		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;

			bool operator()(value_type const &x, value_type const &y) const { return (comp(x.first, y.first)); }
		};

	private:
		typedef __base<const Key, T> map_node;
		typedef typename Alloc::template rebind<map_node>::other node_allocator_type;

		node_allocator_type _node_allocator;
		value_compare _comp;
		size_type _size;
		map_node *_root;
		map_node *_nill;

	public:
		explicit map(const key_compare &comp = key_compare(),
					 const allocator_type &alloc = allocator_type()) :
				_node_allocator(alloc), _comp(comp), _size(0) { _init_nill(); }

		template <class InputIterator>
		map(InputIterator first, InputIterator last,
			const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type()):
				_node_allocator(alloc),
				_comp(comp),
				_size(0) {
			_init_nill();
			insert(first, last);
		}

		map(const map &x) :
				_node_allocator(x._node_allocator),
				_comp(x._comp),
				_size(0) {
			_init_nill();
			insert(x.begin(), x.end());
		}

		~map() {
			clear();
			_node_allocator.deallocate(_nill, 1);
		}

		map &operator=(const map &x) {
			if (this != &x) {
				clear();
				insert(x.begin(), x.end());
			}
			return *this;
		}

		// Iterators
		iterator begin() {
			return iterator(_nill->left, _nill);
		}

		const_iterator begin() const {
			return const_iterator(_nill->left, _nill);
		}

		iterator end() {
			return iterator(_nill, _nill);
		}

		const_iterator end() const {
			return const_iterator(_nill, _nill);
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

		// Capacity:
		size_type size() const {
			return _size;
		}

		bool empty() const {
			return !_size;
		}

		size_type max_size() const {
			return (this->_node_allocator.max_size());
		}

		// Element access:
		mapped_type &operator[](const key_type &k) {
			return ((*((this->insert(std::make_pair(k, mapped_type()))).first)).second);
		}

		// Modifiers
		std::pair<iterator, bool> insert(const_reference val) {
			map_node *newNode = _find_node(_root, val);
			if (newNode != NULL)
				return std::make_pair(iterator(newNode, _nill), false);
			newNode = _create_node(val);
			if (_root == _nill) {
				_root = newNode;
				_nill->left = _root;
				_nill->parent = _root;
			} else
				_insert_at_branch(_root, newNode);
			++_size;
			_nill->left = map_node::get_min(_root, _nill);
			_nill->parent = map_node::get_max(_root, _nill);
			return std::make_pair(iterator(newNode, _nill), true);
		}

		iterator insert(iterator position, const value_type &val) {
			static_cast<void>(position);
			return (insert(val)).first;
		}

		template <class InputIterator>
		void insert(InputIterator first, InputIterator last) {
			while (first != last)
				insert(*first++);
		}

		void erase(iterator position) {
			erase(position.base()->data.first);
		}

		size_type erase(const key_type &k) {
			map_node *node;
			map_node *ret_node;
			if (empty() || (node = _find_node_by_key(_root, k)) == NULL)
				return size_type(0);

			map_node **side_node = _get_parent_side(node); // check which is children (left or right)

			if (node->left == _nill && node->right == _nill) // if node doesn't have left or right children
				ret_node = _erase_node_without_children(side_node, node);
			else if (node->right != _nill && node->left == _nill) // only right
				ret_node = _erase_only_one_child(side_node, node, 1);
			else if ((node->left != _nill && node->right == _nill)) // only left
				ret_node = _erase_only_one_child(side_node, node, 0);
			else { // both
				if (node->right->left == _nill) // right->left doesn't exist
					ret_node = _erase_if_no_left(side_node, node);
				else
					ret_node = _erase_if_left(side_node, node); // right->left exists
			}
			if (_root == node)
				_root = ret_node;
			_destroy_node(node);
			--_size;
			_nill->left = map_node::get_min(_root, _nill);
			_nill->parent = map_node::get_max(_root, _nill);
			return size_type(1);
		}

		void erase(iterator first, iterator last) {
			while (first != last)
				erase(first++);
		}

		void clear() {
			while (_size)
				erase(begin());
		}

		void swap(map &x) {
			ft::itemswap(this->_nill, x._nill);
			ft::itemswap(this->_root, x._root);
			ft::itemswap(this->_size, x._size);
			ft::itemswap(this->_comp, x._comp);
			ft::itemswap(this->_node_allocator, x._node_allocator);
		}

		// Observers
		key_compare key_comp() const {
			return _comp.comp;
		}

		value_compare value_comp() const {
			return _comp;
		}

		// Operations
		iterator find(const key_type &k) {
			map_node *node = _find_node_by_key(_root, k);
			if (node == NULL)
				return end();
			return iterator(node, _nill);
		}

		const_iterator find(const key_type &k) const {
			map_node *node = _find_node_by_key(_root, k);
			if (node == NULL)
				return end();
			return const_iterator(node, _nill);
		}

		size_type count(const key_type &k) const {
			if (_find_node_by_key(_root, k) == NULL)
				return 0;
			return 1;
		}

		iterator lower_bound(const key_type &k) {
			iterator it = begin();
			while (it != end()) {
				if (!(_comp.comp(it->first, k)))
					break;
				++it;
			}
			return it;
		}

		const_iterator lower_bound(const key_type &k) const {
			const_iterator it = begin();
			while (it != end()) {
				if (!(_comp.comp(it->first, k)))
					break;
				++it;
			}
			return it;
		}

		iterator upper_bound(const key_type &k) {
			iterator it = begin();
			while (it != end()) {
				if (_comp.comp(k, it->first))
					break;
				++it;
			}
			return it;
		}

		const_iterator upper_bound(const key_type &k) const {
			const_iterator it = begin();
			while (it != end()) {
				if (_comp.comp(k, it->first))
					break;
				++it;
			}
			return it;
		}

		std::pair<const_iterator, const_iterator> equal_range(const key_type &k) const {
			return (std::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k)));
		}

		std::pair<iterator, iterator> equal_range(const key_type &k) {
			return (std::pair<iterator, iterator>(lower_bound(k), upper_bound(k)));
		}

	private:

		void _init_nill() {
			_nill = _node_allocator.allocate(1);
			_nill->parent = _nill;
			_nill->left = _nill;
			_nill->right = _nill;
			_nill->parent = _nill;
			_nill->isRed = false;
			_root = _nill;
		}

		void _insert_at_branch(map_node *node, map_node *newNode) {
			if (_comp(newNode->data, node->data)) {
				if (node->left != _nill) {
					_insert_at_branch(node->left, newNode);
					return;
				} else
					node->left = newNode;
			} else {
				if (node->right != _nill) {
					_insert_at_branch(node->right, newNode);
					return;
				} else
					node->right = newNode;
			}
			newNode->parent = node;
		}

		map_node *_create_node(const_reference val) {
			allocator_type data_allocator(_node_allocator);
			map_node *newNode = _node_allocator.allocate(1);
			newNode->parent = _nill;
			newNode->left = _nill;
			newNode->right = _nill;
			newNode->isRed = false;
			data_allocator.construct(&(newNode->data), val);
			return newNode;
		}

		void _destroy_node(map_node *node) {
			allocator_type data_allocator(_node_allocator);
			data_allocator.destroy(&(node->data));
			_node_allocator.deallocate(node, 1);
		}

		map_node *_find_node(map_node *node, const_reference val) {
			if (node == _nill)
				return NULL;
			if (_comp(val, node->data))
				return (_find_node(node->left, val));
			if (_comp(node->data, val))
				return (_find_node(node->right, val));
			return node;
		}

		map_node *_find_node_by_key(map_node *node, const key_type &key) const {
			if (node == _nill)
				return NULL;
			if (_comp.comp(key, node->data.first))
				return (_find_node_by_key(node->left, key));
			if (_comp.comp(node->data.first, key))
				return (_find_node_by_key(node->right, key));
			return node;
		}

		map_node **_get_parent_side(map_node *node) const {
			if (node == _root)
				return &(_nill->right);
			else if (node->parent->left == node)
				return &(node->parent->left);
			else if (node->parent->right == node)
				return &(node->parent->right);
			return NULL;
		}

		map_node *_erase_node_without_children(map_node **side_node, map_node *node) {
			*side_node = _nill;
			if (node == _root)
				_root = _nill;
			return _nill;
		}

		map_node *_erase_only_one_child(map_node **side_node, map_node *node, bool right) {
			map_node *ret;
			if (right) {
				ret = node->right;
				*side_node = node->right;
				node->right->parent = node->parent;
			} else {
				ret = node->left;
				*side_node = node->left;
				node->left->parent = node->parent;
			}
			return ret;
		}

		map_node *_erase_if_no_left(map_node **side_node, map_node *node) {
			*side_node = node->right;
			node->right->parent = node->parent;
			node->right->left = node->left;
			node->left->parent = node->right;
			return node->right;
		}

		map_node *_erase_if_left(map_node **side_node, map_node *node) {
			map_node *last_left = map_node::get_min(node->right, _nill);
			*(side_node) = last_left;
			last_left->parent->left = last_left->right;
			last_left->right->parent = last_left->parent;
			last_left->parent = node->parent;
			node->left->parent = last_left;
			last_left->left = node->left;
			node->right->parent = last_left;
			last_left->right = node->right;
			return last_left;
		}
	};

	// Non-member functions
	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs) {
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), rhs.end(), lhs.begin());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs) {
		return (!(lhs == rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key, T, Compare, Alloc> &lhs,
				   const map<Key, T, Compare, Alloc> &rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs) {
		return (!(rhs < lhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const map<Key, T, Compare, Alloc> &lhs,
				   const map<Key, T, Compare, Alloc> &rhs) {
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs) {
		return (!(lhs < rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	void swap(map<Key, T, Compare, Alloc> &lhs,
			  map<Key, T, Compare, Alloc> &rhs) {
		lhs.swap(rhs);
	}
}