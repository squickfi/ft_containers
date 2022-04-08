#include "test_utils.hpp"

void insertTest() {

	cout << "INSERT TEST" << endl << endl;

	ft::Vector<int> ftVec;
	std::vector<int> stdVec;

	for (int i = 0; i < 8; ++i) {
		ftVec.push_back(1);
		stdVec.push_back(1);
	}
	// ftVec[20] = 1;
	// stdVec[20] = 1;
	cout << *ftVec.insert(ftVec.end(), 3);
	cout << endl;
	cout << *stdVec.insert(stdVec.end(), 3);
	cout << endl;
	
	cout << *ftVec.insert(ftVec.end(), 7);
	cout << endl;
	cout << *stdVec.insert(stdVec.end(), 7);
	cout << endl;
	
	printVector(ftVec);
	printVector(stdVec);
	cout << endl;
}
