#pragma once
#include <memory>
#include <exception>
#include "ft_type_traits.hpp"
#include "ft_iterator.hpp"

namespace ft {

	template <class T>
	class VectorIterator {

		public:

			typedef typename ft::iterator_traits<T *>::value_type 			value_type;
			typedef typename ft::iterator_traits<T *>::reference 			reference;
			typedef typename ft::iterator_traits<T *>::pointer				pointer;
			typedef typename ft::iterator_traits<T *>::difference_type		difference_type;
			typedef typename ft::iterator_traits<T *>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<T *>::pointer				iterator_type;

		private:

			pointer p;

		public:

			VectorIterator() : p(NULL) {}
			VectorIterator(pointer _p) : p(_p) {}
			VectorIterator(const VectorIterator& other) : p(other.p) {}
			~VectorIterator() {}
			VectorIterator& operator = (const VectorIterator& other) {

				p = other.p;
				return *this;
			}

			reference operator * () { return *p; }
			pointer operator -> () { return &p; }
			reference operator [] (difference_type n) { return *(p + n); }

			bool operator == (const VectorIterator& other) { return p == other.p; }
			bool operator != (const VectorIterator& other) { return p != other.p; }
			bool operator > (const VectorIterator& other) { return p > other.p; }
			bool operator >= (const VectorIterator& other) { return p >= other.p; }
			bool operator < (const VectorIterator& other) { return p < other.p; }
			bool operator <= (const VectorIterator& other) { return p <= other.p; }

			VectorIterator& operator += (difference_type n) { p += n; return *this; }
			VectorIterator& operator -= (difference_type n) { p -= n; return *this; }
			VectorIterator operator + (difference_type n) { VectorIterator tmp(p); tmp += n; return tmp; }
			VectorIterator operator - (difference_type n) { VectorIterator tmp(p); tmp -= n; return tmp; }
			VectorIterator& operator ++ () { ++p; return *this; }
			VectorIterator operator ++ (int) { VectorIterator tmp(*this); ++p; return tmp; }
			VectorIterator& operator -- () { --p; return *this; }
			VectorIterator operator -- (int) { VectorIterator tmp(*this); --p; return tmp; }

	};

	template <class T>
	class ConstVectorIterator : public VectorIterator<T> {};

	template <class T>
	class ReverseVectorIterator : public reverse_iterator<VectorIterator<T> > {};

	template <class T>
	class ConstReverseVectorIterator : public ReverseVectorIterator<T> {};

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

				// constructors
				// destructors
				// operator =
				// assign
				// get_allocator

			explicit vector(const Allocator& alloc = Allocator())
				:	_size(0), _capacity(0), alloc(alloc) {}

			explicit vector(size_type count,
				const T& value = T(),
				const Allocator& alloc = Allocator())
				:	_size(count), _capacity(count), alloc(alloc) {

				allocVector(value);
			}

			template <class InputIt>
			vector(InputIt first, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type last,
				const Allocator& alloc = Allocator())
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

			~vector() {

				destroyVector();
			}

			vector& operator = (const vector& other) {

				destroyVector();
				_size = _capacity = 0;
				vector::iterator first = other.begin();
				vector::iterator last = other.end();
				for (; first != last; ++first, ++_capacity);
				_size = _capacity;
				allocVector(other.begin());
			}

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

