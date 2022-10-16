/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobject <jobject@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:10:49 by jobject           #+#    #+#             */
/*   Updated: 2022/02/16 17:39:04 by jobject          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <memory>
# include <functional>
# include "ft_iterator.hpp"
# include "ft_utility.hpp"

namespace ft {

    enum COLOR{BLACK, RED};

    template<class T>
    struct node_tree {
        typedef T	data_type;
        data_type   data;
        node_tree*	parent;
        node_tree*  left;
        node_tree*	right;
        COLOR       color;

        explicit node_tree() : data(NULL), parent(NULL), left(NULL), right(NULL), color(RED) {}
        node_tree(const data_type& d, node_tree* par, node_tree* lft, node_tree* rght, COLOR col) : data(d), parent(par), left(lft), right(rght), color(col) {}
        node_tree& operator=(const node_tree& nt) {
        	data = nt.data;
        	right = nt.right;
        	left = nt.left;
        	parent = nt.parent;
        	color = nt.color;
        	return (*this);
        }
    };

    template<class IteratorType>
    class tree_iterator {
    public:
        typedef	IteratorType													iterator_type;
        typedef std::bidirectional_iterator_tag									iterator_category;
        typedef typename ft::iterator_traits<iterator_type*>::value_type		value_type;
        typedef typename ft::iterator_traits<iterator_type*>::difference_type	difference_type;
        typedef typename ft::iterator_traits<iterator_type*>::pointer			pointer;
        typedef typename ft::iterator_traits<iterator_type*>::reference			reference;
        typedef typename ft::iterator_traits<const iterator_type*>::pointer		const_pointer;
        typedef typename ft::iterator_traits<const iterator_type*>::reference	const_reference;
        typedef	node_tree<iterator_type>										node;

        node* _node;
        node* _root;
    private:
        node* tree_min(node* x)
        {
            while (x->left != NULL)
                x = x->left;
            return (x);
        }
        node* tree_max(node* x)
        {
            while (x->right != NULL)
                x = x->right;
            return (x);
        }
        node* tree_parent(node* x, bool is_left)
        {
            if (is_left)
                while (x->parent && x->parent->left == x)
                    x = x->parent;
            else
                while (x->parent && x->parent->right == x)
                    x = x->parent;
            x = x->parent;
            return (x);
        }
    public:
        tree_iterator() {}
        tree_iterator(node* n, node* r) : _node(n), _root(r) {}
        tree_iterator(const tree_iterator& it) : _node(it._node), _root(it._root) {}
        ~tree_iterator() {}
        tree_iterator& operator=(const tree_iterator& it)
        {
            _node = it._node;
            _root = it._root;
            return (*this);
        }
        reference operator*()
        {
            return (_node->data);
        }
        reference operator*() const
        {
            return (_node->data);
        }
        pointer operator->()
        {
            return (&_node->data);
        }
        pointer operator->() const
        {
            return (&_node->data);
        }
        tree_iterator& operator++()
        {
            if (!_node && !_root)
                return (*this);
            if (!_node)
                _node = tree_min(_root);
            else
            {
                if (_node->right)
                    _node = tree_min(_node->right);
                else
                    _node = tree_parent(_node, false);
            }
            return (*this);
        }
        tree_iterator operator++ (int)
        {
            tree_iterator temp(*this);
            ++(*this);
//            std::cout << "....!!!!!!!!!!!!!!!!!!" << std::endl;
            return (temp);
        }
        tree_iterator& operator-- ()
        {
            if (!_node && !_root)
                return (*this);
            if (!_node)
                _node = tree_max(_root);
            else
            {
                if (_node->left)
                    _node = tree_max(_node->left);
                else
                    _node = tree_parent(_node, true);
            }
            return (*this);
        }
        tree_iterator operator-- (int)
        {
            tree_iterator temp(*this);
            --(*this);
            return (temp);
        }
        friend bool operator== (const tree_iterator& lhs, const tree_iterator& rhs)
        {
            return (lhs._node == rhs._node);
        }
        friend bool operator!= (const tree_iterator& lhs, const tree_iterator& rhs)
        {
            return (lhs._node != rhs._node);
        }
    };

    template<class Key, class T, class Compare, class Allocator >
    class rb_tree {
    public:
        typedef	Key														value_type;
        typedef std::size_t												size_type;
        typedef std::ptrdiff_t											difference_type;
        typedef Compare													compare_type;
        typedef Allocator												allocator_type;
        typedef node_tree<value_type>									node;
        typedef typename allocator_type::template rebind<node>::other	node_allocator;
        typedef ft::tree_iterator<value_type>							iterator;
        typedef ft::tree_iterator<value_type>							const_iterator;
        typedef ft::reverse_iterator<iterator>							reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
    private:
        size_type		_size;
        allocator_type	_alloc_value;
        node_allocator	_alloc_node;
        compare_type	_comp;
        node*			_root;
    public:
        //CONSTRUCTOR ------------------------------------------------------------------------
        rb_tree() : _size(0), _alloc_value(allocator_type()), _alloc_node(node_allocator()), _comp(), _root(NULL) {}
        explicit rb_tree(const compare_type& comp, const allocator_type& alloc = allocator_type()) : _size(0), _alloc_value(alloc), _alloc_node(node_allocator()), _comp(comp), _root(NULL) {}
        template< class InputIt >
        rb_tree(InputIt first, InputIt last, const compare_type& comp = compare_type(), const allocator_type& alloc = allocator_type()) : _size(0), _alloc_value(alloc), _alloc_node(node_allocator()), _comp(comp)
        {
            clear_tree(_root);
            for (InputIt it = first; it != last; ++it)
                insert(*it);
        }
        rb_tree(const rb_tree& other) : _size(other._size), _alloc_value(other._alloc_value), _alloc_node(other._alloc_node), _comp(other._comp), _root(NULL)
        {
            copy_tree(&_root, NULL, other._root);
        }
        //DESTRUCTOR ------------------------------------------------------------------------
        ~rb_tree()
        {
            clear_tree(_root);
        }
        //OPERATOR= ------------------------------------------------------------------------
        rb_tree& operator=(const rb_tree& other)
        {
            node* temp;

            copy_tree(&temp, NULL, other._root);
            clear_tree(_root);
            _root = temp;
            _size = other._size;
            return (*this);
        }
        //GET_ALLOCATOR ------------------------------------------------------------------------
        allocator_type get_allocator() const
        {
            return (_alloc_value);
        }
        //EMPTY ------------------------------------------------------------------------
        bool empty() const
        {
            return (!_root);
        }
        //SIZE ------------------------------------------------------------------------
        size_type size() const
        {
            return (_size);
        }
        //MAX_SIZE ------------------------------------------------------------------------
        size_type max_size() const
        {
            return (std::numeric_limits<difference_type>::max() / sizeof(difference_type));
        }
        //CLEAR ------------------------------------------------------------------------
        void clear()
        {
            clear_tree(_root);
        }
        //INSERT ------------------------------------------------------------------------
        ft::pair<iterator,bool> insert (const value_type& value)
        {
            node* n = new_node(value);
            node* y = NULL;
            node* x = _root;
            ft::pair<node*, bool> temp;
            int point = 0;

            while (x != NULL)
            {
                y = x;
                if (_comp(n->data, x->data))
                    x = x->left;
                else if (_comp(x->data, n->data))
                    x = x->right;
                else {
                    delete_node(n);
                    point = 1;
                    temp = ft::make_pair(x, false);
                    break ;
                }
            }
            if (!point) {
                n->parent = y;
                if (y == NULL) {
                    _root = n;
                }
                else if (_comp(n->data, y->data))
                    y->left = n;
                else if (_comp(y->data, n->data))
                    y->right = n;
                insert_fix(n);
                temp = ft::make_pair(n, true);
            }
            return (ft::make_pair(iterator(temp.first, _root), temp.second));
        }
        iterator insert(iterator hint, const value_type& value)
        {
            insert(value);
            return (iterator(hint._node, _root));
        }
        template<class InputIt>
        void insert(InputIt first, InputIt last)
        {

            for (InputIt it = first; it != last; ++it)
                insert(*it);
        }
        //ERASE ------------------------------------------------------------------------
        void erase(iterator pos)
        {
            node* n = pos._node;
            node* y = (n->left == NULL || n->right == NULL) ? n : tree_next(n);
            node* x = y->left != NULL ? y->left : y->right;
            node* w = NULL;

            if (x != NULL)
                x->parent = y->parent;
            if (!y->parent) {
                _root = n->right;
                delete_node(n);
            }
            else if (y->parent && y == y->parent->left) {
                y->parent->left = x;
                if (y != _root)
                    w = y->parent->right;
                else
                    _root = x;
                delete_node(n);
            }
            else if (y->parent && y != y->parent->left)
            {
                y->parent->right = x;
                w = y->parent->left;
                delete_node(n);
            }
            COLOR remove_black = y->color;
            if (y != n) {
                y->parent = n->parent;
                if (n->parent && n == n->parent->left) {
                    y->parent->left = y;
                } else {
//                std::cout << y->parent << ".......!!!!!................." << std::endl;
                    y->parent->right = y;
//                std::cout << ".......!!!!!................." << std::endl;
                }
                y->left = n->left;
                y->left->parent = y;
                y->right = n->right;
                if (y->right != NULL)
                    y->right->parent = y;
                y->color = n->color;
                if (_root == n)
                    _root = y;
            }
            if (remove_black == BLACK && _root != NULL)
                erase_fix(x, w);
        }
        void erase(iterator first, iterator last)
        {
            while (first != last) {
                erase(first++);
            }
        }
        size_type erase(const value_type& key)
        {
//            std::cout << "!!!!!!!!!!!!!!" << std::endl;
            iterator it = find(key, true);
//            std::cout << "!!!!!!!!!!!!!!" << std::endl;

            if (!it._node)
                return (0);
            erase(it);
            return (1);
        }
        //SWAP ------------------------------------------------------------------------
        void swap(rb_tree& other)
        {
            node* temp_root = _root;
            size_type temp_size = this->size();

            _root = other._root;
            _size = other._size;
            other._root = temp_root;
            other._size = temp_size;
        }
        //BEGIN, END, RBEGIN, REND ------------------------------------------------------------------------
        iterator begin()
        {
            node* temp = _root;

            if (temp)
                while (temp->left)
                    temp = temp->left;
            return (iterator(temp, _root));
        }
        const_iterator begin() const
        {
            node* temp = _root;

            if (temp)
                while (temp->left)
                    temp = temp->left;
            return (const_iterator(temp, _root));
        }
        iterator end()
        {
            return (iterator(NULL, _root));
        }
        const_iterator end() const
        {
            return (const_iterator(NULL, _root));
        }
        reverse_iterator rbegin()
        {
            return (reverse_iterator(end()));
        }
        const_reverse_iterator rbegin() const
        {
            return (const_reverse_iterator(end()));
        }
        reverse_iterator rend()
        {
            return (reverse_iterator(begin()));
        }
        const_reverse_iterator rend() const
        {
            return (const_reverse_iterator(begin()));
        }
        //FIND ------------------------------------------------------------------------
        iterator find(const value_type& key, bool is_er_cnt)
        {
            iterator it = lower_bound(key);
            if (it != end() && !_comp(key, *it))
                return (it);
            if (!is_er_cnt) {
                return (iterator());
            }
            return (end());
        }
        const_iterator find(const value_type& key, bool is_er_cnt) const
        {
            const_iterator it = lower_bound(key);
            if (it != end() && !_comp(key, *it))
                return (it);
            if (!is_er_cnt) {
                return (iterator());
            }
            return (end());
        }
        //EQUAL_RANGE ------------------------------------------------------------------------
        ft::pair<iterator, iterator> equal_range(const value_type& key)
        {
            typedef ft::pair<iterator, iterator> pp;
            node* res = NULL;
            node* rt = _root;

            while (rt != NULL)
            {
                if (_comp(key, rt->data))
                {
                    res = rt;
                    rt = rt->left;
                }
                else if (_comp(rt->data, key))
                    rt = rt->right;
                else
                    return (pp(iterator(rt, _root), iterator(rt->right != NULL ? tree_min(rt->right) : res, _root)));
            }
            return (pp(iterator(res, _root), iterator(res, _root)));
        }
        ft::pair<const_iterator, const_iterator> equal_range(const value_type& key) const
        {
            typedef ft::pair<iterator, iterator> pp;
            node* res = NULL;
            node* rt = _root;

            while (rt != NULL)
            {
                if (_comp(key, rt->data))
                {
                    res = rt;
                    rt = rt->left;
                }
                else if (_comp(rt->data, key))
                    rt = rt->right;
                else
                    return (pp(iterator(rt, _root), iterator(rt->right != NULL ? tree_min(rt->right) : res, _root)));
            }
            return (pp(iterator(res, _root), iterator(res, _root)));
        }
        //LOWER_BOUND ------------------------------------------------------------------------
        iterator lower_bound(const value_type& key)
        {
            node *curr = _root;
            node *res = NULL;

            while (curr != NULL)
            {
                if (!_comp(curr->data, key))
                {
                    res = curr;
                    curr = curr->left;
                }
                else
                    curr = curr->right;
            }
            return (iterator(res, _root));
        }
        const_iterator lower_bound(const value_type& key) const
        {
            node *curr = _root;
            node *res = NULL;

            while (curr != NULL)
            {
                if (!_comp(curr->data, key))
                {
                    res = curr;
                    curr = curr->left;
                }
                else
                    curr = curr->right;
            }
            return (const_iterator(res, _root));
        }
        //UPPER_BOUND ------------------------------------------------------------------------
        iterator upper_bound(const value_type& key)
        {
            node *curr = _root;
            node *res = NULL;

            while (curr != NULL)
            {
                if (_comp(key, curr->data))
                {
                    res = curr;
                    curr = curr->left;
                }
                else
                    curr = curr->right;
            }
            return (iterator(res, _root));
        }
        const_iterator upper_bound(const value_type& key) const
        {
            node *curr = _root;
            node *res = NULL;

            while (curr != NULL)
            {
                if (_comp(key, curr->value))
                {
                    res = curr;
                    curr = curr->left;
                }
                else
                    curr = curr->right;
            }
            return (const_iterator(res, _root));
        }

    private:
        node* tree_min(node* x)
        {
            while (x->left != NULL)
                x = x->left;
            return (x);
        }
        node* tree_max(node* x)
        {
            while (x->right != NULL)
                x = x->right;
            return (x);
        }
        node* tree_next(node* n)
        {
            if (n->right != NULL)
                return (tree_min(n->right));
            while (n != n->parent->left)
                n = n->parent;
            n = n->parent;
            return (n);
        }
        node*	new_node(const value_type& data, node *parent = NULL, node *left = NULL, node *right = NULL, COLOR col = RED)
        {
            node* temp = _alloc_node.allocate(1);

            _alloc_node.construct(temp, node(data, parent, left, right, col));
            ++_size;
            return (temp);
        }
        void	copy_tree(node** old_n, node* old_n_par, node* new_n)
        {
            if (new_n) {
                *old_n = new_node(new_n->data, old_n_par);
                copy_tree(&(*old_n)->left, *old_n, new_n->left);
                copy_tree(&(*old_n)->right, *old_n, new_n->right);
            }
        }
        void	delete_node(node *n)
        {
            _alloc_node.destroy(n);
            _alloc_node.deallocate(n, 1);
            --_size;
        }
        void	clear_tree(node *n)
        {
            if (n) {
                clear_tree(n->left);
                clear_tree(n->right);
                delete_node(n);
            }
            else
                _root = NULL;
        }
        void insert_fix(node *n)
        {
            if (n == _root)
                n->color = BLACK;
            else
                n->color = RED;
            while (n != _root && n->parent &&  n->parent->color == RED)
            {
                if (n == n->parent->left)
                {
                    node* y = n->parent->parent->right;
                    if (y != NULL && y->color == RED)
                    {
                        n = n->parent;
                        n->color = BLACK;
                        n = n->parent;
                        if (n == _root)
                            n->color = BLACK;
                        else
                            n->color = RED;
                        y->color = BLACK;
                    }
                    else
                    {
                        n = n->parent;
                        n->color = BLACK;
                        n = n->parent;
                        n->color = RED;
                        tree_right_rotate(n);
                        break ;
                    }
                }
                else
                {
                    node* y = n->parent->parent->left;
                    if (y != NULL && y->color == RED)
                    {
                        n = n->parent;
                        n->color = BLACK;
                        n = n->parent;
                        if (n == _root)
                            n->color = BLACK;
                        else
                            n->color = RED;
                        y->color = BLACK;
                    }
                    else
                    {
                        n = n->parent;
                        n->color = BLACK;
                        n = n->parent;
                        n->color = RED;
                        tree_left_rotate(n);
                        break ;
                    }
                }
            }
        }
        void erase_fix(node *x, node *w)
        {
            if (x != NULL)
                x->color = BLACK;
            else
            {
                while (true)
                {
                    if (w != w->parent->left)
                    {
                        if (w->color == RED)
                        {
                            w->color = BLACK;
                            w->parent->color = RED;
                            tree_left_rotate(w->parent);
                            if (_root == w->left)
                                _root = w;
                            w = w->left->right;
                        }
                        if ((w->left == NULL || w->left->color == BLACK) && (w->right == NULL || w->right->color == BLACK))
                        {
                            w->color = RED;
                            x = w->parent;
                            if (x == _root || x->color == RED)
                            {
                                x->color = BLACK;
                                break ;
                            }
                            if (x == x->parent->left)
                                w = x->parent->right;
                            else
                                w = x->parent->left;
                        }
                        else
                        {
                            if (w->right == NULL || w->right->color == BLACK)
                            {
                                w->left->color = BLACK;
                                w->color = RED;
                                tree_right_rotate(w);
                                w = w->parent;
                            }
                            w->color = w->parent->color;
                            w->parent->color = BLACK;
                            w->right->color = BLACK;
                            tree_left_rotate(w->parent);
                            break;
                        }
                    }
                    else
                    {
                        if (w->color == RED)
                        {
                            w->color = BLACK;
                            w->parent->color = RED;
                            tree_right_rotate(w->parent);
                            if (_root == w->right)
                                _root = w;
                            w = w->right->left;
                        }
                        if ((w->left == NULL || w->left->color == BLACK) && (w->right == NULL || w->right->color == BLACK))
                        {
                            w->color = RED;
                            x = w->parent;
                            if (x->color == RED || x == _root)
                            {
                                x->color = BLACK;
                                break;
                            }
                            if (x == x->parent->left)
                                w = x->parent->right;
                            else
                                w = x->parent->left;
                        }
                        else
                        {
                            if (w->left == NULL || w->left->color == BLACK)
                            {
                                w->right->color = BLACK;
                                w->color = RED;
                                tree_left_rotate(w);
                                w = w->parent;
                            }
                            w->color = w->parent->color;
                            w->parent->color = BLACK;
                            w->left->color = BLACK;
                            tree_right_rotate(w->parent);
                            break;
                        }
                    }
                }
            }
        }
        void tree_left_rotate(node * n)
        {
            node* y = n->right;
            n->right = y->left;

            if (n->right != NULL)
                n->right->parent = n;
            y->parent = n->parent;
            if (n->parent == NULL)
                _root = y;
            else if (n == n->parent->right)
                n->parent->right = y;
            else
                n->parent->left = y;
            y->left = n;
            n->parent = y;
        }
        void tree_right_rotate(node * n)
        {
            node* y = n->left;
            n->left = y->right;

            if (n->left != NULL)
                n->left->parent = n;
            y->parent = n->parent;
            if (n->parent == NULL)
                _root = y;
            else if (n == n->parent->left)
                n->parent->left = y;
            else
                n->parent->right = y;
            y->right = n;
            n->parent = y;
        }
    };
}

