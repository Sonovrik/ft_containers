#pragma once

#include <iostream>

namespace ft{

	template <class T>
	struct node {
	public:
		T				_value;
		node			*_next;
		node			*_prev;
	};


	template < class T, class Alloc = std::allocator<T> >
	class list{
	public:
		typedef Alloc										allocator_type;
		typedef T											value_type;
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef node<T>										list_node;
		typedef list_node *									list_node_pointer;
		typedef typename allocator_type::template rebind<node<T> >::other				node_allocator;

	private:
		node_allocator		_nodeAllocator;
		allocator_type		_allocator;
		list_node			*_root;
		size_type			_size;

	public:
		explicit list (const allocator_type& alloc = allocator_type()):
				_allocator(alloc),
				_size(0){ _insetBeginning(); }

		explicit list (size_type n, const value_type& val = value_type(),
				   const allocator_type& alloc = allocator_type()){
			_insetBeginning();
			for (size_type i = 0; i < n; ++i){
				push_back(val);
			}
		}
		//
		//		template <class InputIterator>
		//		list (InputIterator first, InputIterator last,
		//			  const allocator_type& alloc = allocator_type()){
		//
		//		}
		//
		//		list (const list& x){
		//
		//		}

		~list(){
			clear();
			_nodeAllocator.deallocate(_root, 1);
		}

		void clear(){
			while (_size)
				pop_back();
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

		bool 	empty(){
			return !_size;
		}

		void	push_back(const value_type &val){
			list_node *tmp = _root->_next;
			while (tmp->_next != _root)
				tmp = tmp->_next;
			list_node	*newNode = _createNode(val);
			newNode->_prev = _root->_prev;
			_root->_prev = newNode;

			newNode->_next = _root;
			_root->_prev = newNode;
			++_size;
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