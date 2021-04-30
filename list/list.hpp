#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include "../utils/utils.hpp"
#include "../utils/iterators.hpp"
#include "../utils/const_iterator.hpp"
#include "../utils/reverse_iterator.hpp"
#include "../utils/const_reverse_iterator.hpp"


namespace ft {

	template <class T, class Alloc = std::allocator<T> > class list {
	public:

		typedef Alloc											allocator_type;
		typedef	T												value_type;
		typedef typename allocator_type::reference				reference;
		typedef typename allocator_type::const_reference		const_reference;
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::const_pointer			const_pointer;
		typedef ListIterator<T>									iterator;
		typedef ConstListIterator<T>							const_iterator;
		typedef ReverseListIterator<T>							reverse_iterator;
		typedef ConstReverseListIterator<T>						const_reverse_iterator;
		typedef typename std::ptrdiff_t							difference_type;
		typedef size_t											size_type;

		typedef std::allocator< Node<value_type> > nodeAllocator_t;

		explicit list(const allocator_type &alloc = allocator_type()):
			_allocator(alloc),
			_size(0){
			this->_root = this->_nodeAllocator.allocate(1);
			this->_root->_next = NULL;
			this->_root->_prev = NULL;
		}

		explicit list(size_type n, const value_type &val = value_type(),
			const allocator_type &alloc = allocator_type()):
				_allocator(alloc),
				_size(0){
				this->_root = this->_nodeAllocator.allocate(1);
				this->_root->_next = NULL;
				this->_root->_prev = NULL;
				for (size_t i = 0; i < n; ++i)
					push_back(val);
		}

		 template <class InputIterator>
		 list(InputIterator first, InputIterator last,
				const allocator_type &alloc = allocator_type()
				) {
			iterator it = first;
			while (it != last){
				push_back(*it);
				it++;
			}
		}

		// list(const list &x){

		// }


		~list(){
			clear();
			delete this->_root;
		}

		// list &operator=(const list &x);

//		Iterators
		iterator begin(){
			iterator tmp(this->_root->_next);
			return tmp;
		}

		const_iterator begin() const{
			const_iterator tmp(this->_root->_next);
			return tmp;
		}

		iterator end(){
			iterator tmp(this->_root->_prev);
			return tmp;
		}

		const_iterator end() const{
			const_iterator tmp(this->_root->_prev);
			return tmp;
		}


		 reverse_iterator rbegin(){
			 reverse_iterator tmp(this->_root->_prev);
			 return tmp;
		}

		const_reverse_iterator rbegin() const{
			const_reverse_iterator tmp(this->_root->_prev);
			return tmp;
		}

		reverse_iterator rend(){
			reverse_iterator tmp(this->_root->_next);
			return tmp;
		}

		const_reverse_iterator rend() const{
			const_reverse_iterator tmp(this->_root->_next);
			return tmp;
		}


		// Capacity
		bool empty() const{
			if (!this->_size)
				return true;
			return false;
		}

		size_type size() const{
			return this->_size;
		}

		size_type max_size() const{
			return size_type(-1) / sizeof(value_type);
		}

		// Element access
		reference front(){
			return this->_root->_next->_value;
		}

		const_reference front() const{
            return this->_root->_next->_value;
		}

		reference back(){
			return this->_root->_prev->_value;
		}

		const_reference back() const{
			return this->_root->_prev->_value;
		}

		// Modifiers
		void push_back (const value_type& val){
			if (this->_size == 0)
				_insertBeginning(val);
			else{
				Node<value_type> *newNode = _createNode(val);
				newNode->_prev = this->_root->_prev;
                this->_root->_prev->_next = newNode;

                newNode->_next = this->_root;
                this->_root->_prev = newNode;
                this->_size++;
			}
		}

		void push_front (const value_type& val){
            if (this->_size == 0)
                _insertBeginning(val);
            else{
                Node<value_type> *newNode = _createNode(val);
                newNode->_next = this->_root->_next;
                this->_root->_next->_prev = newNode;

                newNode->_prev = this->_root;
                this->_root->_next = newNode;
                this->_size++;
            }
		}

		void pop_front(){
            Node<value_type> *tmp = this->_root->_next;
            tmp->_next->_prev = this->_root;
            this->_root->_next = tmp->_next;
			this->_size--;
			delete tmp;
		}

		void pop_back(){
            Node<value_type> *tmp = this->_root->_prev;
            tmp->_prev->_next = this->_root;
            this->_root->_prev = tmp->_prev;
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
//		void resize (size_type n, value_type val = value_type()){
//		    if (this->_size <= n){
//		        while (this->_size != n)
//                    push_back(val);
//		    }
//		    else{
//                Node<value_type> *tmp = this->_root->_next;
//                size_t i = 0;
//                while (i != n){
//                    tmp = tmp->_next;
//                    i++;
//                }
//                this->_root->_prev = tmp;
//                Node<value_type> *tmp2;
//                while (tmp != this->_root){
//                    tmp2 = tmp;
//                    tmp = tmp->_next;
//                    delete tmp2;
//                    this->_size--;
//                }
//            }
//		}
		
		void clear(){
			if (empty())
				return;
			Node<value_type> *tmp = this->_root->_next;
			Node<value_type> *tmp2;
			while (tmp != this->_root){
			    tmp2 = tmp;
			    tmp = tmp->_next;
			    delete tmp2;
			    this->_size--;
			}
			this->_root->_next = NULL;
			this->_root->_prev = NULL;
		}

		
		// template <class InputIterator>
		// 	void assign (InputIterator first, InputIterator last);
	
		void assign (size_type n, const value_type& val){
			clear();
			delete this->_root;
			this = list(n, val);
		}

	private:
		nodeAllocator_t _nodeAllocator;
		allocator_type _allocator;
		Node<value_type> *_root;
		size_t _size;
		
		
		
		Node<value_type>	*_createNode(const value_type &val = value_type()){
			Node<value_type>	*newNode = this->_nodeAllocator.allocate(1);
			newNode->_next = NULL;
			newNode->_prev = NULL;
			newNode->_value = val;
			return newNode;
		}

		void				_insertBeginning(const value_type &val = value_type()){
            this->_root->_next = _createNode(val);
            this->_root->_prev = this->_root->_next;
            this->_size++;
		}
	};

}

#endif