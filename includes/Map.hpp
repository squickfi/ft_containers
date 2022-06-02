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
		typedef std::pair<const Key, T>							value_type;
		typedef std::size_t 									size_type;
		typedef Compare											key_compare;
		typedef Allocator										allocator_type;
		typedef value_type&										reference;
		typedef const value_type&								const_reference;
		typedef typename Allocator::pointer						pointer;
		typedef typename Allocator::const_pointer				const_pointer;
		typedef RBTreeIterator<ft::pair<const Key, T> >			iterator;
		typedef RBTreeConstIterator<ft::pair<const Key, T> >	const_iterator;
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

		RBTree<ft::pair<const Key, T>, Compare, Allocator>	_tree;

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
				_tree.insertNode(_tree.getRoot(), *first);
			}
		}

		Map(const Map& other) : _tree(other._tree) {}

		~Map() {}

		Map& operator = (const Map& other) {
			_tree.clearTree(_tree.getRoot());
			RBTreeIterator<T> iter = other._tree.begin();
			for (; iter != other._tree.end(); ++ iter) {
				_tree.insertNode(_tree.getRoot(), *iter);
			}
		}

		allocator_type get_allocator() const {
			allocator_type alloc;
			return alloc;
		}

		// 	/***	****	****
		// 	** element access **
		// 	****	****	***/

		// 	// at
		// 	// operator[]

		T& at(const Key& key) {
			RBtreeNode<ft::pair<Key, T> > node = _tree.findNode(ft::make_pair(key, value_type()));
			if (node) {
				return _tree.findNode(ft::make_pair(key, value_type()))->_value.second;
			}
			else {
				_tree.clearTree(_tree.getRoot());
				throw "map"; // TODO normal throw
			}
		}

		const T& at(const Key& key) const { // TODO THIS
			RBtreeNode<ft::pair<Key, T> > node = _tree.findNode(ft::make_pair(key, value_type()));
			if (node) {
				return _tree.findNode(ft::make_pair(key, value_type()))->_value.second;
			} else {
				_tree.clearTree(_tree.getRoot());
				throw "map"; // TODO normal throw
			}
		}

		T& operator[](const Key& key) {
			return _tree.findNode(ft::make_pair(key, value_type()))->_value.second;
		}

	};
}