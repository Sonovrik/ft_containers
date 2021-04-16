#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include "../utils/utils.hpp"

namespace ft {
	// template <typename T>
	// struct		Node {
	// 	T				_value;
	// 	Node			*_next;
	// 	Node			*_prev;
	// };

	template <class T, class Alloc = std::allocator<T> > class list {
	public:

		typedef Alloc											allocator_type;
		typedef	T												value_type;
		typedef typename allocator_type::reference				reference;
		typedef typename allocator_type::const_reference		const_reference;
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::const_pointer			const_pointer;
		// typedef iterator				allocator_t;
		// typedef const_iterator				allocator_t;
		// typedef reverse_iterator				allocator_t;
		// typedef const_reverse_iterator				allocator_t;
		// typedef difference_type				allocator_t;
		typedef size_t				size_type;


		typedef std::allocator< Node<value_type> > nodeAllocator_t;


		explicit list(const allocator_type &alloc = allocator_type()):
			_allocator(alloc),
			_size(0){
			this->_last = this->_nodeAllocator.allocate(1);
			this->_last->_next = NULL;
			this->_last->_prev = NULL;
			this->_first = this->_last;
		}

		explicit list(size_type n, const value_type &val = value_type(),
			const allocator_type &alloc = allocator_type()):
				_allocator(alloc),
				_size(0){
				for (size_t i = 0; i < n; ++i)
					push_back(val);
		}

		// template <class InputIterator>
		// list(InputIterator first, InputIterator last,
		// 	 const allocator_type &alloc = allocator_type());

		// list(const list &x){

		// }


		~list(){
			if (empty())
				return;
			Node<value_type> *tmp = this->_first;
			while (tmp->_next != NULL){
				this->_size--;
				tmp = tmp->_next;
				delete tmp->_prev;
			}
			delete tmp;
			this->_size--;
		}

		// list &operator=(const list &x);

		// // Iterators
		// iterator begin();
		// const_iterator begin();

		// iterator end();
		// const_iterator end();

		// reverse_iterator rbegin();
		// const_reverse_iterator rbegin();

		// reverse_iterator rend();
		// const_reverse_iterator rend();

		// Capacity
		bool empty() const{
			if (!this->_size)
				return true;
			return false;
		}

		size_type size() const{
			return this->_size;
		}

		size_type max_size() const{ // ???
			return size_type(-1) / sizeof(value_type);
		}

		// Element access
		reference front(){
			return this->_first->_value;
		}

		const_reference front() const{
			return this->_first->_value;
		}

		reference back(){
			return this->_last->_value;
		}

		const_reference back() const{
			return this->_last->_value;
		}

		// Modifiers
		void push_back (const value_type& val){
			if (this->_size == 0)
				_insertBeginning(val);
			else{
				Node<value_type> *newNode = _createNode(val);
				this->_last->_next = newNode;
				newNode->_prev = this->_last;
				this->_last = newNode;
				this->_size++;
			}
		}

		void push_front (const value_type& val){
			if (this->size == 0)
				_insertBeginning(val);
			else{
				Node<value_type> *newNode = _createNode(val);
				this->_first->_prev = newNode;
				newNode->_next = this->_first;
				this->_first = newNode;
				this->_size++;
			}
		}

		void pop_front(){ // ub
			Node<value_type> *tmp = this->_first;
			this->_first = this->_first->_next;
			this->_first->_prev = NULL;
			this->_size--;
			delete tmp;
		}

		void pop_back(){ // ub
			Node<value_type> *tmp = this->_last;
			this->_last = this->_last->_prev;
			this->_last->_next = NULL;
			this->_size--;
			delete tmp;
		}

		// iterator insert (iterator position, const value_type& val);
		// void insert (iterator position, size_type n, const value_type& val);
		// template <class InputIterator>
		// void insert (iterator position, InputIterator first, InputIterator last);
		// iterator erase (iterator position);
		// iterator erase (iterator first, iterator last);
		// void swap (list& x);
		// void resize (size_type n, value_type val = value_type());
		
		void clear(){
			if (empty())
				return;
			Node<value_type> *tmp = this->_first;
			while (tmp->_next != NULL){
				this->_size--;
				tmp = tmp->_next;
				delete tmp->_prev;
			}
			delete tmp;
			this->_size--;
		}

		
		// template <class InputIterator>
		// 	void assign (InputIterator first, InputIterator last);
	
		void assign (size_type n, const value_type& val){
			clear();
			this = list(n, val);
		}

	private:


		nodeAllocator_t _nodeAllocator;
		allocator_type _allocator;
		Node<value_type> *_first;
		Node<value_type> *_last;
		size_t _size;
		
		
		
		Node<value_type>	*_createNode(const value_type &val = value_type()){
			Node<value_type>	*newNode = this->_nodeAllocator.allocate(1);
			newNode->_next = NULL;
			newNode->_prev = NULL;
			newNode->_value = val;
			return newNode;
		}

		void				_insertBeginning(const value_type &val = value_type()){
			this->_first = _createNode(val);
			this->_last = this->_first;
			this->_size++;
		}
	};

}

#endif