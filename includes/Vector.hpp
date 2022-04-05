#pragma once
#include <memory>
#include <exception>
#include "ft_type_traits.hpp"
#include "ft_algorithm.hpp"
#include "ft_iterator.hpp"
// #include "VectorIterator.hpp"

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

			reference operator * () { return *this->p; }
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
	class ConstVectorIterator { 

		public:

			typedef typename ft::iterator_traits<T *>::value_type 			value_type;
			typedef typename ft::iterator_traits<T *>::reference 			reference;
			typedef typename ft::iterator_traits<T *>::pointer				pointer;
            typedef const typename VectorIterator<T>::reference				const_reference;
            typedef const typename VectorIterator<T>::pointer				const_pointer;   
			typedef typename ft::iterator_traits<T *>::difference_type		difference_type;
			typedef typename ft::iterator_traits<T *>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<T *>::pointer				iterator_type;

		private:

			pointer p;

		public:

			ConstVectorIterator() : p(NULL) {}
			ConstVectorIterator(pointer _p) : p(_p) {}
			ConstVectorIterator(const ConstVectorIterator& other) : p(other.p) {}
			~ConstVectorIterator() {}
			ConstVectorIterator& operator = (const ConstVectorIterator& other) {

				p = other.p;
				return *this;
			}

			const_reference operator * () { return *this->p; }
			const_pointer operator -> () { return &p; }
			const_reference operator [] (difference_type n) { return *(p + n); }

			bool operator == (const ConstVectorIterator& other) { return p == other.p; }
			bool operator != (const ConstVectorIterator& other) { return p != other.p; }
			bool operator > (const ConstVectorIterator& other) { return p > other.p; }
			bool operator >= (const ConstVectorIterator& other) { return p >= other.p; }
			bool operator < (const ConstVectorIterator& other) { return p < other.p; }
			bool operator <= (const ConstVectorIterator& other) { return p <= other.p; }

			ConstVectorIterator& operator += (difference_type n) { p += n; return *this; }
			ConstVectorIterator& operator -= (difference_type n) { p -= n; return *this; }
			ConstVectorIterator operator + (difference_type n) { ConstVectorIterator tmp(p); tmp += n; return tmp; }
			ConstVectorIterator operator - (difference_type n) { ConstVectorIterator tmp(p); tmp -= n; return tmp; }
			ConstVectorIterator& operator ++ () { ++p; return *this; }
			ConstVectorIterator operator ++ (int) { ConstVectorIterator tmp(*this); ++p; return tmp; }
			ConstVectorIterator& operator -- () { --p; return *this; }
			ConstVectorIterator operator -- (int) { ConstVectorIterator tmp(*this); --p; return tmp; }

	};

	template <class T>
	class ReverseVectorIterator : public reverse_iterator<VectorIterator<T> > {};

	template <class T>
	class ConstReverseVectorIterator : public ReverseVectorIterator<T> {

		public:

			typedef typename VectorIterator<T>::reference     		reference;
        	typedef typename VectorIterator<T>::pointer       		pointer;   
        	typedef const typename VectorIterator<T>::reference     const_reference;
        	typedef const typename VectorIterator<T>::pointer       const_pointer;   
	};

	/***********
	** Vector **
	***********/

	template < class T, class Allocator = std::allocator<T> >
	class Vector {

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
			allocator_type	_alloc;


			void destroyVector() {

				for (size_type i = 0; i < _size; ++i)
					_alloc.destroy(p + i);
				_alloc.deallocate(p, _capacity);
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

			explicit Vector(const Allocator& alloc = Allocator())
				:	p(NULL), _size(0), _capacity(0), _alloc(alloc) {}

			explicit Vector(size_type count,
				const T& value = T(),
				const Allocator& alloc = Allocator())
				: _size(count), _capacity(count), _alloc(alloc) {

				p = _alloc.allocate(count);
				for (size_type i = 0; i < count; ++i)
					_alloc.construct(p + i, value);
			}

			template<typename InputIt>
			Vector(InputIt first, InputIt last, const allocator_type & alloc = allocator_type(),
				typename enable_if<!std::numeric_limits<InputIt>::is_specialized>::type * = 0)
				: _alloc(alloc), _capacity(20), _size(0) {
					
				if (first > last)
					throw std::length_error("vector");
				p = _alloc.allocate(_capacity);
				assign(first, last);
			}

			Vector(const Vector& other) {

				_size = _capacity = other.size();
				p = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _capacity; ++i)
					_alloc.construct(p + i, other[i]);
			}

			~Vector() {

				for (size_type i = 0; i < _size; ++i)
					_alloc.destroy(p + i);
				_alloc.deallocate(p, _capacity);
				_size = _capacity = 0;
			}

			Vector& operator = (const Vector& other) {

				destroyVector();
				_size = _capacity = other.size();
				p = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _capacity; ++i)
					_alloc.construct(p + i, other[i]);
				return *this;
			}

			void assign(size_type count, const T& value) {

				if (count > _capacity)
				{
					auto new_p = _alloc.allocate(count);
					for (size_type i = 0; i < count; ++i)
						_alloc.construct(new_p + i, value);
					for (size_type i = 0; i < _size; ++i)
						_alloc.destroy(p + i);
					_alloc.deallocate(p, _capacity);
					_size = _capacity = count;
					p = new_p;
					return ;
				}
				for (size_type i = 0; i < _size; ++i)
					_alloc.destroy(p + i);
				for (size_type i = 0; i < count; ++i)
					_alloc.construct(p + i, value);
				_size = count;
			}

			template <class InputIt>
			void assign(typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first, InputIt last) {

				if (first > last)
					throw std::length_error("vector");

				for (size_type i = 0; i < _size; ++i)
					_alloc.destroy(p + i);

				size_type count = 0;
				for (InputIt it = first; it != last; ++it, ++count);

				if (count > _capacity) {

					_alloc.deallocate(p, _capacity);
					_capacity = count;
					p = _alloc.allocate(_capacity);
				}
				_size = count;
				for (size_type i = 0; first != last; ++first, ++i)
					_alloc.construct(p + i, *first);
			}

			allocator_type get_allocator() const { 
				
				allocator_type allocator;
				return allocator;
			}

			// 	/***    ****    ****
			// 	** element access **
			// 	****    ****    ***/

			// 	// at
			// 	// operator[]
			// 	// front
			// 	// back
			// 	// data

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

			// 	/***  ***  ****
			// 	** iterators **
			// 	****  ***  ***/

			// 	// begin
			// 	// end
			// 	// rbegin
			// 	// rend

			iterator begin() { return iterator(p); }
			const_iterator begin() const { return const_iterator(p); }

			iterator end() { return iterator(p + _size); }
			const_iterator end() const { return const_iterator(p + _size); }

			reverse_iterator rbegin() { return reverse_iterator(p); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(p); }

			reverse_iterator rend() { return reverse_iterator(p + _size); }
			const_reverse_iterator rend() const { return const_reverse_iterator(p + _size); }
					
			// 	/***    ****    ****
			// 	** element access **
			// 	****    ****    ***/

			// 	// empty
			// 	// size
			// 	// max_size
			// 	// reserve
			// 	// capacity

			bool empty() const { return _size ? false : true; }

			size_type size() const { return _size; }

			size_type max_size() const { return std::numeric_limits<difference_type>::max(); }

			void reserve(size_type new_cap) {

				if (_capacity < new_cap)
				{
					pointer tmp = _alloc.allocate(new_cap);
					for (size_type i = 0; i < _size; ++i) {

						_alloc.construct(tmp + i, p[i]);
						_alloc.destroy(p + i);
					}
					_alloc.deallocate(p, _capacity);
					_capacity = new_cap;
					p = tmp;
				}
			}

			size_type capacity() const { return _capacity; }
					
			// 	/***  ***  ****
			// 	** modifiers **
			// 	****  ***  ***/

			// 	// clear
			// 	// insert
			// 	// erase
			// 	// push_back
			// 	// pop_back
			// 	// resize
			// 	// swap

			void clear() {

				while (_size)
					_alloc.destroy(p + --_size);
			}

			iterator insert(iterator pos, const T& value) {

				if (_size == _capacity) {

					size_type _new_capacity = _capacity ? _capacity * 2 : 1;
					pointer tmp = _alloc.allocate(_new_capacity);
					size_type i = _size;
					for (iterator it = end(); it != pos; --it)
						_alloc.construct(tmp + i, p[--i]);

					_alloc.construct(p + i, value);
					while (i)
						_alloc.construct(tmp + --i, p[i]);
					for (size_type j = 0; j < _size; ++j)
						_alloc.destroy(p + j);
					_alloc.deallocate(p, _capacity);
					p = tmp;
					_capacity = _new_capacity;
					++_size;
				}
				else {

					size_type i = _size;
					for (iterator it = end(); it != pos; --it) {

						_alloc.construct(p + i, p[--i]);
						_alloc.destroy(p + i);
					}
					_alloc.construct(p + i, value);
					++_size;
				}
			}

			void insert(iterator pos, size_type count, const T& value) {

				size_type _count = count;
				if (_size + count > _capacity) {

					if (!_capacity)
						++_capacity;
					while (_size + count > _capacity)
						_capacity *= 2;
					pointer tmp = _alloc.allocate(_capacity);
					size_type i = _size + count - 1;
					iterator stopCopying = pos + count;
					for (iterator it = end() + count - 1; it != stopCopying; --i, --it)
						_alloc.construct(tmp + i, *(p + i - count));
					for (; count; --i, --count)
						_alloc.construct(tmp + i, value);
					for (; i; --i)
						_alloc.construct(tmp + i, *(p + i));
					_alloc.construct(tmp, *p);
					destroyVector();
					p = tmp;
				}
				else {
					size_type i = _size + count - 1;
					iterator stopCopying = pos + count;
					for (iterator it = end() + count - 1; it != stopCopying; --i, --it) {

						if (i < _size)
							_alloc.destroy(p + i);
						_alloc.construct(p + i, *(p + i - count));

					}
					for (; count; --i, --count) {

						if (i < _size)
							_alloc.destroy(p + i);
						_alloc.construct(p + i, value);
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
					pointer tmp = _alloc.allocate(_capacity);

					size_type i = _size + count - 1;
					iterator stopCopying = pos + count - 1;

					for (iterator it = end() + count - 1; it > stopCopying; --it, --i)
						_alloc.construct(tmp + i, *(p + i - count));
					for (InputIt it = last - 1; it != first - 1; --it, --i)
						_alloc.construct(tmp + i, *it);
					for (; i; --i)
						_alloc.construct(tmp + i, *(p + i));
					_alloc.construct(tmp, *p);
					destroyVector();
					p = tmp;
				}
				else {

					size_type i = _size + count - 1;
					iterator stopCopying = pos + count - 1;
					for (iterator it = end() + count - 1; it > stopCopying; --it, --i) {

						if (i < _size)
							_alloc.destroy(p + i);
						_alloc.construct(p + i, *(p + i - count));
					}
					for (InputIt it = last - 1; it != first - 1; --it, --i) {

						if (i < _size)
							_alloc.destroy(p + i);
						_alloc.construct(p + i, *it);
					}			
				}
				_size += count;
			}

			iterator erase(iterator pos) {

				iterator erase = begin();
				size_type count = 0;
				for (; erase != pos; ++erase, ++count);
				for (; count != _size - 1; ++count) {

					_alloc.destroy(p + count);
					_alloc.construct(p + count, *(p + count + 1));
				}
				_alloc.destroy(p + count + 1);
				--_size;
				return pos;
			}

			iterator erase(iterator first, iterator last) {

				iterator erase = begin();
				iterator itEnd = end();
				size_type count = 0;
				size_type range = 0;
				for (iterator it = first; it != last; ++it, ++range);
				for (; erase != first; ++erase, ++count);
				for (; erase != last && erase != itEnd; ++erase, ++count) {

					_alloc.destroy(p + count);
					_alloc.construct(p + count, *(erase + range));
					// std::cout << count << " ";
				}
				for (; erase != itEnd; ++erase, ++count)
					_alloc.destroy(p + count);
				// std::cout << "!!!...!!!" << std::endl;
				_size -= range;
				return erase;
			}

			void push_back(const T& value) {

				if (_size == _capacity) {

					_capacity = _capacity ? _capacity * 2 : 1;
					pointer tmp = _alloc.allocate(_capacity);
					for (size_type i = 0; i < _size; ++i)
						_alloc.construct(tmp + i, p[i]);
					destroyVector();
					p = tmp;
				}
				_alloc.construct(p + _size, value);
				++_size;
			}

			void pop_back() {

				if (!empty()) {
					
					_alloc.destroy(p + _size - 1);
					--_size;
				}
			}
			
			void resize(size_type count, value_type value = value_type()) {

				for (; count < _size; pop_back());
				for (; count > _size; push_back(value));
			}

			void swap(Vector& other) {

				std::swap(p, other.p);
				std::swap(_size, other._size);
				std::swap(_capacity, other._capacity);
				std::swap(_alloc, other._alloc);
			}

	};

	template <class T, class Alloc>
    bool operator== (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
        return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }

    template <class T, class Alloc>
    bool operator!= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
        return !(lhs == rhs);
    }

    template <class T, class Alloc>
    bool operator<  (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(),
                                    rhs.begin(), rhs.end());
    }

    template <class T, class Alloc>
    bool operator<= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
        return !(rhs < lhs);
    }

    template <class T, class Alloc>
    bool operator>  (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
        return rhs < lhs;
    }

    template <class T, class Alloc>
    bool operator>= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
        return !(lhs < rhs);
    }

    template <class T, class Alloc>
    void swap (Vector<T,Alloc>& x, Vector<T,Alloc>& y) {
        x.swap(y);
    }
}

namespace std {
    template <class T, class Alloc>
    void swap (ft::Vector<T,Alloc>& x, ft::Vector<T,Alloc>& y) {
        x.swap(y);
    }
}
