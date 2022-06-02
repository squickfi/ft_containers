#pragma once

#include <iostream>
#include "ft_utility.hpp"
#include "ft_iterator.hpp"

namespace ft {

	template <class T>
	struct RBtreeNode {

		RBtreeNode*	_previous;
		RBtreeNode*	_left;
		RBtreeNode*	_right;
		T		_value;
		bool	_is_red;
		explicit RBtreeNode(const T& data, RBtreeNode* previous = NULL, RBtreeNode* left = NULL, RBtreeNode* right = NULL, bool is_red = true)
		:	_value(data), _previous(previous), _left(left), _right(right), _is_red(is_red) {}
	};

	template <class T>
	class RBTreeIterator {

		public:

			typedef typename ft::iterator_traits<T*>::value_type 			value_type;
			typedef typename ft::iterator_traits<T*>::reference 			reference;
			typedef typename ft::iterator_traits<T*>::pointer				pointer;
			typedef typename ft::iterator_traits<T*>::difference_type		difference_type;
			typedef typename ft::iterator_traits<T*>::iterator_category		iterator_category;
			typedef typename ft::iterator_traits<T*>::pointer				iterator_type;
			typedef RBtreeNode<T>											Node;
	
		private:

			Node*	_node;
			Node*	_root;

		public:

			RBTreeIterator() : _node(NULL), _root(NULL) {}

			RBTreeIterator(const RBTreeIterator& other)
			:	_node(other._node), _root(other._root) {}

			RBTreeIterator(Node* node, Node* root)
			:	_node(node), _root(root) {}

			RBTreeIterator(Node* root)
			:	_node(root), _root(root) {}

			RBTreeIterator& operator = (const RBTreeIterator& other) {
				_node = other._node;
				_root = other._root;
				return *this;
			}
			~RBTreeIterator() {}

			Node* getNode() const { return _node; }
			Node* getRoot() const { return _root; }

			bool operator == (const RBTreeIterator& other) {
				return _node == other._node && _root == other._root;
			}

			bool operator != (const RBTreeIterator& other) {
				return *this != other;
			}

			reference operator * () {
				return _node->_value;
			}

			pointer operator -> () {
				return &(_node->_value);
			}

			RBTreeIterator& operator ++ () {

				if (!_node) {
					if (_root) {
						_node = _root;
						while (_node->_left)
							_node = _node->_left;
					}
					return *this;
				}
				if (_node->_right) {
					_node = _node->_right;
					while (_node->_left)
						_node = _node->_left;
				}
				else {
					while (_node->_previous && _node->_previous->_right == _node)
						_node = _node->_previous;
					_node = _node->_previous;
				}
				return *this;
			}

			RBTreeIterator operator ++ (int) {

				RBTreeIterator tmp(*this);
				++*this;
				return tmp;
			}

			RBTreeIterator& operator -- () {

				if (!_node) {
					if (_root) {
						_node = _root;
						while (_node->_right)
							_node = _node->_right;
					}
					return *this;
				}
				if (_node->_left) {
					_node = _node->_left;
					while (_node->_right)
						_node = _node->_right;
				}
				else {
					while (_node->_previous && _node->_previous->_left == _node)
						_node = _node->_previous;
					_node = _node->_previous;
				}
				return *this;
			}

			RBTreeIterator operator -- (int) {

				RBTreeIterator tmp(*this);
				--*this;
				return tmp;
			}
	};

	template <class T, class Compare = std::less<T>, class Allocator = std::allocator<RBtreeNode<T> > >
	class RBTree {

		public:

			typedef T										value_type;
			typedef unsigned long							size_type;
			typedef Allocator								allocator_type;
			typedef Compare									comparator_type;
			typedef RBtreeNode<T>							Node;
			typedef value_type&								reference;
			typedef const value_type&						const_reference;
			typedef typename allocator_type::pointer		pointer;
			typedef typename allocator_type::const_pointer	const_pointer;
			typedef RBTreeIterator<pointer>					iterator;
			typedef RBTreeIterator<const_pointer>			const_iterator;

		private:

			Node*			_root;
			allocator_type	_alloc;
			comparator_type	_comp;
			size_type 		_size;

			void leftRotate(Node* node) {

				if (!node->_right)
					return;
				Node* tmp = node->_right->_left;
				node->_right->_previous = node->_previous;
				node->_right->_left = node;
				node->_previous = node->_right;
				node->_right = tmp;
			}

