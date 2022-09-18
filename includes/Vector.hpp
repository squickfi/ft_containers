#pragma once
#include <memory>
#include <exception>
#include "ft_type_traits.hpp"
#include "ft_algorithm.hpp"
#include "ft_iterator.hpp"

//#define _const_it const Iterator

namespace ft {

    template<class Iterator>
    class VectorIterator {

    public:

        typedef typename ft::iterator_traits<Iterator>::value_type value_type;
        typedef typename ft::iterator_traits<Iterator>::reference reference;
        typedef typename ft::iterator_traits<Iterator>::pointer pointer;
        typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
        typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;
        typedef typename ft::iterator_traits<Iterator>::pointer iterator_type;

    private:

        pointer p;

    public:

        VectorIterator() : p(NULL) {}

        VectorIterator(pointer _p) : p(_p) {}

        VectorIterator(const VectorIterator<value_type *> _p) : p(_p.base()) {}

        VectorIterator(const VectorIterator &other) : p(other.p) {}

        ~VectorIterator() {}

        VectorIterator &operator=(const VectorIterator &other) {

            p = other.base();
            return *this;
        }

        reference operator*() { return *this->p; }

        pointer operator->() { return &p; }

        reference operator[](difference_type n) { return *(p + n); }

        bool operator==(const VectorIterator &other) { return p == other.p; }
        bool operator!=(const VectorIterator &other) { return p != other.p; }
        bool operator>(const VectorIterator &other) { return p > other.p; }
        bool operator>=(const VectorIterator &other) { return p >= other.p; }
        bool operator<(const VectorIterator &other) { return p < other.p; }
        bool operator<=(const VectorIterator &other) { return p <= other.p; }

        VectorIterator &operator+=(difference_type n) {
            p += n;
            return *this;
        }

        VectorIterator &operator-=(difference_type n) {
            p -= n;
            return *this;
        }

        VectorIterator operator+(difference_type n) {
            VectorIterator tmp(p);
            tmp += n;
            return tmp;
        }

        VectorIterator operator-(difference_type n) {
            VectorIterator tmp(p);
            tmp -= n;
            return tmp;
        }

        VectorIterator &operator++() {
            ++p;
            return *this;
        }

        VectorIterator operator++(int) {
            VectorIterator tmp(*this);
            ++p;
            return tmp;
        }

        VectorIterator &operator--() {
            --p;
            return *this;
        }

        VectorIterator operator--(int) {
            VectorIterator tmp(*this);
            --p;
            return tmp;
        }

        pointer base() const { return p; }

    };

    template<class Iter1, class Iter2>
    typename VectorIterator<Iter1>::difference_type
    operator-(const VectorIterator<Iter1> &lhs, const VectorIterator<Iter2> &rhs) {
        return lhs.base() - rhs.base();
    }

    template<class Iter1, class Iter2>
    bool operator==(const VectorIterator<Iter1> &lhs, const VectorIterator<Iter2> &rhs) {
        return lhs.base() == rhs.base();
    }

    template<class Iter1, class Iter2>
    bool operator!=(const VectorIterator<Iter1> &lhs, const VectorIterator<Iter2> &rhs) {
        return lhs.base() != rhs.base();
    }

    template<class Iter1, class Iter2>
    bool operator>(const VectorIterator<Iter1> &lhs, const VectorIterator<Iter2> &rhs) {
        return lhs.base() > rhs.base();
    }

    template<class Iter1, class Iter2>
    bool operator>=(const VectorIterator<Iter1> &lhs, const VectorIterator<Iter2> &rhs) {
        return lhs.base() >= rhs.base();
    }

    template<class Iter1, class Iter2>
    bool operator<(const VectorIterator<Iter1> &lhs, const VectorIterator<Iter2> &rhs) {
        return lhs.base() < rhs.base();
    }

    template<class Iter1, class Iter2>
    bool operator<=(const VectorIterator<Iter1> &lhs, const VectorIterator<Iter2> &rhs) {
        return lhs.base() <= rhs.base();
    }

    template<class T, class Allocator = std::allocator<T> >
    class Vector {

