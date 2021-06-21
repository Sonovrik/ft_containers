#pragma once

#include "support_classes.hpp"

namespace ft {

	template <class Iterator>
	class ReverseIterator {
	public:
		typedef Iterator iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category		iterator_category;
		typedef typename iterator_traits<Iterator>::value_type				value_type;
		typedef typename iterator_traits<Iterator>::difference_type			difference_type;
		typedef typename iterator_traits<Iterator>::pointer					pointer;
		typedef typename iterator_traits<Iterator>::reference				reference;

	private:
		iterator_type _it;

	public:
		ReverseIterator() : _it() { }

		explicit ReverseIterator(iterator_type it) : _it(it) { }

		template <class _Iter>
		ReverseIterator(const ReverseIterator<_Iter> &rev_it): _it(rev_it.base()) { }

		~ReverseIterator() { }

		iterator_type base() const {
			return this->_it;
		}

		reference operator*() const {
			iterator_type tmp = this->_it;
			return *(--tmp);
		}

		pointer operator->() const {
			return &(operator*());
		}

		ReverseIterator operator+(difference_type n) const {
			return ReverseIterator(this->_it - n);
		}

		ReverseIterator operator-(difference_type n) const {
			return ReverseIterator(this->_it + n);
		}

		ReverseIterator &operator++() {
			--this->_it;
			return *this;
		}

		ReverseIterator operator++(int) {
			ReverseIterator tmp(*this);
			--this->_it;
			return tmp;
		}

		ReverseIterator &operator--() {
			++this->_it;
			return *this;
		}

		ReverseIterator operator--(int) {
			ReverseIterator tmp(*this);
			++this->_it;
			return tmp;
		}

		ReverseIterator &operator+=(difference_type n) {
			this->_it -= n;
			return *this;
		}

		ReverseIterator &operator-=(difference_type n) {
			this->_it += n;
			return *this;
		}

		reference operator[](difference_type n) const {
			return *(*this + n);
		}
	};

	template <class Iterator>
	bool operator==(const ReverseIterator<Iterator> &lhs,
					const ReverseIterator<Iterator> &rhs) {
		return (lhs.base() == rhs.base());
	}

	template <class Iterator>
	bool operator!=(const ReverseIterator<Iterator> &lhs,
					const ReverseIterator<Iterator> &rhs) {
		return (lhs.base() != rhs.base());
	}

	template <class Iterator>
	bool operator<(const ReverseIterator<Iterator> &lhs,
				   const ReverseIterator<Iterator> &rhs) {
		return (lhs.base() > rhs.base());
	}

	template <class Iterator>
	bool operator<=(const ReverseIterator<Iterator> &lhs,
					const ReverseIterator<Iterator> &rhs) {
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator>
	bool operator>(const ReverseIterator<Iterator> &lhs,
				   const ReverseIterator<Iterator> &rhs) {
		return (lhs.base() < rhs.base());
	}

	template <class Iterator>
	bool operator>=(const ReverseIterator<Iterator> &lhs,
					const ReverseIterator<Iterator> &rhs) {
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator>
	ReverseIterator<Iterator> operator+(
			typename ReverseIterator<Iterator>::difference_type n,
			const ReverseIterator<Iterator> &rev_it) {
		return (rev_it + n);
	}

	template <class Iterator>
	typename ReverseIterator<Iterator>::difference_type operator-(
			const ReverseIterator<Iterator> &lhs,
			const ReverseIterator<Iterator> &rhs) {
		return (rhs.base() - lhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator==(const ReverseIterator<Iterator1> &lhs,
					const ReverseIterator<Iterator2> &rhs) {
		return (lhs.base() == rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator!=(const ReverseIterator<Iterator1> &lhs,
					const ReverseIterator<Iterator2> &rhs) {
		return (lhs.base() != rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator<(const ReverseIterator<Iterator1> &lhs,
				   const ReverseIterator<Iterator2> &rhs) {
		return (lhs.base() > rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator<=(const ReverseIterator<Iterator1> &lhs,
					const ReverseIterator<Iterator2> &rhs) {
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator>(const ReverseIterator<Iterator1> &lhs,
				   const ReverseIterator<Iterator2> &rhs) {
		return (lhs.base() < rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator>=(const ReverseIterator<Iterator1> &lhs,
					const ReverseIterator<Iterator2> &rhs) {
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator1, class Iterator2>
	typename ReverseIterator<Iterator1>::difference_type operator-(
			const ReverseIterator<Iterator1> &lhs,
			const ReverseIterator<Iterator2> &rhs) {
		return (rhs.base() - lhs.base());
	}

}