			void rightRotate(Node* node) {

				if (!node->_left)
					return;
				Node* tmp = node->_left->_right;
				node->_left->_previous = node->_previous;
				node->_left->_right = node;
				node->_previous = node->_left;
				node->_left = tmp;
			}

			Node* createNode(const T& data, Node* previous = NULL, Node* left = NULL, Node* right = NULL, bool is_red = true) {

				Node* node;
				try {
					node = _alloc.allocate(1);
				} catch (...) {
					throw "can't create a node, allocation exception";
				}
				try {
					_alloc.construct(node, Node(data, previous, left, right, is_red));
				} catch (...) {
					_alloc.deallocate(node, 1);
					throw "can't create a node, constructor exception";
				}
				++_size;
				return node;
			}

			void removeNode(Node* node) {
				_alloc.destroy(node);
				_alloc.deallocate(node, 1);
				--_size;
			}

		public:

			void clearTree(Node* node) {

				if (!node)
					return;
				clearTree(node->_left);
				clearTree(node->_right);
				removeNode(node);
			}

			RBTree() : _root(NULL), _size(0) {}

			RBTree(const RBTree& other) : _size(other._size) {
				iterator endIt = other.end();
				for (iterator it = other.begin(); it != endIt; ++it) {
					insertNode(*it);
				}
			}

			RBTree& operator = (const RBTree& other) {

				clearTree(_root);
				iterator endIt = other.end();
				for (iterator it = other.begin(); it != endIt; ++it) {
					insertNode(*it);
				}
				_size = other._size;
				return *this;
			}

			~RBTree() {
				clearTree(_root);
			}

			Node* findNode(value_type value) {

				Node* node = _root;
				while (node) {
					if (_comp(node->_value, value)) { // TODO: check this condition
						node = node->_right;
					}
					else if (value, _comp(node->_value)) {
						node = node->_left;
					}
					else {
						return node;
					}
				}
				return NULL;
			}

		private:

			bool isRed(Node* node) {
				return node && node->_is_red;
			}

			bool isLeftChild(Node* node) {
				return node && node->_previous && node == node->_previous->_left;
			}

			void balanceInsert(Node* node) {

				node->_is_red = node != _root;
				while (node != _root && node->_previous->_is_red) {
					if (isLeftChild(node->_previous)) {
						Node* nodeToCheck = node->_previous->_previous->_right;
						if (nodeToCheck && nodeToCheck->_is_red) {
							node = node->_previous;
							node->_is_red = false;
							node = node->_previous;
							node->_is_red = node != _root;
							nodeToCheck->_is_red = false;
						}
						else {
							if (!isLeftChild(node->_previous)) {
								node = node->_previous;
								leftRotate(node);
							}
							node = node->_previous;
							node->_is_red = false;
							node = node->_previous;
							node->_is_red = true;
							rightRotate(node);
							break;
						}
					}
					else {
						Node* nodeToCheck = node->_previous->_previous->_left;
						if (nodeToCheck && nodeToCheck->_is_red) {
							node = node->_previous;
							node->_is_red = false;
							node = node->_previous;
							node->_is_red = node != _root;
							nodeToCheck->_is_red = false;
						}
						else {
							if (isLeftChild(node)) {
								node = node->_previous;
								rightRotate(node);
							}
							node = node->_previous;
							node->_is_red = false;
							node = node->_previous;
							node->_is_red = true;
							leftRotate(node);
							break;
						}
					}
					if (!node->_previous) {
						_root = node;
					}
				}
			}

			void swapNodes(Node* n1, Node* n2) {

				std::swap(n1->_is_red, n2->_is_red);

				if (n1->_left) {
					n1->_left->_previous = n2;
				}
				if (n2->_left) {
					n2->_left->_previous = n1;
				}
				std::swap(n1->_left, n2->_left);

				if (n1->_right) {
					n1->_right->_previous = n2;
				}
				if (n2->_right) {
					n2->_right->_previous = n1;
				}
				std::swap(n1->_right, n2->_right);

				if (n1->_previous) {
					isLeftChild(n1) ?
						n1->_previous->_left = n2 : n1->_previous->_right = n2;
				}
				if (n2->_previous) {
					isLeftChild(n2) ?
						n2->_previous->_left = n1 : n2->_previous->_right = n1;
				}
				std::swap(n1->_previous, n2->_previous);
			}

