#include "../support_classes.hpp"


namespace ft{

	template <class Alloc>
	class MapIterator {
	public:
		typedef Alloc											allocator_type;
		typedef std::bidirectional_iterator_tag					iterator_category;
		typedef typename allocator_type::difference_type		difference_type;
		typedef typename allocator_type::value_type				value_type;
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::reference				reference;

		typedef __base<Alloc>									map_node;

	private:
		map_node *_node;
		const map_node *_nill;

		void 	_next_iter(map_node &node, const map_node* nill){
			if (node->right != nill)
				node = get_min(node->right, nill);
			else{
				map_node *tmp = _node;
				_node = _node->parent;
				while(_node->left != tmp){
					tmp = _node;
					_node = _node->parent;
				}
			}
		}

		void 	_prev_iter(map_node &node, const map_node* nill){
			if (node->left != nill)
				node = get_max(node->left, nill);
			else
				_node = _node->parent;
		}

	public:
		MapIterator(): _node(NULL), _nill(NULL) {}

		explicit MapIterator(const map_node *node, const map_node *nill): _node(node), _nill(nill) {}

		MapIterator(const MapIterator &other): _node(other._node), _nill(other._nill) {}

		~MapIterator() {}

		MapIterator &operator=(const MapIterator &other){
			if (this != &other){
				_node = other._node;
				_nill = other._nill;
			}
			return *this;
		}

		reference operator*() const {
			return _node->data;
		}

		pointer operator->() const {
			return &(_node->data);
		}

		// incs decs
		MapIterator &operator++(){
			_next_iter(_node, _nill);
			return *this;
		}

		MapIterator  operator++(int) {
			MapIterator tmp = *this;
			_next_iter(_node, _nill);
			return tmp;
		}

		MapIterator &operator--() {
			_prev_iter(_node, _nill);
			return *this;
		}

		MapIterator  operator--(int) {
			MapIterator tmp = *this;
			_prev_iter(_node, _nill);
			return tmp;
		}

		map_node *base() const{
			return _node;
		}

		map_node * base_nill() const{
			return _nill;
		}

		friend
		bool operator==(const MapIterator &lhs, const MapIterator &rhs){
			return (lhs._node == rhs._node && lhs._nill == rhs._nill);
		}

		friend
		bool operator!=(const MapIterator &lhs, const MapIterator &rhs){
			return (lhs._node != rhs._node || lhs._nill != rhs._nill);
		}

	};



}