    public:

        typedef T value_type;
        typedef Allocator allocator_type;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef typename Allocator::pointer pointer;
        typedef typename Allocator::const_pointer const_pointer;
        typedef VectorIterator<pointer> iterator;
        typedef VectorIterator<const_pointer> const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

    private:

        pointer p;
        size_type _size;
        size_type _capacity;
        allocator_type _alloc;

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

        explicit Vector(const Allocator &alloc = Allocator())
                : p(NULL), _size(0), _capacity(0), _alloc(alloc) {}

        explicit Vector(size_type count,
                        const T &value = T(),
                        const Allocator &alloc = Allocator())
                : _size(count), _capacity(count), _alloc(alloc) {

            p = _alloc.allocate(count);
            size_type i = 0;
            try {
                for (; i < count; ++i)
                    _alloc.construct(p + i, value);
            } catch (...) {
                for (; i; --i)
                    _alloc.destroy(p + i - 1);
                _alloc.deallocate(p, count);
                throw "vector";
            }
        }

        template<typename InputIt>
        // TODO
        Vector(InputIt first, InputIt last, const allocator_type &alloc = allocator_type(),
               typename enable_if<!std::numeric_limits<InputIt>::is_specialized>::type * = 0)
                : _size(0), _capacity(20), _alloc(alloc) {

            if (first > last)
                throw std::length_error("vector");
            try {
                p = _alloc.allocate(_capacity);
            } catch (...) {
                throw "vector: couldn't allocate memory";
            }
            assign(first, last);
        }

        Vector(const Vector &other) {

            _size = _capacity = other.size();
            try {
                p = _alloc.allocate(_capacity);
            } catch (...) {
                throw "vector: couldn't allocate memory";
            }
            size_type i = 0;
            try {
                for (; i < _capacity; ++i)
                    _alloc.construct(p + i, other[i]);
            } catch (...) {
                for (; i; --i)
                    _alloc.destroy(p + i - i);
                _alloc.deallocate(p, _capacity);
                throw "vector";
            }
        }

        ~Vector() {

            destroyVector();
            _size = _capacity = 0;
        }

        Vector &operator=(const Vector &other) {

            destroyVector();
            _size = _capacity = other.size();
            try {
                p = _alloc.allocate(_capacity);
            } catch (...) {
                throw "vector: couldn't allocate memory";
            }
            size_type i = 0;
            try {
                for (; i < _capacity; ++i)
                    _alloc.construct(p + i, other[i]);
            } catch (...) {
                for (; i; --i)
                    _alloc.destroy(p + i - 1);
                _alloc.deallocate(p, _capacity);
                throw "vector";
            }
            return *this;
        }

        void assign(size_type count, const T &value) {

            if (count < 0 || count > max_size())
                throw std::length_error("cannot create ft::vector larger than max_size()");

            size_type i = 0;
            if (count > _capacity) {
                pointer tmp;
                try {
                    tmp = _alloc.allocate(count);
                } catch (...) {
                    destroyVector();
                    throw "vector: couldn't allocate memory";
                }
                try {
                    for (; i < count; ++i)
                        _alloc.construct(tmp + i, value);
                } catch (...) {
                    for (; i; --i)
                        _alloc.destroy(tmp + i - 1);
                    _alloc.deallocate(tmp, count);
                    for (i = 0; i < _size; ++i)
                        _alloc.destroy(p + i);
                    _alloc.deallocate(p, _capacity);
                    throw "vector";
                }
                for (i = 0; i < _size; ++i)
                    _alloc.destroy(p + i);
                _alloc.deallocate(p, _capacity);
                _size = _capacity = count;
                p = tmp;
                return;
            }
            for (i = 0; i < _size; ++i)
                _alloc.destroy(p + i);
            try {
                for (i = 0; i < count; ++i)
                    _alloc.construct(p + i, value);
            } catch (...) {
                for (; i; --i)
                    _alloc.destroy(p + i - 1);
                _alloc.deallocate(p, _capacity);
                throw "vector";
            }
            _size = count;
        }

