#include "RBTree.hpp"
#include "ft_utility.hpp"

namespace ft {

	template <	class Key,
				class T,
				class Compare = std::less<Key>,
				class Allocator = std::allocator<ft::pair<const Key, T> >
	> class Map {

	public:

		typedef Key												key_type;
		typedef T												mapped_type;
		typedef ft::pair<const Key, T>							value_type;
		typedef std::size_t 									size_type;
        typedef std::ptrdiff_t                                  difference_type;
		typedef Compare											key_compare;
		typedef Allocator										allocator_type;
		typedef value_type&										reference;
		typedef const value_type&								const_reference;
		typedef typename Allocator::pointer						pointer;
		typedef typename Allocator::const_pointer				const_pointer;
		typedef RBTreeIterator<ft::pair<const Key, T> >			iterator;
		typedef RBTreeIterator<ft::pair<const Key, const T> >	const_iterator; // TODO verify
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

		class value_compare : std::binary_function<value_type, value_type, bool> {
			friend class Map<key_type, value_type, key_compare, Allocator>;

		protected:
			Compare comp;
			value_compare(Compare c) : comp(c) {}

		public:
			bool operator() (const value_type& x, const value_type& y) const {
				return (comp(x.first, y.first));
			}
		};

	private:

		RBTree<ft::pair<const Key, T> > tree;

	public:

		/***     ****     ****
		** member functions **
		****     ****     ***/

		// constructors
		// destructors
		// operator =
		// get_allocator

		Map() {}

		explicit Map(const Compare& comp,
					  const Allocator& alloc = Allocator()) {}

		template <class InputIt>
		Map(InputIt first, InputIt last,
			const Compare& comp = Compare(),
			const Allocator& alloc = Allocator()) {

			for (; first != last; ++first) {
				tree.insertNode(*first);
			}
		}

		Map(const Map& other) : tree(other.tree) {}

		~Map() {}

		Map& operator = (const Map& other) { tree = other.tree; }

		allocator_type get_allocator() const { return allocator_type(); }

        /***	****	****
        ** element access **
        ****	****	***/

        // at
        // operator[]

        T& at(const Key& key) { // TODO

		}

		const T& at(const Key& key) const { // TODO

		}

		T& operator[](const Key& key) { // TODO

		}

        /***  ***  ****
        ** iterators **
        ****  ***  ***/

        // begin
        // end
        // rbegin
        // rend

        iterator begin() { return tree.begin(); }
        const_iterator begin() const { return tree.begin(); }
        iterator end() { return tree.end(); }
        const_iterator end() const { return tree.end(); }
        reverse_iterator rbegin() { return tree.rbegin(); }
        const_reverse_iterator rbegin() const { return tree.rbegin(); }
        reverse_iterator rend() { return tree.rend(); }
        const_reverse_iterator rend() const { return tree.rend(); }

        /***  **  ****
        ** capacity **
        ****  **  ***/

        // empty
        // size
        // max_size

        bool empty() const { return !tree.getSize(); }
        size_type size() const { return tree.getSize(); }
        size_type max_size() const { return std::numeric_limits<difference_type>::max(); }

        /***  ***  ****
        ** modifiers **
        ****  ***  ***/

        // clear
        // insert
        // erase
        // swap

        void clear() { tree.clear(); }

        ft::pair<iterator, bool> insert(const value_type& value) {
            return tree.insert(value_type(value));
        }

        iterator insert(iterator hint, const value_type& value) {
            return tree.insert(value_type(value)).first;
        }

        template<class InputIt>
        void insert(InputIt first, InputIt last) {
            for (; first != last; ++first) {
                tree.insertNode(value_type(*first));
            }
        }

        iterator erase(iterator pos) {
            return tree.erase(pos);
        }

        iterator erase(iterator first, iterator last) {
            iterator toReturn;
            for (; first != last; ++first) {
                toReturn = tree.erase(first);
            }
            return toReturn;
        }

        size_type erase(const Key& key) {
            return tree.eraseNode(ft::make_pair<Key, T>(key, T())) ? 1: 0;
        }

        void swap(Map& other) {
            tree.swap(other.tree);
        }

    };
}