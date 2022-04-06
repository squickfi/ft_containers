#include "test_utils.hpp"

void insertTest() {

	ft::Vector<int> ftVec;
	std::vector<int> stdVec;

	for (int i = 0; i < 3; ++i) {
		ftVec.push_back(1);
		stdVec.push_back(1);
	}
	// ftVec[20] = 1;
	// stdVec[20] = 1;
	ftVec.insert(ftVec.begin(), 5, 3);
	stdVec.insert(stdVec.begin(), 5, 3);
	
	printVector(ftVec);
	printVector(stdVec);
}