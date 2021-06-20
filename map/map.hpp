#pragma once

#include "../support_classes.hpp"
#include <utility>
#include <iostream>
#include "MapIterator.hpp"
#include "../ReverseIterator.hpp"

namespace ft{






	template < class Key,                                  // map::key_type
			class T,                                       // map::mapped_type
			class Compare = _less_compration<Key>,                     // map::key_compare
			class Alloc = std::allocator<std::pair<const Key, T> >    // map::allocator_type
	> class map{
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
			friend class	map;
		protected:
			key_compare		comp;
			value_compare(key_compare c) : comp(c) {}
		public:
			typedef bool		result_type;
			typedef value_type	first_argument_type;
			typedef value_type	second_argument_type;
			bool	operator()(value_type const &x, value_type const &y) const
			{	return (comp(x.first, y.first));	}
		};

	private:
		typedef __base<Key, T>										map_node;
		typedef typename Alloc::template rebind<map_node>::other	node_allocator_type;

		node_allocator_type		_node_allocator;
		value_compare			_comp;
		size_type				_size;
		map_node				*_root;
		map_node				*_nill;

	public:

		explicit map (const key_compare& comp = key_compare(),
					  const allocator_type& alloc = allocator_type()):
				_node_allocator(alloc), _comp(comp), _size(0){
			_init_nill();
		}

		template <class InputIterator>
		map (InputIterator first, InputIterator last,
			 const key_compare& comp = key_compare(),
			 const allocator_type& alloc = allocator_type()):
			 _node_allocator(alloc),
			 _comp(comp),
			 _size(0){
			_init_nill();
			insert(first, last);
		}

		map (const map& x):
			_node_allocator(x._node_allocator),
			_comp(x._comp),
			_size(0){
			_init_nill();
			insert(x.begin(), x.end());
		}

		~map(){
			clear();
			_node_allocator.deallocate(_nill, 1);
		}

		map& operator=(const map& x){
			if (this != &x){
				clear();
				insert(x.begin(), x.end());
			}
			return *this;
		}


		// Iterators
		iterator begin(){
			return iterator(_nill->left, _nill);
		}

		const_iterator begin() const{
			return const_iterator(_nill->left, _nill);
		}

		iterator end(){
			return iterator(_nill, _nill);
		}

		const_iterator end() const{
			return const_iterator(_nill, _nill);
		}

		reverse_iterator rbegin(){
			return reverse_iterator(end());
		}

		const_reverse_iterator rbegin() const{
			return const_reverse_iterator(end());
		}

		reverse_iterator rend(){
			return reverse_iterator(begin());
		}

		const_reverse_iterator rend() const{
			return const_reverse_iterator(begin());
		}

		// Capacity:
		size_type size() const{
			return _size;
		}

		bool empty() const{
			return !_size;
		}

		size_type max_size() const{
			return (size_type(-1) / sizeof(value_type)); // ???
		}

		// Element access:
		mapped_type& operator[] (const key_type& k){
			return ((*((this->insert(make_pair(k,mapped_type()))).first)).second);
		}

		// Modifiers
		std::pair<iterator,bool> insert (const_reference val){
			map_node *node = _find_node(_root, val);
			if (node != NULL)
				return std::make_pair(iterator(node, _nill), false);
			node = _map_insert(val);
			++_size;
			return std::make_pair(iterator(node, _nill), true);
		}

		iterator insert (iterator position, const value_type& val){
			static_cast<void>(position);
			insert(val);
		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last){
			while (first != last)
				insert(*first++);
		}

		void erase (iterator position){
			erase(position.base()->data.first);
		}

		size_type erase (const key_type& k){
			map_node *node;
			if (empty() || (node = _find_node_by_key(_root, k)) == NULL)
				return size_type(0);

			// check which is child (left or right parent) ...
			map_node **side_node;
			if (node == _root)
				side_node = &(_nill->right);
			else if (node->parent->left == node) // replace to _nill parent ...
				side_node = &(node->parent->left);
			else if (node->parent->right == node)
				side_node = &(node->parent->right);
			// if node doesn't have left or right
			if (node->left == _nill && node->right == _nill){
				*side_node = _nill;
				if (node == _root)
					_root = _nill;
				_destroy_node(node);
			}
			// only right
			else if (node->right != _nill && node->left == _nill){
				*side_node = node->right;
				node->right->parent = node->parent;
				if (node == _root)
					_root = node->right;
				_destroy_node(node);
			}
			// only left
			else if ((node->left != _nill && node->right == _nill)){
				*side_node = node->left;
				node->left->parent = node->parent;
				if (node == _root)
					_root = node->left;
				_destroy_node(node);
			}
			else{
				if (node->right->left == _nill){
					// change parent
					*side_node = node->right;
					node->right->parent = node->parent;
					node->right->left = node->left;
					node->left->parent = node->right;
					if (node == _root)
						_root = node->right;
					_destroy_node(node);
				}
				else{
					map_node *last_left = get_min(node->right, _nill);
					*(side_node) = last_left;
					last_left->parent->left = _nill;
					last_left->parent = node->parent;
					node->left->parent = last_left;
					last_left->left = node->left;
					node->right->parent = last_left;
					last_left->right = node->right;
					if (node == _root)
						_root = last_left;
					_destroy_node(node);
				}
			}
			--_size;
			_nill->left = get_min(_root, _nill);
			_nill->parent = get_max(_root, _nill);
			return size_type(1);
		}