        template<class InputIt>
        void assign(typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first, InputIt last) {

            if (first > last)
                throw std::length_error("vector");

            size_type i = 0;
            for (; i < _size; ++i)
                _alloc.destroy(p + i);

            size_type count = 0;
            for (InputIt it = first; it != last; ++it, ++count);

            if (count > _capacity) {

                _alloc.deallocate(p, _capacity);
                _capacity = count;
                try {
                    p = _alloc.allocate(_capacity);
                } catch (...) {
                    throw "vector: couldn't allocate memory";
                }
            }
            _size = count;
            try {
                for (i = 0; first != last; ++first, ++i)
                    _alloc.construct(p + i, *first);
            } catch (...) {
                for (; i; --i)
                    _alloc.destroy(p + i - 1);
                _alloc.deallocate(p, _capacity);
                throw "vector";
            }
        }

        allocator_type get_allocator() const {

            allocator_type allocator;
            return allocator;
        }

        // 	/***	****	****
        // 	** element access **
        // 	****	****	***/

        // 	// at
        // 	// operator[]
        // 	// front
        // 	// back
        // 	// data

        reference at(size_type pos) {

            if (pos < 0 || pos >= _size)
                throw std::out_of_range("Vector:: range check: pos < 0 || pos >= this->size(), it's wrong :c");
            return (p[pos]);
        }

        const_reference at(size_type pos) const {

            if (pos < 0 || pos >= _size) {

                destroyVector();
                throw std::out_of_range("Vector:: out of range");
            }
            return (p[pos]);
        }

        reference operator[](size_type pos) { return p[pos]; }

        const_reference operator[](size_type pos) const { return p[pos]; }

        reference front() { return p[0]; }

        const_reference front() const { return p[0]; }

        reference back() { return p[_size - 1]; }

        const_reference back() const { return p[_size - 1]; }

        T *data() { return p ? p : NULL; }

        const T *data() const { return p ? p : NULL; }

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

        reverse_iterator rbegin() { return reverse_iterator(p + _size); }

        const_reverse_iterator rbegin() const { return const_reverse_iterator(p + _size); }

        reverse_iterator rend() { return reverse_iterator(p); }

        const_reverse_iterator rend() const { return const_reverse_iterator(p); }

        // 	/***	****	****
        // 	** element access **
        // 	****	****	***/

        // 	// empty
        // 	// size
        // 	// max_size
        // 	// reserve
        // 	// capacity

        bool empty() const { return _size ? false : true; }

        size_type size() const { return _size; }

        size_type max_size() const { return std::numeric_limits<difference_type>::max() / 2; }

