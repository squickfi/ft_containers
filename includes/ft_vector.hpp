#pragma once
#include <memory>
#include "ft_type_traits.hpp"

namespace ft {

	template <class T>
	class VectorIterator {


	};

	template <class T>
	class ConstVectorIterator {


	};

	template <class T>
	class ReverseVectorIterator {


	};

	template <class T>
	class ConstReverseVectorIterator {


	};

	/***********
	** vector **
	***********/

	template < class T, class Allocator = std::allocator<T> >
	class vector {

		public:

			typedef T									value_type;
   			typedef Allocator							allocator_type;
			typedef std::size_t							size_type;
			typedef std::ptrdiff_t						difference_type;
			typedef value_type&							reference;
			typedef const value_type&					const_reference;
			typedef typename Allocator::pointer			pointer;
			typedef typename Allocator::const_pointer	const_pointer;
			typedef VectorIterator<T>					iterator;
			typedef ConstVectorIterator<T>				const_iterator;
			typedef ReverseVectorIterator<T>			reverse_iterator;
			typedef ConstReverseVectorIterator<T>		const_reverse_iterator;

		private:

			pointer			p;
			size_type		size;			
			size_type		capacity;
			allocator_type	alloc;

			void allocVector() {

				p = alloc.allocate(capacity);
				for (size_type i = 0; i < capacity; ++i)
					alloc.construct(p + i);
			}

			void allocVector(const T& value) {

				p = alloc.allocate(capacity);
				for (size_type i = 0; i < capacity; ++i)
					alloc.construct(p + i, value);
			}

			void allocVector(vector::iterator iter) {

				p = alloc.allocate(capacity);
				for (size_type i = 0; i < capacity; ++i, ++iter)
					alloc.construct(p + i, *iter);
			}

			void destroyVector() {

				for (size_type i = 0; i < size; ++i)
					alloc.destroy(p + i);
				alloc.deallocate(p, capacity);
			}

		public:

			/***          ****
			** constructors **
			****          ***/

			explicit vector(const Allocator& alloc = Allocator())
			:	p(NULL), size(0), capacity(0), alloc(alloc) {}

			explicit vector(size_type count,
				const T& value = T(),
				const Allocator& alloc = Allocator())
				:	size(count), capacity(count), alloc(alloc) {

				allocVector(value);
			}

			template <class InputIt>
			vector(InputIt first, InputIt last, const Allocator& alloc = Allocator(), 
					typename ft::enable_if<!ft::is_integral<InputIt>::value_type>::type* = 0)
					:	alloc(alloc) {
					
					for (InputIt i = first; i != last; ++i)
						++capacity;
					size = capacity;
					allocVector();
			}

			vector(const vector& other) {

				vector::iterator first = other.begin();
				vector::iterator last = other.end();
				for (; first != last; ++first)
					++capacity;
				size = capacity;
				allocVector(other.begin());
			}

			/***        ****
			** destructor **
			****        ***/

			~vector() {

				destroyVector();
			}

			/***      ****
			** operator **
			****      ***/

			vector& operator = (const vector& other) {

				destroyVector();
				size = capacity = 0;
				vector::iterator first = other.begin();
				vector::iterator last = other.end();
				for (; first != last; ++first)
					++capacity;
				size = capacity;
				allocVector(other.begin());
			}

			/***    ****
			** assign **
			****    ***/

			void assign(size_type count, const T& value) {

				if(!capacity) {

					capacity = size = count;
					allocVector(value);
					return;
				}
				if (capacity < count) {

					destroyVector();
					capacity = count;
					allocVector(value);
					return;
				}
				for (size_type i = 0; i < size; ++i) {

					alloc.destruct(p + i);
					alloc.construct(p + i, value);
				}
			}
	};

}