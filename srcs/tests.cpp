#include "test_utils.hpp"

int main() {

	{ //copy constructor

	cout << "COPY CONSTRUCTOR" << endl << endl;
	std::vector<int> vec;
	vec.push_back(7);
	vec.push_back(7);
	vec.push_back(7);
	std::vector<int> vec2(vec);

	cout << "Copied." << endl;
	cout << "vector1 capasity: " << vec.capacity() << endl;
	cout << "vector2 capasity: " << vec2.capacity() << endl;
	cout << endl;

	printVector(vec);
	printVector(vec2);

	cout << endl;
	
	}

	{ //operator =

	cout << "OPERATOR =" << endl << endl;
	std::vector<int> vec;
	vec.push_back(7);
	vec.push_back(7);
	vec.push_back(7);
	std::vector<int> vec2;
	vec2 = vec;

	cout << " =" << endl;
	cout << "vector1 capasity: " << vec.capacity() << endl;
	cout << "vector2 capasity: " << vec2.capacity() << endl;
	cout << endl;

	printVector(vec);
	printVector(vec2);

	cout << endl;

	}

	{ //at
	
	cout << "AT" << endl << endl;

	std::vector<int> vec;
	vec.push_back(7);
	vec.push_back(7);
	vec.push_back(7);
	try {
		for (int i = 0; i < 10; ++i)
			cout << vec.at(i) << " ";
		cout << endl;
	}
	catch (const std::exception& e) {
		std::cerr << endl << e.what() << endl;
	}
	cout << endl;

	}

	{ //clear
	
	cout << "CLEAR" << endl << endl;

	std::vector<int> vec;
	vec.push_back(7);
	vec.push_back(7);
	vec.push_back(7);
	vec.push_back(7);
	vec.push_back(7);
	cout << "size = " << vec.size() << ", capacity = " << vec.capacity() << endl;
	vec.clear();
	cout << "clear" << endl;
	cout << "size = " << vec.size() << ", capacity = " << vec.capacity() << endl;
	cout << endl;

	}

	{ //insert
	
	// cout << "INSERT" << endl << endl;

	// std::vector<int> vec;
	// vec.push_back(7);
	// vec.push_back(7);
	// vec.push_back(7);
	// vec.push_back(7);

	// printVector(vec);
	
	// vec.insert(vec.begin(), 1);
	// vec.insert(vec.begin() + 2, 2);
	// cout << "insert" << endl;

	// printVector(vec);

	// vec.insert(vec.begin() + 2, 10, 2);
	// cout << "insert" << endl;

	// printVector(vec);

	// cout << endl;

	// insertTest();

	}

	{ //iterator
	
	cout << "ITERATORS" << endl << endl;

	std::vector<int> vec;
	vec.push_back(0);
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);

	printVector(vec);
	
	std::vector<int>::iterator it = vec.begin();
	cout << "begin: " << *it << endl;
	it += 2;
	cout << "begin += 2: " << *it << endl;
	it += 8;
	cout << "begin += 8: " << *it << endl;
	it -= 8;
	cout << "begin -= 8: " << *it << endl;

	cout << endl;

	}

	{ //FT

	cout << "FT_VECTOR" << endl << endl;
	ft::Vector<int> vec(20, 1);

	cout << "vector: ";
	for (ft::Vector<int>::size_type i = 0; i < vec.size(); ++i)
		cout << vec[i] << " ";
	cout << " size = " << vec.size() << " capacity = " << vec.capacity() << endl;

	vec.push_back(3);
	cout << "push_back" << endl;

	cout << "vector: ";
	for (ft::Vector<int>::size_type i = 0; i < vec.size(); ++i)
		cout << vec[i] << " ";
	cout << " size = " << vec.size() << " capacity = " << vec.capacity() << endl;

	ft::Vector<int>::iterator it = vec.begin() + 2;
	// vec.insert(it, 83);
	// it += 5;
	// vec.insert(it, 3, 19);
	// it += 5;
	// vec.insert(it, 16, 11);

	ft::Vector<int> vec2;
	for (int i = 100; i < 150; ++i)
		vec2.push_back(i);
	// for (int i = 0; i < vec2.size(); ++i)
	// 	cout << vec2[i] << " ";

	vec.clear();
	for (int i = 0; i < 41; ++i)
		vec.push_back(i);

	it = vec.begin() + 25;

	cout << "vector: ";
	for (ft::Vector<int>::size_type i = 0; i < vec.size(); ++i)
		cout << vec[i] << " ";
	cout << " size = " << vec.size() << " capacity = " << vec.capacity() << endl;
	vec.insert(it, vec2.begin(), vec2.end());

	cout << "insert" << endl;

	cout << "vector: ";
	for (ft::Vector<int>::size_type i = 0; i < vec.size(); ++i)
		cout << vec[i] << " ";
	cout << " size = " << vec.size() << " capacity = " << vec.capacity() << endl;

	// it = vec.begin() + 30;
	// cout << *it << endl;
	vec.erase(vec.begin() + 30);
	vec.erase(vec.begin() + 30, vec.begin() + 50);
	vec.pop_back();
	vec.pop_back();
	vec.pop_back();

	std::cout << "!!!..........!!!" << std::endl;

	cout << "vector: ";
	for (ft::Vector<int>::size_type i = 0; i < vec.size(); ++i)
		cout << vec[i] << " ";
	cout << " size = " << vec.size() << " capacity = " << vec.capacity() << endl;

	cout << endl;

	}

	insertTest();
	
	return (0);
}