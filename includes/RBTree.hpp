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
		RBtreeNode(T& data, RBtreeNode* previous = NULL, RBtreeNode* left = NULL, RBtreeNode* right = NULL, bool is_red = true)
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

			T& operator * () {
				return _node->_value;
			}

			T* operator -> () {
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

			RBTreeIterator& operator ++ (int) {

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
	};

	template <class T, class Compare = std::less<T>, class Allocator = std::allocator<T> >
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

			void clearTree(Node* node) {

				if (!node)
					return;
				clearTree(node->_left);
				clearTree(node->_right);
				_alloc.destroy(node);
				_alloc.deallocate(node, sizeof(Node));
			}

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
					node = _alloc.allocate(sizeof(Node));
				} catch (...) {
					throw "can't create a node, allocation exception";
				}
				try {
					_alloc.construct(node, Node(data, previous, left, right, is_red));
				} catch (...) {
					_alloc.deallocate(node, sizeof(Node));
					throw "can't create a node, constructor exception";
				}
				++_size;
				return node;
			}

			void removeNode(Node* node) {
				_alloc.destroy(node);
				_alloc.deallocate(node, sizeof(Node));
				--_size;
			}

		public:

			RBTree() : _root(NULL) {}

			RBTree(const RBTree& other) {
				iterator endIt = other.end();
				for (iterator it = other.begin(); it != endIt; ++it)
					insertNode(*it); // TODO: insert function, try catch
			}

			RBTree& operator = (const RBTree& other) {

				clearTree(_root);
				iterator endIt = other.end();
				for (iterator it = other.begin(); it != endIt; ++it)
					insertNode(*it); // TODO: try catch
				return *this;
			}

			~RBTree() {
				clearTree(_root);
			}

			Node* findNode(value_type value) {

				Node* node = _root;
				while (node && node->_value != value) {
					if (node->_value == NULL) {
						return NULL;
					}
					if (_comp(node->_value, value)) // TODO: check this condition
						node = node->_right;
					else
						node = node->_left;
				}
				return node;
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
							node->_is_red - true;
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
							node->_is_red - true;
							leftRotate(node);
							break;
						}
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
					if (isLeftChild(n1)) {
						n1->_previous->_left = n2;
					}
					else {
						n1->_previous->_right = n2;
					}
				}
				if (n2->_previous) {
					if (isLeftChild(n2)) {
						n2->_previous->_left = n1;
					}
					else {
						n2->_previous->_right = n1;
					}
				}
				std::swap(n1->_previous, n2->_previous);
			}

			void balanceErase(Node* newNode, Node* nodeParent) {
				// HERE!
			}

		public:

			ft::pair<Node*, bool> insertNode(Node* node, const T& value) {

				Node* parent = node ? node->_previous : NULL;
				while (node) {
					if (_comp(value, node->_value)) {
						parent = node;
						node = node->_left;
					}
					else if (_comp(node->_value, value)) {
						parent = node;
						node = node->_left;
					}
					else {
						return ft::make_pair(node, false);
					}
				}
				node = createNode(value, parent); // TODO try catch
				balanceInsert(node);
				return ft::make_pair(node, true);
			}

			void eraseNode(Node* node) {

				bool isRemovedRed = node->_is_red;
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
				if (!isRemovedRed)
					balanceErase(nodeToPaste, nodeParent); // TODO <--
			}

			//TODO erase
	};

}















