#include "test_utils.hpp"

int main() {

	std::map<int, int> map;
	for (int i = 0; i < 10; ++i) {
		map.insert(std::make_pair(i, i * 10));
	}
	auto it = map.begin();

	ft::RBTree<int> tree;
	cout << "!!!" << endl;
	tree.insertNode(tree.getRoot(), 4);
	cout << "!!!" << endl;
	tree.insertNode(tree.getRoot(), 7);
	cout << "!!!" << endl;
	tree.insertNode(tree.getRoot(), 9);
	cout << "!!!" << endl;
	tree.insertNode(tree.getRoot(), 1);
	cout << "!!!" << endl;

	ft::RBTreeIterator<int> iter = tree.begin();
	tree.eraseNode(iter.getNode());
	iter = tree.begin();
	tree.eraseNode(iter.getNode());
	iter = tree.begin();
	cout << "..." << endl;
	++iter;
	--iter;
	cout << *iter << endl;
}