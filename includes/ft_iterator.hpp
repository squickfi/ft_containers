#pragma once
#include <iostream>

namespace ft {

	/********************
	** iterator_traits **
	********************/

	template <class Iter>
	struct iterator_traits {

		typedef typename Iter::value_type				value_type;
		typedef typename Iter::difference_type			difference_type;
		typedef typename Iter::pointer					pointer;
		typedef typename Iter::reference				reference;
		typedef typename Iter::iterator_category		iterator_category;
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

	/*********************
	** reverse_iterator **
	*********************/

	template <class Iter>
	class reverse_iterator {

		public:
			typedef Iter iterator_type;
			typedef typename iterator_traits<Iter>::value_type				value_type;
			typedef typename iterator_traits<Iter>::difference_type			difference_type;
			typedef typename iterator_traits<Iter>::pointer					pointer;
			typedef typename iterator_traits<Iter>::reference				reference;
			typedef typename iterator_traits<Iter>::iterator_category		iterator_category;

		protected:
			iterator_type current;

		public:

			/***          ****
			** constructors **
			****          ***/

			reverse_iterator() : current() {}
			explicit reverse_iterator(iterator_type x) : current(x) {}
			explicit reverse_iterator(const reverse_iterator& x) : current(x.base()) {}
			template <class U>
			reverse_iterator( const reverse_iterator<U>& other ) : current(other.base()) {}
			
			/***       ****
			** operators **
			****       ***/

			template <class U>
			reverse_iterator& operator = (const reverse_iterator<U>& other) {
				current = other.base();
				return *this;
			}
			reference operator * () const { iterator_type tmp = current; return *--tmp; }
			pointer operator->() const { return &(operator*());	}
			reference operator [] (difference_type n) { return *(*this - n); }
			reverse_iterator& operator ++ () { --current; return *this; }
			reverse_iterator& operator ++ (int) { reverse_iterator tmp(*this); --current; return tmp; } // !!!!!!!!!!!!!
			reverse_iterator& operator -- () { ++current; return *this; }
			reverse_iterator& operator -- (int) { reverse_iterator tmp(*this); ++current; return tmp; }
			reverse_iterator operator + ( difference_type n ) const { 
				
				reverse_iterator tmp(*this);
				tmp += n;
				return tmp;
			}
			reverse_iterator operator - ( difference_type n ) const { 

				reverse_iterator tmp(*this);
				tmp -= n;
				return tmp;
			}
			reverse_iterator& operator += ( difference_type n ) { current -= n; return *this; }
			reverse_iterator& operator -= ( difference_type n ) { current += n; return *this; }

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
	bool operator==(const ft::reverse_iterator<Iterator1>& lhs,
				const ft::reverse_iterator<Iterator2>& rhs ) { 
		return (lhs.base() == rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator!=(const ft::reverse_iterator<Iterator1>& lhs,
				const ft::reverse_iterator<Iterator2>& rhs) { 
		return (lhs.base() != rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator<(const ft::reverse_iterator<Iterator1>& lhs,
				const ft::reverse_iterator<Iterator2>& rhs) { 
		return (lhs.base() < rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator<=(const ft::reverse_iterator<Iterator1>& lhs,
				const ft::reverse_iterator<Iterator2>& rhs) { 
		return (lhs.base() <= rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator>(const ft::reverse_iterator<Iterator1>& lhs,
				const ft::reverse_iterator<Iterator2>& rhs) { 
		return (lhs.base() > rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator>=(const ft::reverse_iterator<Iterator1>& lhs,
				const ft::reverse_iterator<Iterator2>& rhs) { 
		return (lhs.base() >= rhs.base());
	}
}

