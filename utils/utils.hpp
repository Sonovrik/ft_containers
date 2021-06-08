#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft{
template <typename T>
struct		Node {
	T				_value;
	Node			*_next;
	Node			*_prev;
};
	template< typename S >
	void	itemswap(S& var1, S& var2) {
		S tmpvar = var1;
		var1 = var2;
		var2 = tmpvar;
	}
}


#endif