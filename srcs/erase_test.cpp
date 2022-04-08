#include "test_utils.hpp"

void eraseTest() {

	cout << "ERASE TEST" << endl << endl;

	std::vector<int> stdVec;
	ft::Vector<int> ftVec;

	for (int i = 0; i < 10; ++i) {
		stdVec.push_back(i + 1);
		ftVec.push_back(i + 1);
	}

	std::vector<int>::iterator stdIt1 = stdVec.begin() + 2;
	std::vector<int>::iterator stdIt2 = stdVec.end() - 2;
	ft::Vector<int>::iterator ftIt1 = ftVec.begin() + 2;
	ft::Vector<int>::iterator ftIt2 = ftVec.end() - 2;

	stdVec.erase(stdIt1, stdIt2);
	ftVec.erase(ftIt1, ftIt2);

	printVector(stdVec);
	printVector(ftVec);
	cout << endl;
}
