#pragma once

#include <iostream>

namespace ft {

	template <class T, class Compare = std::less<T>, class Allocator = std::allocator<T> >
	class RBTree {

		public:

			typedef T	value_type;
			typedef unsigned long	size_type;
			typedef Allocator	allocator_type;
			typedef Compare	comparator_type;
			// TO DO: typedef iterators

		private:

			struct Node {

				Node*	_previous;
				Node*	_left;
				Node*	_right;
				T		_data;
				bool	_is_red;
				Node(T& data, Node* previous = NULL, Node* left = NULL, Node* right = NULL, bool is_red = true)
				:	_data(data), _previous(previous), _left(left), _right(right), _is_red(is_red) {}
			};

		Node* _root;	
	};

}