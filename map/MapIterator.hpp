#include "map_base.hpp"

namespace ft {

	template <class K, class T>
	class MapIterator {
	public:
		typedef std::bidirectional_iterator_tag			iterator_category;
		typedef std::pair<const K, T>					value_type;
		typedef value_type *							pointer;
		typedef std::pair<const K, T> &					reference;
		typedef std::ptrdiff_t							difference_type;

		typedef __base<const K, T>						map_node;

	private:
		map_node *_node;
		map_node *_nill;

	public:
		MapIterator() : _node(NULL), _nill(NULL) { }

		explicit MapIterator(map_node *node, map_node *nill) : _node(node), _nill(nill) { }

		MapIterator(const MapIterator &other) : _node(other._node), _nill(other._nill) { }

		~MapIterator() { }

		MapIterator &operator=(const MapIterator &other) {
			if (this != &other) {
				_node = other._node;
				_nill = other._nill;
			}
			return *this;
		}

		reference operator*() const {
			return _node->data;
		}

		pointer operator->() const {
			return &(operator*());
		}

		MapIterator &operator++() {
			_node = map_node::_next_node(_node, _nill);
			return *this;
		}

		MapIterator operator++(int) {
			MapIterator tmp = *this;
			_node = map_node::_next_node(_node, _nill);
			return tmp;
		}

		MapIterator &operator--() {
			_node = map_node::_prev_node(_node, _nill);
			return *this;
		}

		MapIterator operator--(int) {
			MapIterator tmp = *this;
			_node = map_node::_prev_node(_node, _nill);
			return tmp;
		}

		const map_node *base() const {
			return _node;
		}

		const map_node *base_nill() const {
			return _nill;
		}

		friend
		bool operator==(const MapIterator &lhs, const MapIterator &rhs) {
			return (lhs._node == rhs._node && lhs._nill == rhs._nill);
		}

		friend
		bool operator!=(const MapIterator &lhs, const MapIterator &rhs) {
			return (lhs._node != rhs._node || lhs._nill != rhs._nill);
		}

	};

	template <class K, class T>
	class ConstMapIterator {
	public:
		typedef std::bidirectional_iterator_tag			iterator_category;
		typedef const std::pair<const K, T>				value_type;
		typedef const std::pair<const K, T> &			reference;
		typedef value_type *							pointer;
		typedef std::ptrdiff_t							difference_type;

		typedef const __base<const K, T>				map_node;

	private:
		map_node *_node;
		map_node *_nill;

	public:
		ConstMapIterator() : _node(NULL), _nill(NULL) { }

		explicit ConstMapIterator(const map_node *node, const map_node *nill) : _node(node), _nill(nill) { }

		ConstMapIterator(const ConstMapIterator &other) : _node(other._node), _nill(other._nill) { }

		ConstMapIterator(const MapIterator<K, T> &other) : _node(other.base()), _nill(other.base_nill()) { }

		~ConstMapIterator() { }

		ConstMapIterator &operator=(const ConstMapIterator &other) {
			if (this != &other) {
				_node = other._node;
				_nill = other._nill;
			}
			return *this;
		}

		ConstMapIterator &operator=(const MapIterator<K, T> &other) {
			_node = other.base();
			_nill = other.base_nill();
			return *this;
		}

		reference operator*() const {
			return _node->data;
		}

		pointer operator->() const {
			return &(operator*());
		}

		ConstMapIterator &operator++() {
			_node = map_node::_next_node(_node, _nill);
			return *this;
		}

		ConstMapIterator operator++(int) {
			ConstMapIterator tmp = *this;
			_node = map_node::_next_node(_node, _nill);
			return tmp;
		}

		ConstMapIterator &operator--() {
			_node = map_node::_prev_node(_node, _nill);
			return *this;
		}

		ConstMapIterator operator--(int) {
			ConstMapIterator tmp = *this;
			_node = map_node::_prev_node(_node, _nill);
			return tmp;
		}

		map_node *base() const {
			return _node;
		}

		map_node *base_nill() const {
			return _nill;
		}

		friend
		bool operator==(const ConstMapIterator &lhs, const ConstMapIterator &rhs) {
			return (lhs._node == rhs._node && lhs._nill == rhs._nill);
		}

		friend
		bool operator!=(const ConstMapIterator &lhs, const ConstMapIterator &rhs) {
			return (lhs._node != rhs._node || lhs._nill != rhs._nill);
		}

	};

}