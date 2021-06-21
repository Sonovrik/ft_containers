#pragma once

#include <iostream>

namespace ft {

	template <class Key, class Type>
	struct __base {
	private:
		typedef std::pair<Key, Type>		value_type;
		typedef __base<Key, Type>			map_node;

		__base() : parent(NULL), left(NULL), right(NULL), isRed(false) { }

	public:
		value_type data;
		map_node *parent;
		map_node *left;
		map_node *right;
		bool isRed;

		__base(map_node *nill, const value_type &data) :
				data(data),
				parent(nill),
				left(nill),
				right(nill),
				isRed(false) { }

		__base(const __base &x) :
				data(x.data),
				parent(x.parent),
				left(x.left),
				right(x.right),
				isRed(x.isRed) { }

		__base &operator=(const __base &other) {
			if (this != &other) {
				this->data = other.data;
				this->parent = other.parent;
				this->left = other.left;
				this->right = other.right;
				this->isred = other.isred;
			}
			return (*this);
		}

		~__base() { }

		static map_node *get_min(map_node *node, const map_node *nill) {
			while (node != nill && node->left != nill)
				node = node->left;
			return node;
		}

		static map_node *get_max(map_node *node, const map_node *nill) {
			while (node != nill && node->right != nill)
				node = node->right;
			return node;
		}

		template <class NodePtr>
		static NodePtr _next_node(NodePtr node, NodePtr nill) {
			if (node->right != nill)
				node = get_min(node->right, nill);
			else if (node == nill->parent) // check end() - 1
				node = nill;
			else {
				const map_node *tmp = node;
				node = node->parent;
				while(node->left != tmp){
					tmp = node;
					node = node->parent;
				}
			}
			return node;
		}

		template <class NodePtr>
		static NodePtr _prev_node(NodePtr node, NodePtr nill) {
			if (node == nill)
				node = nill->parent;
			else if (node->left != nill)
				node = get_max(node->left, nill);
			else if (nill->left == node) // check begin()
				node = nill;
			else{
				while (node->parent != nill && node == node->parent->left)
					node = node->parent;
				node = node->parent;
			}
			return node;
		}

	};


}