		void erase (iterator first, iterator last) {
			while (first != last)
				erase(first++);
		}

		void clear(){
			while (_size)
				erase(begin());
		}

		void swap (map& x){
			ft::itemswap(this->_nill, x._nill);
			ft::itemswap(this->_root, x._root);
			ft::itemswap(this->_size, x._size);
			ft::itemswap(this->_comp, x._comp);
			ft::itemswap(this->_node_allocator, x._node_allocator);
		}

		// Observers
		key_compare key_comp() const{
			return _comp.comp;
		}

		value_compare value_comp() const{
			return _comp;
		}

		// Operations
		iterator find (const key_type& k){
			map_node *node = _find_node_by_key(_root, k);
			if (node == NULL)
				return end();
			return iterator(node);
		}

		const_iterator find (const key_type& k) const{
			map_node *node = _find_node_by_key(_root, k);
			if (node == NULL)
				return end();
			return const_iterator(node);
		}

		size_type count (const key_type& k) const{
			if (_find_node_by_key(_root, k) == NULL)
				return 0;
			return 1;
		}

		iterator lower_bound (const key_type& k){
			iterator it = begin();
			while (it != end()){
				if (!(_comp.comp(it->first, k)))
					break;
				++it;
			}
			return it;
		}

		const_iterator lower_bound (const key_type& k) const{
			const_iterator it = begin();
			while (it != end()){
				if (!(_comp.comp(it->first, k)))
					break;
				++it;
			}
			return it;
		}

		iterator upper_bound (const key_type& k){
			iterator it = begin();
			while (it != end()){
				if (_comp.comp(k, it->first))
					break;
				++it;
			}
			return it;
		}

		const_iterator upper_bound (const key_type& k) const{
			const_iterator it = begin();
			while (it != end()){
				if (_comp.comp(k, it->first))
					break;
				++it;
			}
			return it;
		}

		std::pair<const_iterator,const_iterator>	equal_range (const key_type& k) const{
			return (std::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k)));
		}

		std::pair<iterator,iterator>		equal_range (const key_type& k){
			return (std::pair<iterator, iterator>(lower_bound(k), upper_bound(k)));
		}




	private:

		void		_init_nill(){
			_nill = _node_allocator.allocate(1);
			_nill->parent = _nill;
			_nill->left = _nill;
			_nill->right = _nill;
			_nill->parent = _nill;
			_nill->isRed = false;
			_root = _nill;
		}

		void 		_insert_at(map_node *node, map_node *newNode){
			if (_comp(newNode->data, node->data)){
				if (node->left != _nill){
					_insert_at(node->left, newNode);
					return;
				}
				else
					node->left = newNode;
			}
			else {
				if (node->right != _nill){
					_insert_at(node->right, newNode);
					return;
				}
				else
					node->right = newNode;
			}
			newNode->parent = node;
		}

		map_node	*_map_insert(const_reference val){
			map_node *newNode = _create_node(val);
			if (_root == _nill)
				_root = newNode;
			else {
				_insert_at(_root, newNode);
			}

			//balance

			_nill->left = get_min(_root, _nill);
			_nill->parent = get_max(_root, _nill);
			return newNode;
		}

		map_node	*_create_node(const_reference val){
			allocator_type data_allocator(_node_allocator);
			map_node *newNode = _node_allocator.allocate(1);
			newNode->parent = _nill;
			newNode->left = _nill;
			newNode->right = _nill;
			newNode->isRed = false;
			data_allocator.construct(&(newNode->data), val);
			return newNode;
		}

		void 		_destroy_node(map_node *node){
			allocator_type data_allocator(_node_allocator);
			data_allocator.destroy(&(node->data));
			_node_allocator.deallocate(node, 1);
		}

		map_node *_find_node(map_node *node, const_reference val){
			if (node == _nill)
				return NULL;
			if (_comp(val, node->data))
				return (_find_node(node->left, val));
			if (_comp(node->data, val))
				return (_find_node(node->right, val));
			return node;
		}

		map_node *_find_node_by_key(map_node *node, const key_type &key){
			if (node == _nill)
				return NULL;
			if (_comp.comp(key, node->data.first))
				return (_find_node_by_key(node->left, key));
			if (_comp.comp(node->data.first, key))
				return (_find_node_by_key(node->right, key));
			return node;
		}

	};

}