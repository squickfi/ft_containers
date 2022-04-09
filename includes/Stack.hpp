#pragma once
#include "Vector.hpp"
#include <vector>

namespace ft {

	template <class T, class Container = ft::Vector<T> >
	class Stack {

		public:

			typedef Container							container_type;
			typedef typename Container::value_type		value_type;
			typedef typename Container::size_type		size_type;
			typedef typename Container::reference		reference;
			typedef typename Container::const_reference	const_reference;

		private:

			container_type	c;

		public:

			explicit Stack(const Container& cont = Container()) : c(cont) {}
			Stack(const Stack& other) : c(other.c) {}
			~Stack() {}
			Stack& operator=(const Stack& other) {
				c = other.c;
				return *this;
			}

			/***    ****    ****
			** element access **
			****    ****    ***/

			reference top() { return c.back(); }
			const_reference top() const { return c.back(); }

			/***  **  ****
			** capacity **
			****  **  ***/

			bool empty() const { return c.empty(); }
			size_type size() const {return c.size(); }

			/***  ***  ****
			** modifiers **
			****  ***  ***/

			void push(const value_type& value) { c.push_back(value); }
			void pop() { c.pop_back(); }

			template <class T1, class C1>
			friend bool operator == (const ft::Stack<T1, C1>& lhs, const ft::Stack<T1, C1>& rhs);
			template <class T1, class C1>
			friend bool operator != (const ft::Stack<T1, C1>& lhs, const ft::Stack<T1, C1>& rhs);
			template <class T1, class C1>
			friend bool operator < (const ft::Stack<T1, C1>& lhs, const ft::Stack<T1, C1>& rhs);
			template <class T1, class C1>
			friend bool operator <= (const ft::Stack<T1, C1>& lhs, const ft::Stack<T1, C1>& rhs);
			template <class T1, class C1>
			friend bool operator > (const ft::Stack<T1, C1>& lhs, const ft::Stack<T1, C1>& rhs);
			template <class T1, class C1>
			friend bool operator >= (const ft::Stack<T1, C1>& lhs, const ft::Stack<T1, C1>& rhs);
	};
}

template <class T1, class C1>
bool operator == (const ft::Stack<T1, C1>& lhs, const ft::Stack<T1, C1>& rhs) { return lhs.c == rhs.c; }

template <class T1, class C1>
bool operator != (const ft::Stack<T1, C1>& lhs, const ft::Stack<T1, C1>& rhs) { return lhs.c != rhs.c; }

template <class T1, class C1>
bool operator < (const ft::Stack<T1, C1>& lhs, const ft::Stack<T1, C1>& rhs) { return lhs.c < rhs.c; }

template <class T1, class C1>
bool operator <= (const ft::Stack<T1, C1>& lhs, const ft::Stack<T1, C1>& rhs) { return lhs.c <= rhs.c; }

template <class T1, class C1>
bool operator > (const ft::Stack<T1, C1>& lhs, const ft::Stack<T1, C1>& rhs) { return lhs.c > rhs.c; }

template <class T1, class C1>
bool operator >= (const ft::Stack<T1, C1>& lhs, const ft::Stack<T1, C1>& rhs) { return lhs.c >= rhs.c; }