        void reserve(size_type new_cap) {

            if (_capacity < new_cap) {
                pointer tmp = _alloc.allocate(new_cap);
                size_type i = 0;
                for (; i < _size; ++i) {

                    try {
                        _alloc.construct(tmp + i, p[i]);
                    } catch (...) {
                        for (; i; --i)
                            _alloc.destroy(tmp + i);
                        _alloc.deallocate(tmp, new_cap);
                        for (; i < _size; ++i)
                            _alloc.destroy(p + i);
                        _alloc.deallocate(p, _capacity);
                        throw "vector";
                    }
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

        iterator insert(iterator pos, const T &value) {

            if (_size == _capacity) {

                size_type _new_capacity = _capacity ? _capacity * 2 : 1;
                pointer tmp = _alloc.allocate(_new_capacity);
                iterator _new_pos;
                size_type i = _size;
                for (iterator it = end(); it != pos; --it, --i) {

                    try {
                        _alloc.construct(tmp + i, p[i - 1]);
                    } catch (...) {
                        for (; i; --i)
                            _alloc.destroy(tmp + i - 1);
                        _alloc.deallocate(tmp, _new_capacity);
                        destroyVector();
                        throw "vector";
                    }
                }
                try {
                    _alloc.construct(tmp + i, value);
                    _new_pos = tmp + i;
                } catch (...) {
                    for (; i; --i)
                        _alloc.destroy(tmp + i - 1);
                    _alloc.deallocate(tmp, _new_capacity);
                    destroyVector();
                    throw "vector";
                }
                for (; i; --i) {

                    try {
                        _alloc.construct(tmp + i - 1, p[i - 1]);
                    } catch (...) {
                        for (; i; --i)
                            _alloc.destroy(tmp + i - 1);
                        _alloc.deallocate(tmp, _new_capacity);
                        destroyVector();
                        throw "vector";
                    }
                }
                destroyVector();
                _capacity = _new_capacity;
                ++_size;
                p = tmp;
                return _new_pos;
            } else {

                size_type i = _size;
                for (iterator it = end(); it != pos; --it) {

                    try {
                        _alloc.construct(p + i, p[i - 1]);
                    } catch (...) {
                        for (size_type j = i; j < _size; ++j)
                            _alloc.destroy(p + j + 1);
                        for (; i; --i)
                            _alloc.destroy(p + i - 1);
                        _alloc.deallocate(p, _capacity);
                        throw "vector";
                    }
                    --i;
                    _alloc.destroy(p + i);
                }
                try {
                    _alloc.construct(p + i, value);
                } catch (...) {
                    for (size_type j = i; j < _size; ++j)
                        _alloc.destroy(p + j + 1);
                    for (; i; --i)
                        _alloc.destroy(p + i - 1);
                    _alloc.deallocate(p, _capacity);
                    throw "vector";
                }
            }
            ++_size;
            return pos;
        }

        void insert(iterator pos, size_type count, const T &value) {

            if (_size + count > _capacity) {

                size_type _new_capacity = _size + count;
                pointer tmp;
                try {
                    tmp = _alloc.allocate(_new_capacity);
                } catch (...) {
                    destroyVector();
                    throw "vector: couldn't allocate memory";
                }
                size_type i = 0;
                iterator it = begin();
                for (; it != pos; ++it, ++i) {

                    try {
                        _alloc.construct(tmp + i, p[i]);
                    } catch (...) {
                        for (; i; --i)
                            _alloc.destroy(tmp + i - 1);
                        _alloc.deallocate(tmp, _new_capacity);
                        for (i = 0; i < _size; ++i)
                            _alloc.destroy(p + i);
                        _alloc.deallocate(p, _capacity);
                        throw "vector";
                    }
                }
                for (size_type _count = count; _count; --_count, ++i) {

                    try {
                        _alloc.construct(tmp + i, value);
                    } catch (...) {
                        for (; i; --i)
                            _alloc.destroy(tmp + i - 1);
                        _alloc.deallocate(tmp, _new_capacity);
                        for (i = 0; i < _size; ++i)
                            _alloc.destroy(p + i);
                        _alloc.deallocate(p, _capacity);
                        throw "vector";
                    }
                }
                for (iterator itEnd = end(); it != itEnd; ++it, ++i) {

                    try {
                        _alloc.construct(tmp + i, p[i - count]);
                    } catch (...) {
                        for (; i; --i)
                            _alloc.destroy(tmp + i - 1);
                        _alloc.deallocate(tmp, _new_capacity);
                        for (i = 0; i < _size; ++i)
                            _alloc.destroy(p + i);
                        _alloc.deallocate(p, _capacity);
                        throw "vector";
                    }
                }
                for (i = 0; i < _size; ++i)
                    _alloc.destroy(p + i);
                _alloc.deallocate(p, _capacity);
                _capacity = _new_capacity;
                p = tmp;
            } else {

                size_type i = _size + count - 1;
                for (iterator it = end() + count - 1; it != pos; --it, --i) {

                    try {
                        if (i < _size)
                            _alloc.destroy(p + i);
                        _alloc.construct(p + i, p[i - count]);
                    } catch (...) {
                        size_type i_tmp = i;
                        for (; i < _size + count; ++i)
                            _alloc.destroy(p + i);
                        for (i = 0; i < i_tmp; ++i)
                            _alloc.destroy(p + i);
                        _alloc.deallocate(p, _capacity);
                        throw "vector";
                    }
                }
                for (size_type _count = count; _count; --_count, --i) {

                    try {
                        if (i < _size)
                            _alloc.destroy(p + i);
                        _alloc.construct(p + i, value);
                    } catch (...) {
                        size_type i_tmp = i;
                        for (; i < _size + count; ++i)
                            _alloc.destroy(p + i);
                        for (i = 0; i < i_tmp; ++i)
                            _alloc.destroy(p + i);
                        _alloc.deallocate(p, _capacity);
                        throw "vector";
                    }
                }
            }
            _size += count;
        }

        template<class InputIt>
        void insert(iterator pos, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first,
                    InputIt last) {

            size_type count = last - first;

            if (_size + count > _capacity) {

                size_type _new_capacity = _capacity ? _capacity * 2 : 1;
                while (_size + count > _new_capacity)
                    _new_capacity *= 2;
                pointer tmp;
                try {
                    tmp = _alloc.allocate(_new_capacity);
                } catch (...) {
                    destroyVector();
                    throw "vector: couldn't allocate memory";
                }
                size_type i = 0;
                for (iterator it = begin(); it != pos; ++it, ++i) {

                    try {
                        _alloc.construct(tmp + i, p[i]);
                    } catch (...) {
                        for (; i; --i)
                            _alloc.destroy(tmp + i - 1);
                        _alloc.deallocate(tmp, _new_capacity);
                        for (i = 0; i < _size; ++i)
                            _alloc.destroy(p + i);
                        _alloc.deallocate(p, _capacity);
                        throw "vector";
                    }
                }
                for (; first != last; ++first, ++i) {

                    try {
                        _alloc.construct(tmp + i, *first);
                    } catch (...) {
                        for (; i; --i)
                            _alloc.destroy(tmp + i - 1);
                        _alloc.deallocate(tmp, _new_capacity);
                        for (i = 0; i < _size; ++i)
                            _alloc.destroy(p + i);
                        _alloc.deallocate(p, _capacity);
                        throw "vector";
                    }
                }
                for (; i - count < _size; ++i) {

                    try {
                        _alloc.construct(tmp + i, p[i - count]);
                    } catch (...) {
                        for (; i; --i)
                            _alloc.destroy(tmp + i - 1);
                        _alloc.deallocate(tmp, _new_capacity);
                        for (i = 0; i < _size; ++i)
                            _alloc.destroy(p + i);
                        _alloc.deallocate(p, _capacity);
                        throw "vector";
                    }
                }
                destroyVector();
                _capacity = _new_capacity;
                _size += count;
                p = tmp;
            } else {

                size_type stopCopying = count + (pos - begin());
                size_type i = _size + count;
                for (; i != stopCopying; --i) {

                    try {
                        if (i - 1 < _size)
                            _alloc.destroy(p + i - 1);
                        _alloc.construct(p + i - 1, p[i - count - 1]);
                    } catch (...) {
                        for (size_type _count = i; _count != _size + count - 1; ++_count)
                            _alloc.destroy(p + _count + 1);
                        for (; i; --i)
                            _alloc.destroy(p + i - 1);
                        _alloc.deallocate(p, _capacity);
                        throw "vector";
                    }
                }
                for (; last != first; --last, --i) {

                    try {
                        if (i < _size)
                            _alloc.destroy(p + i - 1);
                        _alloc.construct(p + i - 1, *(last - 1));
                    } catch (...) {
                        for (size_type _count = i; _count != _size + count - 1; ++_count)
                            _alloc.destroy(p + _count + 1);
                        for (; i; --i)
                            _alloc.destroy(p + i - 1);
                        _alloc.deallocate(p, _capacity);
                        throw "vector";
                    }
                }
                _size += count;
            }
        }

        iterator erase(iterator pos) {

            iterator erase = begin();
            size_type count = 0;
            for (; erase != pos; ++erase, ++count);
            for (; count != _size - 1; ++count) {

                _alloc.destroy(p + count);
                try {
                    _alloc.construct(p + count, *(p + count + 1));
                } catch (...) {
                    for (size_type i = count + 1; i != _size; ++i)
                        _alloc.destroy(p + i);
                    for (size_type i = count; i; --i)
                        _alloc.destroy(p + i - 1);
                    _alloc.deallocate(p, _capacity);
                    throw "vector";
                }
            }
            _alloc.destroy(p + count + 1);
            --_size;
            return pos;
        }

        iterator erase(iterator first, iterator last) {

            iterator it = begin();
            size_type n = first - it;
            size_type count = last - first;
            if (count == 0)
                return last;
            for (size_type i = 0; i < count; ++i)
                _alloc.destroy(p + n + i);
            for (size_type i = n + count; i < _size; ++i) {

                try {
                    _alloc.construct(p + i - count, p[i]);
                } catch (...) {
                    for (size_type j = 0; j < i - count; ++j)
                        _alloc.destroy(p + j);
                    for (size_type j = i; j < _size; ++j)
                        _alloc.destroy(p + j);
                    _size = 0;
                    throw;
                }
                _alloc.destroy(p + i);
            }
            if (last == end())
                n = _size - count;
            _size -= count;
            return iterator(p + n);
        }

        void push_back(const T &value) {

            if (_size == _capacity) {

                size_type _new_capacity = _capacity ? _capacity * 2 : 1;
                pointer tmp;
                try {
                    tmp = _alloc.allocate(_new_capacity);
                } catch (...) {
                    destroyVector();
                    throw "vector: couldn't allocate memory";
                }
                for (size_type i = 0; i < _size; ++i) {

                    try {
                        _alloc.construct(tmp + i, p[i]);
                    } catch (...) {
                        for (; i; --i)
                            _alloc.destroy(tmp + i - 1);
                        _alloc.deallocate(tmp, _new_capacity);
                        for (size_type j = 0; j < _size; ++j)
                            _alloc.destroy(p + j);
                        _alloc.deallocate(p, _capacity);
                        throw "vector";
                    }
                }
                for (size_type j = 0; j < _size; ++j)
                    _alloc.destroy(p + j);
                _alloc.deallocate(p, _capacity);
                _capacity = _new_capacity;
                p = tmp;
            }
            try {
                _alloc.construct(p + _size, value);
            } catch (...) {
                for (size_type i = 0; i < _size; ++i)
                    _alloc.destroy(p + i);
                _alloc.deallocate(p, _capacity);
                throw "vector";
            }
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

        void swap(Vector &other) {

            std::swap(p, other.p);
            std::swap(_size, other._size);
            std::swap(_capacity, other._capacity);
            std::swap(_alloc, other._alloc);
        }

    };

    template<class T, class Allocator>
    bool operator==(const ft::Vector<T, Allocator> &lhs, const ft::Vector<T, Allocator> &rhs) {
        if (lhs.size() == rhs.size()) {
            size_t i = 0;
            for (; i < lhs.size() && lhs[i] == rhs[i]; i++);
            if (i == lhs.size())
                return true;
        }
        return false;
    }

    template<class T, class Allocator>
    bool operator!=(const ft::Vector<T, Allocator> &lhs, const ft::Vector<T, Allocator> &rhs) { return !(lhs == rhs); }

    template<class T, class Allocator>
    bool operator<(const ft::Vector<T, Allocator> &lhs, const ft::Vector<T, Allocator> &rhs) {
        int size = lhs.size() > rhs.size() ? rhs.size() : lhs.size();
        for (int i = 0; i < size; i++)
            if (rhs[i] != lhs[i])
                return lhs[i] < rhs[i];
        return lhs.size() < rhs.size();
    }

    template<class T, class Allocator>
    bool operator<=(const ft::Vector<T, Allocator> &lhs, const ft::Vector<T, Allocator> &rhs) {
        return lhs == rhs || lhs < rhs;
    }

    template<class T, class Allocator>
    bool operator>(const ft::Vector<T, Allocator> &lhs, const ft::Vector<T, Allocator> &rhs) { return !(lhs <= rhs); }

    template<class T, class Allocator>
    bool operator>=(const ft::Vector<T, Allocator> &lhs, const ft::Vector<T, Allocator> &rhs) { return !(lhs < rhs); }
}

namespace std {

	template <class T, class Alloc>
	void swap (ft::Vector<T,Alloc>& x, ft::Vector<T,Alloc>& y) {
		x.swap(y);
	}
}
