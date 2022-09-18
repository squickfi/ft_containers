#include <iostream>
#include "ft_utility.hpp"
#include "ft_iterator.hpp"

namespace ft {

    template <class T>
    struct RBTreeNode {
        RBTreeNode* parent;
        RBTreeNode* left;
        RBTreeNode* right;
        T value;
        bool isRed;
        RBTreeNode(T value, RBTreeNode* parent = NULL, RBTreeNode* left = NULL, RBTreeNode* right = NULL, bool isRed = true)
            : value(value), parent(parent), left(left), right(right), isRed(isRed) {}
    };

    template <class T>
    class RBTreeIterator {

    public:

        typedef typename ft::iterator_traits<T *>::value_type value_type;
        typedef typename ft::iterator_traits<T *>::reference reference;
        typedef typename ft::iterator_traits<T *>::pointer pointer;
        typedef typename ft::iterator_traits<T *>::difference_type difference_type;
        typedef typename ft::iterator_traits<T *>::iterator_category iterator_category;
        typedef typename ft::iterator_traits<T *>::pointer iterator_type;
        typedef RBTreeNode<T> Node;

    private:

        Node* node;
        Node* root;

    public:

        RBTreeIterator() {}

        RBTreeIterator(Node *node, Node* root) : node(node), root(root) {}

        RBTreeIterator(Node* root) : root(root) {}

        RBTreeIterator(const RBTreeIterator &other) : node(other.node), root(other.root) {}

        RBTreeIterator &operator=(const RBTreeIterator &other) { node = other.node; root = other.root; }

        reference operator*() { return node->value; }

        pointer operator->() { return &operator*(); }

        bool operator==(const RBTreeIterator &other) { return node == other._node; }

        bool operator!=(const RBTreeIterator &other) { return *this != other; }

        RBTreeIterator &operator++() {

            if (node) {

                if (node->right) {
                    node = node->right;
                    while (node->left) {
                        node = node->left;
                    }
                } else if (isLeftChild(node)) {
                    node = node->parent;
                } else {
                    while (isRightChild(node)) {
                        node = node->parent;
                    }
                    node = node->parent;
                }
            }
            return *this;
        }

        RBTreeIterator operator++(int) {
            RBTreeIterator tmp(*this);
            operator++();
            return tmp;
        }

        RBTreeIterator &operator--() {

            if (node) {

                if (node->left) {
                    node = node->left;
                    while (node->right) {
                        node = node->right;
                    }
                } else if (isRightChild(node)) {
                    node = node->parent;
                } else {
                    while (isLeftChild(node)) {
                        node = node->parent;
                    }
                    node = node->parent;
                }
            }
            else {
                Node* node = root;
                while (node->right) {
                    node = node->right;
                }
                this->node = node;
            }
            return *this;
        }

        RBTreeIterator operator--(int) {
            RBTreeIterator tmp(*this);
            operator--();
            return tmp;
        }

    };

    template <class T, class Compare = std::less<T>, class Allocator = std::allocator<RBTreeNode<T> > >
    class RBTree {

    public:

        typedef T value_type;
        typedef unsigned long size_type;
        typedef Allocator allocator_type;
        typedef Compare comparator_type;
        typedef RBTreeNode<T> Node;
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef RBTreeIterator<value_type> iterator;
        typedef RBTreeIterator<const value_type> const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

    private:

        Node *root;
        allocator_type alloc;
        comparator_type comp;
        size_type size;

        Node* createNode(const T& data, Node* previous = NULL, Node* left = NULL, Node* right = NULL, bool is_red = true) {

            Node* node;
            try {
                node = alloc.allocate(1);
            } catch (...) {
                throw;
            }
            try {
                alloc.construct(node, Node(data, previous, left, right, is_red));
            } catch (...) {
                alloc.deallocate(node, 1);
                throw;
            }
            ++size;
            return node;
        }

        void removeNode(Node* node) {
            alloc.destroy(node);
            alloc.deallocate(node, 1);
            --size;
        }

    public:

        /* constructors */

        RBTree() {}

        explicit RBTree(const Compare& comp, const Allocator& alloc = Allocator())
            : comp(comp), alloc(alloc) {}

        template <class InputIt>
        RBTree(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()) {
            for (; first != last; ++first) {
                insert(*first);
            }
        }

