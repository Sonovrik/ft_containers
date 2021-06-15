#pragma once

namespace ft{
	template < class Key,                                     // map::key_type
			class T,                                       // map::mapped_type
			class Compare = less<Key>,                     // map::key_compare
			class Alloc = allocator<pair<const Key,T> >    // map::allocator_type
	> class map{
	public:
		typedef Key													key_type;
		typedef T													mapped_type;
		typedef Compare												key_compare;
		typedef Alloc												allocator_type;
		typedef typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::const_pointer				const_pointer;
		typedef typename allocator_type::pointer					pointer;

		typedef typename allocator_type::difference_type			difference_type;
		typedef typename allocator_type::size_type					size_type;
		typedef std::pair<const key_type, mapped_type>				value_type;

		// typedef iterators

		// in C++98, it is required to inherit binary_function<value_type,value_type,bool>
		class value_compare : public binary_function<value_type, value_type, bool> {
		private:
			friend class	map;
		protected:
			key_compare		comp;
			value_compare(key_compare c) : comp(c) {}
		public:
			typedef bool		result_type;
			typedef value_type	first_argument_type;
			typedef value_type	second_argument_type;
			bool	operator()(value_type const &x, value_type const &y) const
			{	return (comp(x.first, y.first));	}
		};

	private:


	public:



	};

}