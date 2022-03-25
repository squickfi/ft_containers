#pragma once
#include <memory>
#include <exception>
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
			typedef std::size_t						size_type;
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
			size_type		_size;			
			size_type		_capacity;
			allocator_type	alloc;

			void allocVector() {

				p = alloc.allocate(_capacity);
				for (size_type i = 0; i < _capacity; ++i)
					alloc.construct(p + i);
			}

			void allocVector(const T& value) {

				p = alloc.allocate(_capacity);
				for (size_type i = 0; i < _capacity; ++i)
					alloc.construct(p + i, value);
			}

			void allocVector(vector::iterator& iter) {

				p = alloc.allocate(_capacity);
				for (size_type i = 0; i < _capacity; ++i, ++iter)
					alloc.construct(p + i, *iter);
			}

			template<class InputIt>
			void allocVector(InputIt& first, InputIt& last) {

				p = alloc.allocate(_capacity);
				for (size_type i = 0; first != last; ++first, ++i)
					alloc.construct(p + i, *first);
			}

			void destroyVector() {

				for (size_type i = 0; i < _size; ++i)
					alloc.destroy(p + i);
				alloc.deallocate(p, _capacity);
			}

		public:

					/***     ****     ****
					** member functions **
					****     ****     ***/

			/***          ****
			** constructors **
			****          ***/

			explicit vector(const Allocator& alloc = Allocator())
			:	p(NULL), _size(0), _capacity(0), alloc(alloc) {}

			explicit vector(size_type count,
				const T& value = T(),
				const Allocator& alloc = Allocator())
				:	_size(count), _capacity(count), alloc(alloc) {

				allocVector(value);
			}

			template <class InputIt>
			vector(InputIt first, InputIt last, const Allocator& alloc = Allocator(), 
					typename ft::enable_if<!ft::is_integral<InputIt>::value_type>::type* = 0)
					:	alloc(alloc) {
					
					for (InputIt i = first; i != last; ++i, ++_capacity);
					_size = _capacity;
					allocVector(first, last);
			}

			vector(const vector& other) {

				vector::iterator first = other.begin();
				vector::iterator last = other.end();
				for (; first != last; ++first, ++_capacity);
				_size = _capacity;
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
				_size = _capacity = 0;
				vector::iterator first = other.begin();
				vector::iterator last = other.end();
				for (; first != last; ++first, ++_capacity);
				_size = _capacity;
				allocVector(other.begin());
			}

			/***    ****
			** assign **
			****    ***/

			void assign(size_type count, const T& value) {

				if(!_capacity) {

					_capacity = _size = count;
					allocVector(value);
					return;
				}
				if (_capacity < count) {

					destroyVector();
					_capacity = count;
					allocVector(value);
					return;
				}
				for (size_type i = 0; i < count; ++i) {

					if (i < _size)
						alloc.destruct(p + i);
					alloc.construct(p + i, value);
				}
			}

			template<class InputIt, typename ft::enable_if<!ft::is_integral<InputIt>::value_type>::type* = 0>
			void assign(InputIt first, InputIt last) {

				size_type count = 0;
				for (InputIt it = first; it != last; ++it, ++count);
				if(!_capacity) {

					_capacity = _size = count;
					allocVector(first, last);
					return;
				}
				if (_capacity < count) {

					destroyVector();
					_capacity = count;
					allocVector(first, last);
					return;
				}
				for (size_type i = 0; i < count; ++i, ++first) {

					if (i < _size)
						alloc.destruct(p + i);
					alloc.construct(p + i, *first);
				}
			}

			/***           ****
			** get_allocator **
			****           ***/

			allocator_type get_allocator() const { 
				
				allocator_type allocator;
				return allocator;
			}

					/***    ****    ****
					** element access **
					****    ****    ***/

			/***  ****
			**  at  **
			****  ***/

			reference at(size_type pos) {

				if (pos < 0 || pos >= _size)
					throw std::out_of_range("Vector:: out of range");
				return (p[pos]);
			}

			const_reference at(size_type pos) const {

				if (pos < 0 || pos >= _size)
					throw std::out_of_range("Vector:: out of range");
				return (p[pos]);
			}

			/***        ****
			** operator = **
			****        ***/

			reference operator[] (size_type pos) { return p[pos]; }
			const_reference operator[] (size_type pos) const { return p[pos]; }

			/***   ****
			** front **
			****   ***/

			reference front() { return p[0]; }
			const_reference front() const { return p[0]; }
			
			/***  ****
			** back **
			****  ***/

			reference back() { return p[_size - 1]; }
			const_reference back() const { return p[_size - 1]; }

			/***  ****
			** data **
			****  ***/

			T* data() { return p ? p : NULL; }
			const T* data() const { return p ? p : NULL; }

					/***  ***  ****
					** iterators **
					****  ***  ***/
			
			/***   ****
			** begin **
			****   ***/

			iterator begin() { return iterator(p); }
			const_iterator begin() const { return iterator(p); }
			
			/***   ****
			**  end  **
			****   ***/

			iterator end() { return iterator(p + _size); }
			const_iterator end() const { return iterator(p + _size); }

			/***    ****
			** rbegin **
			****    ***/

			iterator rbegin() { return reverse_iterator(p); }
			const_iterator rbegin() const { return reverse_iterator(p); }
			
			/***    ****
			**  rend  **
			****    ***/

			reverse_iterator rend() { return reverse_iterator(p + _size); }
			const_reverse_iterator rend() const { return reverse_iterator(p + _size); }
					
					/***    ****    ****
					** element access **
					****    ****    ***/
			
			/***   ****
			** empty **
			****   ***/

			bool empty() const { return _size ? false : true; }

			/***  ****
			** size **
			****  ***/

			size_type size() const { return _size; }
			
			/***      ****
			** max_size **
			****      ***/

			size_type max_size() const { return std::numeric_limits<difference_type>::max(); }

			/***     ****
			** reserve **
			****     ***/

			void reserve(size_type new_cap) {

				if (_capacity < new_cap)
				{
					pointer tmp = alloc.allocate(new_cap);
					for (size_type i = 0; i < _size; ++i)
						alloc.construct(tmp + i, p[i]);
					destroyVector();
					p = tmp;
				}
			}

			/***      ****
			** capacity **
			****      ***/

			size_type capacity() const { return _capacity; }
					
					/***  ***  ****
					** modifiers **
					****  ***  ***/

			/***   ****
			** clear **
			****   ***/

			void clear() {

				for (; _size; --_size)
					alloc.destroy(p + _size - 1);
			}

			/***    ****
			** insert **
			****    ***/

			iterator insert(iterator pos, const T& value) {

				
			}


	};

}