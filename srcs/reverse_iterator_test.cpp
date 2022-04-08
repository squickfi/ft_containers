#include "test_utils.hpp"

void reverseIteratorTest() {

	cout << "REVERSE ITERATOR TEST" << endl << endl;

	std::vector<int> stdVec;
	ft::Vector<int> ftVec;

	for (int i = 0; i < 10; ++i) {
		stdVec.push_back(i + 1);
		ftVec.push_back(i + 1);
	}

	std::vector<int>::reverse_iterator stdRit = stdVec.rbegin();
	ft::Vector<int>::reverse_iterator ftRit = ftVec.rbegin();

	cout << "std reverse iterator: " << endl;
	for (; stdRit != stdVec.rend(); ++stdRit)
		cout << *stdRit << " ";
	cout << endl;

	cout << "ft reverse iterator: " << endl;
	for (int i = 0; ftRit != ftVec.rend() && i < 10; ++ftRit, ++i)
		cout << *ftRit << " ";
	cout << endl;
	cout << endl;
}
