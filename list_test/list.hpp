#pragma once

#include <iostream>
#include "../support_classes.hpp"

namespace ft{

	template <typename T>
	class ListIterator;

	template <typename T>
	class ConstListIterator;

	template <typename ImputIterator>
	class ReverseIterator;

	template < class T, class Alloc = std::allocator<T> >
	class list{
	public:
		typedef Alloc														allocator_type;
		typedef T															value_type;
		typedef typename allocator_type::size_type							size_type;
		typedef typename allocator_type::reference							reference;
		typedef typename allocator_type::const_reference					const_reference;
		typedef typename allocator_type::pointer							pointer;
		typedef typename allocator_type::const_pointer						const_pointer;
		typedef node<value_type>														list_node;
		typedef list_node *													list_node_pointer;
		typedef typename allocator_type::template rebind<node<T> >::other	node_allocator;

		typedef ListIterator<value_type>							iterator;
		typedef ReverseIterator<iterator>									reverse_iterator;
		typedef ConstListIterator<value_type>				const_iterator;
		typedef ReverseIterator<const_iterator>								const_reverse_iterator;


	private:
		allocator_type		_allocator;
		node_allocator		_nodeAllocator;
		list_node			*_root;
		size_type			_size;

	public:
		explicit list (const allocator_type& alloc = allocator_type()):
				_allocator(alloc),
				_root(NULL),
				_size(0) { _insetBeginning(); }

		explicit list (size_type n, const value_type& val = value_type(),
				   const allocator_type& alloc = allocator_type()):
				   _allocator(alloc),
				   _size(0),
				   _root(NULL){
			_insetBeginning();
			for (size_type i = 0; i < n; ++i)
				push_back(val);
		}
		//
		//		template <class InputIterator>
		//		list (InputIterator first, InputIterator last,
		//			  const allocator_type& alloc = allocator_type()){
		//
		//		}
		//
				list (const list& x):
				_allocator(x._allocator),
				_nodeAllocator(x._nodeAllocator),
				_size(0),
				_root(NULL){
					_insetBeginning();
					list_node *tmp = x._root->_next;
					while (tmp != x._root){
						push_back(tmp->_value);
						tmp = tmp->_next;
					}
				}

		~list(){
			clear();
			_nodeAllocator.deallocate(_root, 1);
		}

		// Iterators
		iterator begin(){
			return iterator(_root->_next);
		}

		const_iterator begin() const{
			return const_iterator(_root->_next);
		}

		iterator end(){
			return iterator(_root);
		}

		const_iterator end() const{
			return const_iterator(_root);
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

		// Capacity
		bool 	empty(){
			return !_size;
		}

		size_type size() const{
			return _size;
		}

		size_type max_size() const{
			return (size_type(-1) / sizeof(value_type));
		}

		// Element access
		reference front(){
			return _root->_next->_value;
		}

		const_reference front() const{
			return _root->_next->_value;
		}

		reference back(){
			return _root->_prev->_value;
		}

		const_reference back() const{
			return _root->_prev->_value;
		}

		// Modifiers
		void	push_back(const value_type &val){
			list_node	*newNode = _createNode(val);
			newNode->_prev = _root->_prev;
			_root->_prev->_next = newNode;

			newNode->_next = _root;
			_root->_prev = newNode;
			++_size;
		}

		void	pop_back(){
			if (empty())
				return;
			list_node *tmp = _root->_prev;
			tmp->_prev->_next = _root;
			_root->_prev = tmp->_prev;
			--_size;
			_destroyNode(tmp);
		}

		void push_front (const value_type& val){
			list_node	*newNode = _createNode(val);
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

		void clear(){
			while (_size)
				pop_back();
		}


	private:

		void 			_destroyNode(list_node *node){
			_allocator.destroy(&(node->_value));
			_nodeAllocator.deallocate(node, 1);
		}

		void 			_insetBeginning(){
			_root = _nodeAllocator.allocate(1);
			_root->_next = _root;
			_root->_prev = _root;
		}

		list_node		*_createNode(const value_type &val){
			list_node	*tmp = _nodeAllocator.allocate(1);
			tmp->_next = tmp;
			tmp->_prev = tmp;
			_allocator.construct(&tmp->_value, val);
			return tmp;
		}
	};
}

#include "ListIterator.hpp"
#include "../ReverseIterator.hpp"
