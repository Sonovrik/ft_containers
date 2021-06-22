#pragma once

#include <deque>

namespace ft {


	template <class T, class Container = std::deque<T> >
	class stack {
	public:
		typedef T									value_type;
		typedef Container							container_type;
		typedef typename container_type::size_type	size_type;

	private:
		container_type c;

	public:
		explicit stack(const container_type &ctnr = container_type()) : c(ctnr) { }

		bool empty() const { return c.empty(); }

		size_type size() const { return c.size(); }

		value_type &top() { return c.back(); }

		const value_type &top() const { return c.back(); }

		void push(const value_type &val) { this->c.push_back(val); }

		void pop() { c.pop_back(); }
	};

	template <class T, class Container>
	bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return (lhs.c == rhs.c);
	}

	template <class T, class Container>
	bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return !(lhs == rhs);
	}

	template <class T, class Container>
	bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return (lhs.c < rhs.c);
	}

	template <class T, class Container>
	bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return !(rhs < lhs);
	}

	template <class T, class Container>
	bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return (rhs < lhs);
	}

	template <class T, class Container>
	bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return !(lhs < rhs);
	}

}