#pragma once

#include <iostream>

namespace ft {

	template <class T>
	struct RBtreeNode {

		RBtreeNode*	_previous;
		RBtreeNode*	_left;
		RBtreeNode*	_right;
		T		_data;
		bool	_is_red;
		Node(T& data, RBtreeNode* previous = NULL, RBtreeNode* left = NULL, RBtreeNode* right = NULL, bool is_red = true)
		:	_data(data), _previous(previous), _left(left), _right(right), _is_red(is_red) {}
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
				return !(*this == other);
			}

			T& operator * () {
				return _node->_data;
			}

			T* operator -> () {
				return &(_node->_data);
			}

			RBTreeIterator& operator ++ () {

				
			}

			RBTreeIterator& operator ++ (int) {

				RBTreeIterator tmp(*this);
				++*this;
				return tmp;
			}

			RBTreeIterator& operator -- () {

				
			}

	};

	template <class T, class Compare = std::less<T>, class Allocator = std::allocator<T> >
	class RBTree {

		public:

			typedef T	value_type;
			typedef unsigned long	size_type;
			typedef Allocator	allocator_type;
			typedef Compare	comparator_type;
			typedef RBtreeNode<T> Node;
			// TO DO: typedef iterators

		private:

		Node* _root;	
	};

}