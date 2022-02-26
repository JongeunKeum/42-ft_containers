#ifndef MAPITERATOR_HPP
#define MAPITERATOR_HPP

#include "utils.hpp"
#include "RBTreeNode.hpp"

namespace ft
{
	template <typename T, bool B>
	class MapIterator : public ft::iterator<ft::bidirectional_iterator_tag, T>
	{
	public :
		typedef const T																																			value_type;
		typedef typename ft::choose<B, const T*, T*>::type																	pointer;
		typedef typename ft::choose<B, const T&, T&>::type																	reference;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type		difference_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category	iterator_category;
		typedef ft::RBTreeNode<T>																														node_type;

		MapIterator(node_type* ptr = ft_nullptr) : _node(ptr) {}	// Default constructor
		MapIterator(const MapIterator<T, false>& copy) : _node(copy.base()) {}	// Copy constructor
		MapIterator& operator=(const MapIterator& copy) { if (this != &copy) this->_node = copy.base(); return *this; }	// Assignment operator
		virtual ~MapIterator() {}	// Destructor
		node_type* const & base() const { return _node; }	// Getter

		/**
		 * @brief Operators
		 */
		reference operator*() const { return *_node->value; }
		pointer operator->() const { return _node->value; }

		MapIterator& operator++() {
			node_type* tmp = ft_nullptr;
			if (_node->right_child->value != ft_nullptr) {	// if right_child exists,
				tmp = _node->right_child;
				// search the leftmost of the right_child.
				while (tmp->left_child->value != ft_nullptr)
					tmp = tmp->left_child;
			}
			else {	// if right_child doesn't exist,
				tmp = _node->parent;
				if (tmp->right_child == _node) {	// if current node is right_child,
					while (tmp->parent->right_child == tmp)
						tmp = tmp->parent;
					tmp = tmp->parent;
				}
			}
			_node = tmp;
			return *this;
		}
		MapIterator operator++(int) { MapIterator tmp = *this; ++(*this); return tmp; }

		MapIterator& operator--() {
			node_type* tmp = ft_nullptr;
			if (_node->value == ft_nullptr)
				tmp = _node->parent;
			else if (_node->left_child->value != ft_nullptr) {	// if left_child exists,
				tmp = _node->left_child;
				// search the rightmost of the left_child.
				while (tmp->right_child->value != ft_nullptr)
					tmp = tmp->right_child;
			}
			else {	// if left_child doesn't exist,
				tmp = _node->parent;
				if (tmp->left_child == _node) {	// if current node is left_child,
					while (tmp->parent->left_child == tmp)
						tmp = tmp->parent;
					tmp = tmp->parent;
				}
			}
			_node = tmp;
			return *this;
		}
		MapIterator operator--(int) { MapIterator tmp = *this; --(*this); return tmp; }

		/**
		 * @brief Relational operators
		 */
		bool operator==(const MapIterator& iter) { return _node == iter.base(); }
		bool operator!=(const MapIterator& iter) { return _node != iter.base(); }

	protected :
		node_type* _node;
	};
} // namespace ft

#endif
