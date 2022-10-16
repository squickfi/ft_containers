#pragma once

#include "ft_utility.hpp"
#include "ft_algorithm.hpp"
#include "RBTree.hpp"

namespace ft {

    template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > >
    class Map {
    public:
        typedef Key										key_type;
        typedef T										mapped_type;
        typedef ft::pair<const Key, T>					value_type;
        typedef std::size_t								size_type;
        typedef std::ptrdiff_t							difference_type;
        typedef	Compare									key_compare;
        typedef Allocator								allocator_type;
        typedef value_type&								reference;
        typedef const value_type&						const_reference;
        typedef typename allocator_type::pointer		pointer;
        typedef typename allocator_type::const_pointer	const_pointer;
        typedef ft::tree_iterator<value_type>			iterator;
        typedef ft::tree_iterator<value_type>			const_iterator;
        typedef ft::reverse_iterator<iterator>			reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
        class value_compare {
        protected:
            key_compare _comp;
        public:
            value_compare(key_compare comp = key_compare()) : _comp(comp) {}
            bool operator() (const value_type& lhs, const value_type& rhs) const
            {
                return (_comp(lhs.first, rhs.first));
            }
        };
    private:
        rb_tree<value_type, mapped_type, value_compare, allocator_type> _tree;
        key_compare _comp;
        ft::pair<key_type, mapped_type> pair_instance(const key_type& key) const
        {
            return (ft::make_pair(key, mapped_type()));
        }
    public:
        // constructors
        Map() : _tree(), _comp() {}
        explicit Map(const value_compare& comp, const allocator_type& alloc = allocator_type()) : _tree(comp, alloc), _comp(comp) {}
        template< class InputIt >
        Map(InputIt first, InputIt last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(comp, alloc), _comp(comp) {
            for (InputIt it = first; it != last; ++it)
                _tree.insert(*it);
        }
        Map(const Map& other) : _tree(other._tree), _comp(other._comp) {}
        // destructor
        ~Map() {
            clear();
        }
        // operator=
        Map& operator=(const Map& other) {
            _tree = other._tree;
            _comp = other._comp;
            return (*this);
        }
        // get_allocator
        allocator_type get_allocator() const {
            return (_tree.get_allocator());
        }
        // at
        mapped_type& at(const key_type& key) {
            iterator it = find(key);

            if (!it._node)
                throw std::out_of_range("map error: at");
            return (it->second);
        }
        const mapped_type& at(const key_type& key) const {
            const_iterator	it = find(key);

            if (!it._node)
                throw std::out_of_range("map error: at");
            return (it->second);
        }
        // operator[]
        mapped_type& operator[](const key_type& key) {
            return (insert(pair_instance(key)).first->second);
        }
        // begin, end, rbegin, rend
        iterator begin() {
            return (_tree.begin());
        }
        const_iterator begin() const {
            return (_tree.begin());
        }
        iterator end() {
            return (_tree.end());
        }
        const_iterator end() const {
            return (_tree.end());
        }
        reverse_iterator rbegin() {
            return (_tree.rbegin());
        }
        const_reverse_iterator rbegin() const {
            return (_tree.rbegin());
        }
        reverse_iterator rend() {
            return (_tree.rend());
        }
        const_reverse_iterator rend() const {
            return (_tree.rend());
        }
        // empty
        bool empty() const {
            return (_tree.empty());
        }
        // size
        size_type size() const {
            return (_tree.size());
        }
        // max_size
        size_type max_size() const {
            return (_tree.max_size());
        }
        // clear
        void clear() {
            _tree.clear();
        }
        // insert
        ft::pair<iterator,bool> insert(const value_type& value) {
            return (_tree.insert(value));
        }
        iterator insert(iterator hint, const value_type& value) {
            return (_tree.insert(hint, value));
        }
        template<class InputIt>
        void insert(InputIt first, InputIt last) {
            _tree.insert(first, last);
        }
        // erase
        void erase(iterator pos) {
            _tree.erase(pos);
        }
        void erase(iterator first, iterator last) {
            _tree.erase(first, last);
        }
        size_type erase(const key_type& key) {
            return (_tree.erase(pair_instance(key)));
        }
        // swap
        void	swap(Map & other) {
            _tree.swap(other._tree);
        }
        // count
        size_type count(const key_type& key) const {
            if (_tree.find(pair_instance(key), true) == _tree.end())
                return (0);
            return (1);
        }
        // find
        iterator find(const key_type& key)  {
            return (_tree.find(pair_instance(key), false));
        }
        const_iterator find(const key_type& key) const {
            return (_tree.find(pair_instance(key), false));
        }
        // equal_range
        ft::pair<iterator,iterator> equal_range(const key_type& key) {
            return (_tree.equal_range(pair_instance(key)));
        }
        ft::pair<const_iterator,const_iterator> equal_range(const key_type& key) const {
            return (_tree.equal_range(pair_instance(key)));
        }
        // lower_bound
        iterator lower_bound(const key_type& key) {
            return (_tree.lower_bound(pair_instance(key)));
        }

        const_iterator lower_bound(const key_type& key) const {
            return (_tree.lower_bound(pair_instance(key)));
        }
        // upper_bound
        iterator upper_bound(const key_type& key) {
            return(_tree.upper_bound(pair_instance(key)));
        }
        const_iterator upper_bound(const key_type& key) const {
            return (_tree.upper_bound(pair_instance(key)));
        }
        // key_comp
        key_compare key_comp() const {
            return (_comp);
        }
        // value_comp
        value_compare value_comp() const {
            return (value_compare(_comp));
        }
    };

    // operators == != < <= > >=

    template< class Key, class T, class Compare, class Allocator >
    bool	operator==(const ft::Map<Key, T, Compare, Allocator>& lhs, const ft::Map<Key, T, Compare, Allocator>& rhs) {
        if (lhs.size() != rhs.size())
            return (false);
        return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }

    template< class Key, class T, class Compare, class Allocator >
    bool	operator!=(const ft::Map<Key, T, Compare, Allocator>& lhs, const ft::Map<Key, T, Compare, Allocator>& rhs) {
        if (lhs.size() != rhs.size())
            return (true);
        return (!ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }

    template< class Key, class T, class Compare, class Allocator >
    bool	operator<(const ft::Map<Key, T, Compare, Allocator>& lhs, const ft::Map<Key, T, Compare, Allocator>& rhs) {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

    template< class Key, class T, class Compare, class Allocator >
    bool	operator<=(const ft::Map<Key, T, Compare, Allocator>& lhs, const ft::Map<Key, T, Compare, Allocator>& rhs) {
        return (!ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
    }

    template< class Key, class T, class Compare, class Allocator >
    bool	operator>(const ft::Map<Key, T, Compare, Allocator>& lhs, const ft::Map<Key, T, Compare, Allocator>& rhs) {
        return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
    }

    template< class Key, class T, class Compare, class Allocator >
    bool	operator>=(const ft::Map<Key, T, Compare, Allocator>& lhs, const ft::Map<Key, T, Compare, Allocator>& rhs) {
        return (!ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }
}

namespace std
{
    template<class Key, class T, class Compare, class Allocator>
    void	swap(ft::Map<Key, T, Compare, Allocator>& lhs, ft::Map<Key, T, Compare, Allocator>& rhs) {
        lhs.swap(rhs);
    }
}