        RBTree(const RBTree& other) { // TODO HERE!!!
            for (iterator it = other.begin(); it != other.end(); ++it) {
                insert(*it);
            }
        }

        RBTree& operator=(const RBTree& other) {
            clear();
            for (iterator it = other.begin(); it != other.end(); ++it) {
                insert(root, *it);
            }
        }

        ~RBTree() { clear(); }

        iterator find(value_type value) {
            Node* node = root;
            while (node) {
                if (_comp(node->_value, value)) {
                    node = node->_right;
                }
                else if (value, _comp(node->_value)) {
                    node = node->_left;
                }
                else {
                    return iterator(node, root);
                }
            }
            return NULL;
        }

        ft::pair<iterator, bool> insert(const value_type& value) { return insert(root, value); }

        ft::pair<iterator, bool> insert(Node* node, const value_type& value) {

            Node* parent = node ? node->parent : NULL;
            bool isLeft = true;
            while (node) {
                if (comp(value, node->value)) {
                    parent = node;
                    node = node->left;
                    isLeft = true;
                }
                else if (comp(node->value, value)) {
                    parent = node;
                    node = node->right;
                    isLeft = false;
                }
                else {
                    return ft::make_pair(iterator(node, root), false);
                }
            }
            try {
                node = createNode(value, parent);
            } catch (...) {
                clear();
                throw;
            }
            if (!root) {
                root = node;
            }
            if (parent) {
                isLeft ? parent->left = node : parent->right = node;
            }
            balanceInsert(node);
            ++size;
            return ft::make_pair(iterator(node, root), true);
        }

        void clear() { clear(root); }

        iterator erase(iterator pos) {

            iterator toReturn(pos);
            ++toReturn;
            Node* node = findNode(*pos);
            if (!node) {
                return NULL;
            }
            bool isRemovedRed = node->isRed;
            bool isRemovedLeft = isLeftChild(node);
            Node* nodeToPaste = node->right;
            Node* nodeParent = node->parent;

            if (node->left && node->right) {
                while (nodeToPaste->left) {
                    nodeToPaste = nodeToPaste->left;
                }
                nodeToPaste->parent = nodeParent;
                nodeToPaste->left = node->left;
                nodeToPaste->right = node->right;
            }
            else if (node->left || node->right) {
                nodeToPaste = node->left ? node->left : node->right;
                nodeToPaste->parent = nodeParent;
                nodeToPaste->isRed = false;
            }
            if (nodeParent) {
                isLeftChild(node) ?
                        nodeParent->left = nodeToPaste : nodeParent->right = nodeToPaste;
            }
            removeNode(node);
            if (!isRemovedRed) {
                isRemovedLeft ? balanceLeftErase(nodeParent) : balanceRightErase(nodeParent);
            }
            if (node == root) {
                root = nodeToPaste;
            }
            --size;
            return toReturn;
        }

        iterator begin() {
            Node* node = root;
            while (node->left) {
                node = node->left;
            }
            return iterator(node, root);
        }

        const_iterator begin() const {
            Node* node = root;
            while (node->left) {
                node = node->left;
            }
            return const_iterator(node, root);
        }

        iterator end() { return iterator(); }

        const_iterator end() const { return const_iterator(); }

        reverse_iterator rbegin() { return reverse_iterator(); }

        const_reverse_iterator rbegin() const { return const_reverse_iterator(); }

        reverse_iterator rend() {
            Node* node = root;
            while (node->right) {
                node = node->right;
            }
            return reverse_iterator(node, root);
        }

        const_reverse_iterator rend() const {
            Node* node = root;
            while (node->right) {
                node = node->right;
            }
            return const_reverse_iterator(node, root);
        }

        size_t getSize() { return size; }

        void swap(RBTree& other) { std::swap(root, other.root); }

    private:

        bool isLeftChild(Node *node) { return node->parent && node == node->parent->left; }

        bool isRightChild(Node *node) { return node->parent && node == node->parent->right; }

        bool isRed(Node* node) { return node && node->_is_red; }

        Node* findNode(value_type value) {
            Node* node = root;
            while (node) {
                if (_comp(node->_value, value)) {
                    node = node->_right;
                }
                else if (value, _comp(node->_value)) {
                    node = node->_left;
                }
                else {
                    return node;
                }
            }
            return NULL;
        }

