#pragma once
namespace ft{

	template <class Iterator>
	class iterator_traits{
	public:
		typedef typename Iterator::difference_type	difference_type;
		typedef typename Iterator::value_type		value_type;
		typedef typename Iterator::pointer			pointer;
		typedef typename Iterator::reference		reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};


	template <class T>
	class iterator_traits <T*>{
	public:
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	template<class T>
	class iterator_traits<const T*> {
	public:
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef std::random_access_iterator_tag iterator_category;
	};


	template<class Iterator >
	class ReverseIterator {
	public:
		typedef Iterator iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
		typedef typename iterator_traits<Iterator>::value_type value_type;
		typedef typename iterator_traits<Iterator>::difference_type difference_type;
		typedef typename iterator_traits<Iterator>::pointer pointer;
		typedef typename iterator_traits<Iterator>::reference reference;

	private:
		Iterator _it;

	public:
		ReverseIterator(): _it(){}
		explicit ReverseIterator (iterator_type it): _it(it) {}

		template<class _Iter>
		ReverseIterator(const ReverseIterator<_Iter>& rev_it): _it(rev_it.base()) {}

		~ReverseIterator() {}

		iterator_type base() const{
			return this->_it;
		}

		reference operator*() const{
			iterator_type tmp = this->_it;
			return *tmp;
		}

		pointer operator->() const{
			return &(operator*());
		}

		ReverseIterator operator+(difference_type n) const{
			return ReverseIterator(this->_it - n);
		}

		ReverseIterator operator-(difference_type n) const{
			return ReverseIterator(this->_it + n);
		}

		ReverseIterator &operator++(){
			--this->_it;
			return *this;
		}

		ReverseIterator operator++(int){
			ReverseIterator tmp = *this;
			--this->_it;
			return tmp;
		}

		ReverseIterator &operator--(){
			++this->_it;
			return *this;
		}

		ReverseIterator operator--(int){
			ReverseIterator tmp = this->_it;
			++this->_it;
			return tmp;
		}

		ReverseIterator& operator+=(difference_type n){
			this->_it -= n;
			return *this;
		}

		ReverseIterator& operator-=(difference_type n){
			this->_it += n;
			return *this;
		}

		reference operator[](difference_type n) const {
			return *(*this + n);
		}
	};

	template <class Iterator>
	bool operator==(const ReverseIterator<Iterator>& lhs,
					 const ReverseIterator<Iterator>& rhs) {
		return (lhs.base() == rhs.base());
	}

	template <class Iterator>
	bool operator!=(const ReverseIterator<Iterator>& lhs,
					 const ReverseIterator<Iterator>& rhs){
		return (lhs.base() != rhs.base());
	}

	template <class Iterator>
	bool operator<(const ReverseIterator<Iterator>& lhs,
					 const ReverseIterator<Iterator>& rhs){
		return (lhs.base() < rhs.base());
	}

	template <class Iterator>
	bool operator<=(const ReverseIterator<Iterator>& lhs,
					 const ReverseIterator<Iterator>& rhs){
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator>
	bool operator>(const ReverseIterator<Iterator>& lhs,
					 const ReverseIterator<Iterator>& rhs){
		return (lhs.base() > rhs.base());
	}

	template <class Iterator>
	bool operator>=(const ReverseIterator<Iterator>& lhs,
					 const ReverseIterator<Iterator>& rhs){
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator>
	ReverseIterator<Iterator> operator+ (
			typename ReverseIterator<Iterator>::difference_type n,
			const ReverseIterator<Iterator>& rev_it){
		return (rev_it + n);
	}

	template <class Iterator>
	typename ReverseIterator<Iterator>::difference_type operator- (
			const ReverseIterator<Iterator>& lhs,
			const ReverseIterator<Iterator>& rhs){
		return (lhs - rhs);
	}
}