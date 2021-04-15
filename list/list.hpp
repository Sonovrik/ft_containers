#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>


namespace ft {

	template <class T, class Alloc = std::allocator<T> > class list {
	public:
		typedef std::allocator<Node> nodeAllocator_t;

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




		explicit list(const allocator_type &alloc = allocator_type())
		{
			this->_allocator = alloc;
			this->_size = 0;
			this->_last = this->_nodeAllocator.allocate(1);
			this->_last->_next = NULL;
			this->_last->_prev = NULL;
			this->_first = this->_last;
		};

		explicit list(size_type n, const value_type &val = value_type(),
					const allocator_type &alloc = allocator_type()){
			Node *tmp;
			for (size_t i = 0; i < n; i++){
				tmp = createNode(n);
				tmp->_prev = this->_last;
				this->_last = tmp;


			}
			
			this->_allocator = alloc;
			this->_last = this->_nodeAllocator.allocate(1);
			this->_last->_next = NULL;
			this->_last->_prev = NULL;
			this->_first = this->_last;
			this->_size = n;
		};

		template <class InputIterator>
		list(InputIterator first, InputIterator last,
			 const allocator_type &alloc = allocator_type());

		list(const list &x);
		~list();
		list &operator=(const list &x);

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
		bool empty() const;
		size_type size() const;
		size_type max_size() const;

		// Element access
		reference front();
		const_reference front() const;

		reference back();
		const_reference back() const;

		// Modifiers
		void push_back (const value_type& val){
			Node *newNode = createNode(val);

			// this->
		}

	

	private:

		friend class Node {
			private:
				T _value;
				Node *_next;
				Node *_prev;

			public:
				Node() : _next(NULL), _prev(NULL){};
				~Node(){};
		};

		nodeAllocator_t _nodeAllocator;
		allocator_type _allocator;
		Node *_first;
		Node *_last;
		size_t _size;
		
		
		
		Node	*createNode(const value_type &val = value_type()) const{
			Node	*newNode = this->_nodeAllocator.allocate(1);
			newNode->_next = NULL;
			newNode->_prev = NULL;
			newNode->_value = val;
			return newNode;
		}
	};

}

#endif