        void leftRotate(Node* node) {

            if (!node->right)
                return;
            Node* tmp = node->right->left;
            node->right->parent = node->parent;
            node->right->left = node;
            node->parent = node->right;
            node->right = tmp;
        }

        void rightRotate(Node* node) {

            if (!node->left)
                return;
            Node* tmp = node->left->right;
            node->left->parent = node->parent;
            node->left->right = node;
            node->parent = node->left;
            node->left = tmp;
        }

        void balanceInsert(Node* node) {

            node->isRed = node != root;
            while (node != root && node->parent->isRed) {
                if (isLeftChild(node->parent)) {
                    Node* nodeToCheck = node->parent->parent->right;
                    if (nodeToCheck && nodeToCheck->isRed) {
                        node = node->parent;
                        node->isRed = false;
                        node = node->parent;
                        node->isRed = node != root;
                        nodeToCheck->isRed = false;
                    }
                    else {
                        if (!isLeftChild(node->parent)) {
                            node = node->parent;
                            leftRotate(node);
                        }
                        node = node->parent;
                        node->isRed = false;
                        node = node->parent;
                        node->isRed = true;
                        rightRotate(node);
                        break;
                    }
                }
                else {
                    Node* nodeToCheck = node->parent->parent->left;
                    if (nodeToCheck && nodeToCheck->isRed) {
                        node = node->parent;
                        node->isRed = false;
                        node = node->parent;
                        node->isRed = node != root;
                        nodeToCheck->isRed = false;
                    }
                    else {
                        if (isLeftChild(node)) {
                            node = node->parent;
                            rightRotate(node);
                        }
                        node = node->parent;
                        node->isRed = false;
                        node = node->parent;
                        node->isRed = true;
                        leftRotate(node);
                        break;
                    }
                }
                if (!node->parent) {
                    root = node;
                }
            }
        }

        void clear(Node* node) {

            if (!node)
                return;
            clear(node->left);
            clear(node->right);
            removeNode(node);
        }

        void balanceLeftErase(Node* nodeParent) {

            if (!nodeParent) {
                return;
            }
            if (isRed(nodeParent->right)) {
                nodeParent->right->isRed = false;
                nodeParent->isRed = true;
                leftRotate(nodeParent);
                nodeParent = nodeParent->parent;
            }
            if (nodeParent->right && !isRed(nodeParent->right) && !isRed(nodeParent->left)) {
                bool isParentRed = nodeParent->isRed;
                nodeParent->right->isRed = true;
                nodeParent->isRed = false;
                if (isParentRed) {
                    balanceInsert(nodeParent);
                }
            }
            if (nodeParent->right && isRed(nodeParent->right->left)) {
                std::swap(nodeParent->right->isRed, nodeParent->right->left->isRed);
                rightRotate(nodeParent->right);
            }
            if (nodeParent->right && isRed(nodeParent->right->right)) {
                nodeParent->right->isRed = nodeParent->isRed;
                nodeParent->right->right->isRed = false;
                nodeParent->isRed = false;
                rightRotate(nodeParent);
            }
        }

        void balanceRightErase(Node* nodeParent) {

            if (!nodeParent) {
                return;
            }
            if (isRed(nodeParent->left)) {
                nodeParent->left->isRed = false;
                nodeParent->isRed = true;
                rightRotate(nodeParent);
                nodeParent = nodeParent->parent;
            }
            if (nodeParent->left && !isRed(nodeParent->left) && !isRed(nodeParent->right)) {
                bool isParentRed = nodeParent->isRed;
                nodeParent->left->isRed = true;
                nodeParent->isRed = false;
                if (isParentRed) {
                    balanceInsert(nodeParent);
                }
            }
            if (nodeParent->left && isRed(nodeParent->left->right)) {
                std::swap(nodeParent->left->isRed, nodeParent->left->right->isRed);
                leftRotate(nodeParent->left);
            }
            if (nodeParent->left && isRed(nodeParent->left->left)) {
                nodeParent->left->isRed = nodeParent->isRed;
                nodeParent->left->left->isRed = false;
                nodeParent->isRed = false;
                leftRotate(nodeParent);
            }
        }

    };





}