#pragma once

#include "../support_classes.hpp"
#include <utility>
#include <iostream>

#include "../support_classes.hpp"
#include "MapIterator.hpp"

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

		typedef MapIterator<Alloc>							iterator;

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
		typedef __base<Alloc>										map_node;
		typedef typename Alloc::template rebind<map_node>::other	node_allocator_type;
//		typedef std::pair<iterator, bool>	map_insres;

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

//		template <class InputIterator>
//		map (InputIterator first, InputIterator last,
//			 const key_compare& comp = key_compare(),
//			 const allocator_type& alloc = allocator_type()){
//
//		}
//
//		map (const map& x){
//
//		}

		~map(){

		}


		// Iterators
		iterator begin(){
			return iterator(_nill->left, _nill);
		}

//		const_iterator begin() const{
//
//		}

		iterator end(){
			return iterator(_nill, _nill);
		}

//		const_iterator end() const{
//
//		}

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



		// Modifiers
		std::pair<iterator,bool> insert (const value_type& val){
			// find element
			// node = find
			// if (node) retunr ... false
			// else
			map_node *newNode = _map_insert(val);
			++this->_size;
			return std::make_pair(iterator(newNode), true);
		}

		iterator insert (iterator position, const value_type& val){

		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last){

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
			if (_com(node->data, newNode->data)){
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

//			balance + _nill right, left
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
		}

		void 		_delete_node(map_node *node){
			allocator_type data_allocator(_node_allocator);
			data_allocator.destroy(&(node->data));
			_node_allocator.deallocate(node, 1);
		}

		map_node *_find_node(map_node *node, const_reference val){
			if (node == _nill)
				return NULL;

		}

	};

}