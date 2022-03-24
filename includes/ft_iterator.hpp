#pragma once
#include <iostream>

namespace ft {

	/********************
	** iterator_traits **
	********************/

	template <class Iter>
	struct iterator_traits {

		typedef Iter::value_type				value_type;
		typedef Iter::difference_type			difference_type;
		typedef Iter::pointer					pointer;
		typedef Iter::reference					reference;
		typedef Iter::iterator_category			iterator_category;
	};

	template <class T>
	struct iterator_traits<T*> {

		typedef T								value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	template <class T>
	struct iterator_traits<const T*> {

		typedef T								value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	/*************
	** iterator **
	*************/

	template <class _value_type, class _difference_type, class _pointer,
				class _reference, class _iterator_category>
	struct iterator {

		typedef _value_type					value_type;
		typedef _difference_type			difference_type;
		typedef _pointer					pointer;
		typedef _reference					reference;
		typedef _iterator_category			iterator_category;
	};

	/*********************
	** reverse_iterator **
	*********************/

	template <class Iter>
	class reverse_iterator : public iterator <iterator_traits<Iter>::value_type,
											iterator_traits<Iter>::difference_type,
											iterator_traits<Iter>::pointer,
											iterator_traits<Iter>::reference,
											iterator_traits<Iter>::iterator_category,> {

		public:
			typedef Iter iterator_type;

		protected:
			iterator_type current;

		public:

			/***          ****
			** constructors **
			****          ***/

			reverse_iterator() : current() {}
			explicit reverse_iterator( iterator_type x ) : current(x) {}
			template <class U>
			reverse_iterator( const reverse_iterator<U>& other ) : current(other.base) {}
			
			/***       ****
			** operators **
			****       ***/

			template <class U>
			reverse_iterator& operator = (const reverse_iterator<U>& other) {
				current = other.base();
				return *this;
			}
			reference operator * () const { iterator_type tmp(current); return *--tmp; }
			pointer operator->() const { return &(operator*());	}
			reference operator [] (difference_type n) { return *(*this - n); }
			reverse_iterator& operator ++ () { --current; return *this; }
			reverse_iterator& operator ++ (int) { reverse_iterator tmp(*this); --current; return tmp; }
			reverse_iterator& operator -- () { ++current; return *this; }
			reverse_iterator& operator -- (int) { reverse_iterator tmp(*this); ++current; return tmp; }
			reverse_iterator operator + ( difference_type n ) const { return reverse_iterator(current - n); }
			reverse_iterator operator - ( difference_type n ) const { return reverse_iterator(current + n); }
			reverse_iterator& operator += ( difference_type n ) { current -= n; return &this; }
			reverse_iterator& operator -= ( difference_type n ) { current += n; return &this; }

			/***       ****
			** functions **
			****       ***/

			iterator_type base() const {
				return current;
			}
	};

	/***********************
	**  reverse_iterator  **
	** operator overloads **
	***********************/

	template< class Iterator1, class Iterator2 >
	bool operator==( const std::reverse_iterator<Iterator1>& lhs,
				const std::reverse_iterator<Iterator2>& rhs ) { 
		return (lhs.base() == rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator!=( const std::reverse_iterator<Iterator1>& lhs,
				const std::reverse_iterator<Iterator2>& rhs ) { 
		return (lhs.base() != rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator<( const std::reverse_iterator<Iterator1>& lhs,
				const std::reverse_iterator<Iterator2>& rhs ) { 
		return (lhs.base() < rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator<=( const std::reverse_iterator<Iterator1>& lhs,
				const std::reverse_iterator<Iterator2>& rhs ) { 
		return (lhs.base() <= rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator>( const std::reverse_iterator<Iterator1>& lhs,
				const std::reverse_iterator<Iterator2>& rhs ) { 
		return (lhs.base() > rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator>=( const std::reverse_iterator<Iterator1>& lhs,
				const std::reverse_iterator<Iterator2>& rhs ) { 
		return (lhs.base() >= rhs.base());
	}
}