			template<class InputIt>
			void assign(InputIt first, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type last) {

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

			allocator_type get_allocator() const { 
				
				allocator_type allocator;
				return allocator;
			}

				/***    ****    ****
				** element access **
				****    ****    ***/

				// at
				// operator[]
				// front
				// back
				// data

			reference at(size_type pos) {

				if (pos < 0 || pos >= _size) {

					destroyVector();	
					throw std::out_of_range("Vector:: out of range");
				}
				return (p[pos]);
			}

			const_reference at(size_type pos) const {

				if (pos < 0 || pos >= _size) {

					destroyVector();
					throw std::out_of_range("Vector:: out of range");
				}
				return (p[pos]);
			}

			reference operator[] (size_type pos) { return p[pos]; }
			const_reference operator[] (size_type pos) const { return p[pos]; }

			reference front() { return p[0]; }
			const_reference front() const { return p[0]; }

			reference back() { return p[_size - 1]; }
			const_reference back() const { return p[_size - 1]; }

			T* data() { return p ? p : NULL; }
			const T* data() const { return p ? p : NULL; }

				/***  ***  ****
				** iterators **
				****  ***  ***/

				// begin
				// end
				// rbegin
				// rend

			iterator begin() { return iterator(p); }
			const_iterator begin() const { return iterator(p); }

			iterator end() { return iterator(p + _size); }
			const_iterator end() const { return iterator(p + _size); }

			iterator rbegin() { return reverse_iterator(p); }
			const_iterator rbegin() const { return reverse_iterator(p); }

			reverse_iterator rend() { return reverse_iterator(p + _size); }
			const_reverse_iterator rend() const { return reverse_iterator(p + _size); }
					
				/***    ****    ****
				** element access **
				****    ****    ***/

				// empty
				// size
				// max_size
				// reserve
				// capacity

			bool empty() const { return _size ? false : true; }

			size_type size() const { return _size; }

			size_type max_size() const { return std::numeric_limits<difference_type>::max(); }

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

			size_type capacity() const { return _capacity; }
					
				/***  ***  ****
				** modifiers **
				****  ***  ***/

				// clean
				// insert
				// erase
				// push_back
				// pop_back
				// resize
				// swap

			void clear() {

				for (; _size; --_size)
					alloc.destroy(p + _size - 1);
			}

			iterator insert(iterator pos, const T& value) {

				if (_size == _capacity) {

					_capacity = _capacity ? _capacity * 2 : 1;
					pointer tmp = alloc.allocate(_capacity);
					size_type i = _size;
					for (iterator it = end(); it > pos; --it, --i)
						alloc.construct(tmp + i, p[i - 1]);
					alloc.construct(tmp + i, value);
					--i;
					for (; i; --i)
						alloc.construct(tmp + i, p[i]);
					destroyVector();
					p = tmp;
				}
				else {

					size_type i = _size;
					for (iterator it = end(); it > pos; --it) {
						alloc.construct(p + i, p[i - 1]);
						--i;
						alloc.destroy(p + i);
					}
					alloc.construct(p + i, value);
				}
				++_size;
				return pos;
			}

			void insert(iterator pos, size_type count, const T& value) {

				size_type _count = count;
				if (_size + count > _capacity) {

					if (!_capacity)
						++_capacity;
					while (_size + count > _capacity)
						_capacity *= 2;
					pointer tmp = alloc.allocate(_capacity);
					size_type i = _size + count - 1;
					iterator stopCopying = pos + count;
					for (iterator it = end() + count - 1; it != stopCopying; --i, --it)
						alloc.construct(tmp + i, *(p + i - count));
					for (; count; --i, --count)
						alloc.construct(tmp + i, value);
					for (; i; --i)
						alloc.construct(tmp + i, *(p + i));
					alloc.construct(tmp, *p);
					destroyVector();
					p = tmp;
				}
				else {
					size_type i = _size + count - 1;
					iterator stopCopying = pos + count;
					for (iterator it = end() + count - 1; it != stopCopying; --i, --it) {

						if (i < _size)
							alloc.destroy(p + i);
						alloc.construct(p + i, *(p + i - count));

					}
					for (; count; --i, --count) {

						if (i < _size)
							alloc.destroy(p + i);
						alloc.construct(p + i, value);
					}
				}
				_size += _count;
			}

			template <class InputIt>
			void insert(iterator pos, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first,
				InputIt last) {

				size_type count = 0;
				for (InputIt it = first; it != last; ++it, ++count);

				if (_size + count >= _capacity) {

					if (!_capacity)
						++_capacity;
					while (_size + count >= _capacity)
						_capacity *= 2;
					pointer tmp = alloc.allocate(_capacity);

					size_type i = _size + count - 1;
					iterator stopCopying = pos + count - 1;

					for (iterator it = end() + count - 1; it > stopCopying; --it, --i)
						alloc.construct(tmp + i, *(p + i - count));
					for (InputIt it = last - 1; it != first - 1; --it, --i)
						alloc.construct(tmp + i, *it);
					for (; i; --i)
						alloc.construct(tmp + i, *(p + i));
					alloc.construct(tmp, *p);
					destroyVector();
					p = tmp;
				}
				else {

					size_type i = _size + count - 1;
					iterator stopCopying = pos + count - 1;
					for (iterator it = end() + count - 1; it > stopCopying; --it, --i) {

						if (i < _size)
							alloc.destroy(p + i);
						alloc.construct(p + i, *(p + i - count));
					}
					for (InputIt it = last - 1; it != first - 1; --it, --i) {

						if (i < _size)
							alloc.destroy(p + i);
						alloc.construct(p + i, *it);
					}
						
				}
				_size += count;

			}

			// TO DO: erase

			iterator erase(iterator pos) {

				iterator erase = begin();
				size_type count = 0;
				for (; erase != pos; ++erase, ++count);
				for (; count != _size - 2;) {

					alloc.destroy(p + count);
					alloc.construct(p + count, *(p + count + 1));
				}
				alloc.destroy(p + count + 1);
				--_size;
			}

			iterator erase(iterator first, iterator last) {

				iterator erase = begin();
				iterator itEnd = end();
				size_type count = 0;
				for (; erase != first; ++erase, ++count);
				for (; erase != last, first != itEnd; ++first, ++count) {

					alloc.destroy(p + count);
					alloc.construct(p + count, *(first + 1));
				}
				for (; erase != itEnd; ++erase, ++count)
					alloc.destroy(p + count);
			}

			void push_back(const T& value) {

				if (_size == _capacity) {

					_capacity = _capacity ? _capacity * 2 : 1;
					pointer tmp = alloc.allocate(_capacity);
					for (size_type i = 0; i < _size; ++i)
						alloc.construct(tmp + i, p[i]);
					destroyVector();
					p = tmp;
				}
				alloc.construct(p + _size, value);
				++_size;
			}

	};

}