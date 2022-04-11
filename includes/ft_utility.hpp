#pragma once

namespace ft {

	/*********
	** pair **
	*********/

	template <class T1, class T2>
	struct pair {

		typedef T1 first_type;
		typedef T2 second_type;

		T1	first;
		T2	second;

		pair() : first(), second() {}
		pair(const T1& _first, const T2& _second) : first(_first), second(_second) {}

		template <class U1, class U2>
		pair(const pair<U1, U2>& other) : first(other.first), second(other.second) {}

		pair& operator = (const pair& other) {
			first = other.first;
			second = other.second;
			return *this;
		}

	};

	/*******************
	** pair operators **
	*******************/

	template <class T1, class T2>
	bool operator == (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}
	template <class T1, class T2>
	bool operator != (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
		return !(lhs == rhs);
	}
	template <class T1, class T2>
	bool operator < (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
		return lhs.first < rhs.first;
	}
	template <class T1, class T2>
	bool operator <= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
		return lhs.first <= rhs.first;
	}
	template <class T1, class T2>
	bool operator > (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
		return lhs.first > rhs.first;
	}
	template <class T1, class T2>
	bool operator >= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
		return lhs.first >= rhs.first;
	}

	/**************
	** make_pair **
	**************/

	template< class T1, class T2 >
	ft::pair<T1,T2> make_pair(T1 t, T2 u) {

		ft::pair<T1, T2> p(t, u);
		return p;
	}

}
