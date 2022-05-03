#pragma once

#include <iostream>

namespace ft {

	template <class T>
	struct RBtreeNode {

		RBtreeNode*	_previous;
		RBtreeNode*	_left;
		RBtreeNode*	_right;
		T		_value;
		bool	_is_red;
		Node(T& data, RBtreeNode* previous = NULL, RBtreeNode* left = NULL, RBtreeNode* right = NULL, bool is_red = true)
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

			RBTreeIterator& operator = () {
				_node = other._node;
				_root = other._root;
				return *this;
			}
			~RBTreeIterator() {}

			Node* getNode() const { return _node; }
			Node* getRoot() const { return _root; }

			bool operator == (const RBTreeIterator& other) {
				return _node == other.getNode() && _root == other.getRoot();
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

			Node* createNode(T data) {

				try {
					Node* node = _alloc.allocate(sizeof(Node));
				} catch (...) {
					throw "can't create a node, allocation exception";
				}
				try {
					_alloc.construct(node, data);
				} catch (...) {
					_alloc.deallocate(node, sizeof(Node));
					throw "can't create a node, constructor exception";
				}
				return node;
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

			void balanceLeftChild(Node* node) { // HERE!

				if (node->_previous->_previous) {
					if (node->_previous->_previous->_left == node->_previous) { // isNewNodeParentLeftChild
						if (node->_previous->_previous && node->_previous->_previous->_right->_is_red) {
							node->_previous->_is_red = false;
							node->_previous->_previous->_right->_is_red = false;
						} else {
							node->_previous->_previous->_is_red = true;
							leftRotate(node->_previous->_previous);
						}
					}
					else {

					}
				}
			}

			void balanceRightChild(Node* node) {

			}

			void balanceInsert(Node* node) {

				if (node->_previous && node->_previous->_is_red) {
					node == node->_previous->_left ?						// isNewNodeLeftChild
						balanceLeftChild(node) : balanceRightChild(node);
				}
				//else OK
			}

		public:
			RBTreeIterator<value_type> insert(value_type value) {

				Node* new_node = createNode(value); //TODO try catch
				RBTreeIterator<value_type> it(_root);

				//finding place
				while (*it != NULL) {
					if (_comp(new_node._value, *it)) {
						--it;
					}
					else {
						++it;
					}
				}
				//inserting element
				if (it.getNode()->_previous) {
					if (it.getNode()->_previous->_left == it.getNode()) {
						it.getNode()->_previous->_left = new_node;
					}
					else {
						it.getNode()->_previous->_right = new_node;
					}
				}
				new_node->_previous = it.getNode()->_previous;

				balanceInsert(new_node);

				return RBTreeIterator<value_type> iterator(new_node, _root);
			}

			//TO DO: insert, erase
	};

}















