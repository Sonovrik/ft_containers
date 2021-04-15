
#include <iostream>

template <class Category, class T, class Distance = ptrdiff_t,
		class Pointer = T*, class Reference = T& > class iterator {

private:

	


public:

		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;

};