			void balanceLeftErase(Node* nodeParent) {

				if (!nodeParent) {
					return;
				}
				if (isRed(nodeParent->_right)) {
					nodeParent->_right->_is_red = false;
					nodeParent->_is_red = true;
					leftRotate(nodeParent);
					nodeParent = nodeParent->_previous;
				}
				if (nodeParent->_right && !isRed(nodeParent->_right) && !isRed(nodeParent->_left)) {
					bool isParentRed = nodeParent->_is_red;
					nodeParent->_right->_is_red = true;
					nodeParent->_is_red = false;
					if (isParentRed) {
						balanceInsert(nodeParent);
					}
				}
				if (nodeParent->_right && isRed(nodeParent->_right->_left)) {
					std::swap(nodeParent->_right->_is_red, nodeParent->_right->_left->_is_red);
					rightRotate(nodeParent->_right);
				}
				if (nodeParent->_right && isRed(nodeParent->_right->_right)) {
					nodeParent->_right->_is_red = nodeParent->_is_red;
					nodeParent->_right->_right->_is_red = false;
					nodeParent->_is_red = false;
					rightRotate(nodeParent);
				}
			}

			void balanceRightErase(Node* nodeParent) {

				if (!nodeParent) {
					return;
				}
				if (isRed(nodeParent->_left)) {
					nodeParent->_left->_is_red = false;
					nodeParent->_is_red = true;
					rightRotate(nodeParent);
					nodeParent = nodeParent->_previous;
				}
				if (nodeParent->_left && !isRed(nodeParent->_left) && !isRed(nodeParent->_right)) {
					bool isParentRed = nodeParent->_is_red;
					nodeParent->_left->_is_red = true;
					nodeParent->_is_red = false;
					if (isParentRed) {
						balanceInsert(nodeParent);
					}
				}
				if (nodeParent->_left && isRed(nodeParent->_left->_right)) {
					std::swap(nodeParent->_left->_is_red, nodeParent->_left->_right->_is_red);
					leftRotate(nodeParent->_left);
				}
				if (nodeParent->_left && isRed(nodeParent->_left->_left)) {
					nodeParent->_left->_is_red = nodeParent->_is_red;
					nodeParent->_left->_left->_is_red = false;
					nodeParent->_is_red = false;
					leftRotate(nodeParent);
				}
			}

		public:

			Node *getRoot() {
				return _root;
			}

			ft::pair<Node*, bool> insertNode(Node* node, const T& value) {

				Node* parent = node ? node->_previous : NULL;
				bool isLeft = true;
				while (node) {
					if (_comp(value, node->_value)) {
						parent = node;
						node = node->_left;
						isLeft = true;
					}
					else if (_comp(node->_value, value)) {
						parent = node;
						node = node->_right;
						isLeft = false;
					}
					else {
						return ft::make_pair(node, false);
					}
				}
				try {
					node = createNode(value, parent); // TODO throw exceptions not const char*!
				} catch (...) {
					clearTree(_root);
					throw;
				}
				if (!_root) {
					_root = node;
				}
				if (parent) {
					isLeft ? parent->_left = node : parent->_right = node;
				}
				balanceInsert(node);
				++_size;
				return ft::make_pair(node, true);
			}

			void eraseNode(Node* node) {

				bool isRemovedRed = node->_is_red;
				bool isRemovedLeft = isLeftChild(node);
				Node* nodeToPaste = node->_right;
				Node* nodeParent = node->_previous;

				if (node->_left && node->_right) {
					while (nodeToPaste->_left) {
						nodeToPaste = nodeToPaste->_left;
					}
					nodeToPaste->_previous = nodeParent;
					nodeToPaste->_left = node->_left;
					nodeToPaste->_right = node->_right;
				}
				else if (node->_left || node->_right) {
					nodeToPaste = node->_left ? node->_left : node->_right;
					nodeToPaste->_previous = nodeParent;
					nodeToPaste->_is_red = false;
				}
				if (nodeParent) {
					isLeftChild(node) ?
						nodeParent->_left = nodeToPaste : nodeParent->_right = nodeToPaste;
				}
				removeNode(node);
				if (!isRemovedRed) {
					isRemovedLeft ? balanceLeftErase(nodeParent) : balanceRightErase(nodeParent);
				}
				if (node == _root) {
					_root = nodeToPaste;
				}
				--_size;
			}

			RBTreeIterator<T> begin() {

				Node* tmp = _root;
				if (tmp) {
					while (tmp->_left) {
						tmp = tmp->_left;
					}
				}
				RBTreeIterator<T> _begin(tmp);
				return _begin;
			}

			RBTreeIterator<T> end() {

				RBTreeIterator<T> _end(NULL);
				return _end;
			}

			size_type size() {
				return _size;
			}
	};

}















