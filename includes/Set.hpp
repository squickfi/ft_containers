#pragma once

#include "ft_utility.hpp"
#include "ft_algorithm.hpp"
#include "RBTree.hpp"

namespace ft {
    template<class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
    class Set {
    public:
        typedef Key										key_type;
        typedef Key										value_type;
        typedef std::size_t								size_type;
        typedef std::ptrdiff_t							difference_type;
        typedef Compare									key_compare;
        typedef Compare									value_compare;
        typedef Allocator								allocator_type;
        typedef value_type&								reference;
        typedef const value_type&						const_reference;
        typedef typename allocator_type::pointer		pointer;
        typedef typename allocator_type::const_pointer	const_pointer;
        typedef ft::tree_iterator<value_type>			iterator;
        typedef ft::tree_iterator<value_type>			const_iterator;
        typedef ft::reverse_iterator<iterator>			reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
    private:
        rb_tree<value_type, key_type, key_compare, allocator_type> _tree;
        key_compare _comp;
    public:
        //CONSTRUCTOR ------------------------------------------------------------------------
        Set() : _tree(), _comp() {}
        explicit Set(const value_compare& comp, const allocator_type& alloc = allocator_type()) : _tree(comp, alloc), _comp(comp) {}
        template< class InputIt >
        Set(InputIt first, InputIt last, const value_compare& comp = value_compare(), const allocator_type& alloc = allocator_type())
        {
            for (InputIt it = first; it != last; ++it)
                _tree.insert(*it);
        }
        Set(const Set& other) : _tree(other._tree), _comp(other._comp) {}
        //DESTRUCTOR ------------------------------------------------------------------------
        ~Set()
        {
            clear();
        }
        //OPERATOR= ------------------------------------------------------------------------
        Set& operator=(const Set& other)
        {
            _tree = other._tree;
            _comp = other._comp;
            return (*this);
        }
        //GET_ALLOCATOR ------------------------------------------------------------------------
        allocator_type get_allocator() const
        {
            return (_tree.get_allocator());
        }
        //BEGIN, END, RBEGIN, REND ------------------------------------------------------------------------
        iterator begin()
        {
            return (_tree.begin());
        }
        const_iterator begin() const
        {
            return (_tree.begin());
        }
        iterator end()
        {
            return (_tree.end());
        }
        const_iterator end() const
        {
            return (_tree.end());
        }
        reverse_iterator rbegin()
        {
            return (_tree.rbegin());
        }
        const_reverse_iterator rbegin() const
        {
            return (_tree.rbegin());
        }
        reverse_iterator rend()
        {
            return (_tree.rend());
        }
        const_reverse_iterator rend() const
        {
            return (_tree.rend());
        }
        //EMPTY ------------------------------------------------------------------------
        bool empty() const
        {
            return (_tree.empty());
        }
        //SIZE ------------------------------------------------------------------------
        size_type size() const
        {
            return (_tree.size());
        }
        //MAX_SIZE ------------------------------------------------------------------------
        size_type max_size() const
        {
            return (_tree.max_size());
        }
        //CLEAR ------------------------------------------------------------------------
        void clear()
        {
            _tree.clear();
        }
        //INSERT ------------------------------------------------------------------------
        ft::pair<iterator,bool> insert(const value_type& value)
        {
            return (_tree.insert(value));
        }
        iterator insert(iterator hint, const value_type& value)
        {
            return (_tree.insert(hint, value));
        }
        template< class InputIt >
        void insert(InputIt first, InputIt last)
        {
            _tree.insert(first, last);
        }
        //ERASE ------------------------------------------------------------------------
        void erase(iterator pos)
        {
            _tree.erase(pos);
        }
        void erase(iterator first, iterator last)
        {
            _tree.erase(first, last);
        }
        size_type erase(const key_type& key)
        {
            return (_tree.erase(key));
        }
        //SWAP ------------------------------------------------------------------------
        void swap(Set& other)
        {
            _tree.swap(other._tree);
        }
        //FIND ------------------------------------------------------------------------
        iterator find(const key_type& key)
        {
            return (_tree.find(key, true));
        }
        const_iterator find(const key_type& key) const
        {
            return (_tree.find(key, true));
        }
        //COUNT ------------------------------------------------------------------------
        size_type count(const key_type& key) const
        {
            if (_tree.find(key, true) == _tree.end())
                return (0);
            return (1);
        }
        //EQUAL_RANGE ------------------------------------------------------------------------
        ft::pair<iterator, iterator> equal_range(const key_type& key)
        {
            return (_tree.equal_range(key));
        }
        ft::pair<const_iterator, const_iterator> equal_range(const key_type& key) const
        {
            return (_tree.equal_range(key));
        }
        //LOWER_BOUND ------------------------------------------------------------------------
        iterator lower_bound(const key_type& key)
        {
            return (_tree.lower_bound(key));
        }
        const_iterator lower_bound(const key_type& key) const
        {
            return (_tree.lower_bound(key));
        }
        //UPPER_BOUND ------------------------------------------------------------------------
        iterator upper_bound(const key_type& key)
        {
            return (_tree.upper_bound(key));
        }
        const_iterator upper_bound(const key_type& key) const
        {
            return (_tree.upper_bound(key));
        }
        //KEY_COMP ------------------------------------------------------------------------
        key_compare key_comp() const
        {
            return (_comp);
        }
        //VALUE_COMP ------------------------------------------------------------------------
        value_compare value_comp() const
        {
            return (value_compare(_comp));
        }
    };
    //OPERATOR == != < <= > >= ------------------------------------------------------------------------
    template< class Key, class Compare, class Allocator >
    bool	operator==(const ft::Set<Key, Compare, Allocator>& lhs, const ft::Set<Key, Compare, Allocator>& rhs)
    {
        if (lhs.size() != rhs.size())
            return (false);
        return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }
    template< class Key, class Compare, class Allocator >
    bool	operator!=(const ft::Set<Key, Compare, Allocator>& lhs, const ft::Set<Key, Compare, Allocator>& rhs)
    {
        if (lhs.size() != rhs.size())
            return (true);
        return (!ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }
    template< class Key, class Compare, class Allocator >
    bool	operator<(const ft::Set<Key, Compare, Allocator>& lhs, const ft::Set<Key, Compare, Allocator>& rhs)
    {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }
    template< class Key, class Compare, class Allocator >
    bool	operator<=(const ft::Set<Key, Compare, Allocator>& lhs, const ft::Set<Key, Compare, Allocator>& rhs)
    {
        return (!ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
    }
    template< class Key, class Compare, class Allocator >
    bool	operator>(const ft::Set<Key, Compare, Allocator>& lhs, const ft::Set<Key, Compare, Allocator>& rhs)
    {
        return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
    }
    template< class Key, class Compare, class Allocator >
    bool	operator>=(const ft::Set<Key, Compare, Allocator>& lhs, const ft::Set<Key, Compare, Allocator>& rhs)
    {
        return (!ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }
}

namespace std
{
    template <class Key, class Compare, class Allocator>
    void	swap(ft::Set<Key, Compare, Allocator>& lhs, ft::Set<Key, Compare, Allocator>& rhs)
    {
        lhs.swap(rhs);
    }
}