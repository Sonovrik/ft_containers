
#include <iostream>

namespace ft{

	class random_access_iterator_tag { };

	template<typename T>
	class VectorIterator: public random_access_iterator_tag {
	public:

		typedef T value_type;
		typedef size_t size_type;
		typedef  value_type& reference;
		typedef  const value_type& const_reference;
		typedef  value_type * pointer;
		typedef  value_type const * const_pointer;
		typedef typename std::ptrdiff_t difference_type;

	private:
		pointer _ptr;


	public:
		VectorIterator(): _ptr(NULL) {}

		VectorIterator(VectorIterator const &other): _ptr(other._ptr){}

		VectorIterator(pointer ptr): _ptr(ptr){}

		virtual ~VectorIterator(){}

		VectorIterator	&operator=(VectorIterator const &other){
			if (this != &other)
				this->_ptr = other._ptr;
			return *this;
		}

		VectorIterator &operator++() {
			this->_ptr++;
			return *this;
		}

		VectorIterator operator++(int) {
			VectorIterator tmp(*this);
			this->_ptr++;
			return tmp;
		}

		VectorIterator &operator--() {
			this->_ptr--;
			return *this;
		}

		VectorIterator operator--(int) {
			VectorIterator tmp(*this);
			this->_ptr--;
			return tmp;
		}

		bool	operator==(VectorIterator const &other) const{
			return (this->_ptr == other._ptr);
		}

		bool	operator!=(VectorIterator const &other) const{
			return (this->_ptr != other._ptr);
		}

		reference 	operator*(){
			return *(this->_ptr);
		}

		const_reference	operator*() const{
			return *this->_ptr;
		}

		pointer operator->(){
			return this->_ptr;
		}

		const_pointer operator->() const{
			return this->_ptr;
		}

		VectorIterator operator+(size_type n) const{
			VectorIterator tmp(*this);
			tmp += n;
			return tmp;
		}

		VectorIterator operator-(size_type n) const{
			VectorIterator tmp(*this);
			tmp -= n;
			return tmp;
		}

//		difference_type operator+(VectorIterator const &other) const{
//			return (this->_ptr + other._ptr);
//		}

		difference_type operator-(VectorIterator const &other) const{
			return (this->_ptr - other._ptr);
		}

		bool 	operator<(VectorIterator const &other) const{
			return (this->_ptr < other._ptr);
		}

		bool 	operator>(VectorIterator const &other) const{
			return (this->_ptr > other._ptr);
		}

		bool 	operator<=(VectorIterator const &other) const{
			return (this->_ptr <= other._ptr);
		}

		bool 	operator>=(VectorIterator const &other) const{
			return (this->_ptr <= other._ptr);
		}

		VectorIterator &operator+=(size_type n){
			this->_ptr += n;
			return *this;
		}

		VectorIterator &operator-=(size_type n){
			this->_ptr -= n;
			return *this;
		}

		reference operator[](size_type n){
			return (this->_ptr[n]);
		}

		const_reference operator[](size_type n) const{
			return (this->_ptr[n]);
		}
	};


}