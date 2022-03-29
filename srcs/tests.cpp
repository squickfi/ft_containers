#include <iostream>
#include <vector>
#include <map>
#include <type_traits>
#include <algorithm>
#include "ft_vector.hpp"

using std::cout;
using std::endl;

template <class T>
void printVector(std::vector<T> &vec) {

	cout << "vector: ";
	typename std::vector<T>::iterator it_begin = vec.begin();
	typename std::vector<T>::iterator it_end = vec.end();
	for (; it_begin != it_end; ++it_begin)
		cout << *it_begin << " ";
	cout << "size = " << vec.size() << " capacity = " << vec.capacity() << endl;
}

template <class T>
void printVector(std::vector<T> &vec, int i) {

	cout << "vector" << i << ": ";
	typename std::vector<T>::iterator it_begin = vec.begin();
	typename std::vector<T>::iterator it_end = vec.end();
	for (; it_begin != it_end; ++it_begin)
		cout << *it_begin << " ";
	cout << "size = " << vec.size() << " capacity = " << vec.capacity() << endl;
}

int main() {

	{ //copy constructor

	cout << "COPY CONSTRUCTOR" << endl << endl;
	std::vector<int> vec;
	vec.push_back(7);
	vec.push_back(7);
	vec.push_back(7);
	std::vector<int> vec2(vec);
	std::vector<int>::iterator it_begin = vec.begin();
	std::vector<int>::iterator it_end = vec.end();
	std::vector<int>::iterator it_begin2 = vec2.begin();
	std::vector<int>::iterator it_end2 = vec2.end();

	cout << "Copied." << endl;
	cout << "vector1 capasity: " << vec.capacity() << endl;
	cout << "vector2 capasity: " << vec2.capacity() << endl;
	cout << endl;

	printVector(vec, 1);
	printVector(vec2, 2);

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
	std::vector<int>::iterator it_begin = vec.begin();
	std::vector<int>::iterator it_end = vec.end();
	std::vector<int>::iterator it_begin2 = vec2.begin();
	std::vector<int>::iterator it_end2 = vec2.end();

	cout << " =" << endl;
	cout << "vector1 capasity: " << vec.capacity() << endl;
	cout << "vector2 capasity: " << vec2.capacity() << endl;
	cout << endl;

	printVector(vec, 1);
	printVector(vec2, 2);

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
	
	cout << "INSERT" << endl << endl;

	std::vector<int> vec;
	vec.push_back(7);
	vec.push_back(7);
	vec.push_back(7);
	vec.push_back(7);

	printVector(vec);
	
	vec.insert(vec.begin(), 1);
	vec.insert(vec.begin() + 2, 2);
	cout << "insert" << endl;

	printVector(vec);

	vec.insert(vec.begin() + 2, 10, 2);
	cout << "insert" << endl;

	printVector(vec);

	cout << endl;

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
	ft::vector<int> vec(20, 20);

	cout << "vector: ";
	for (int i = 0; i < vec.size(); ++i)
		cout << vec[i] << " ";
	cout << " size = " << vec.size() << " capacity = " << vec.capacity() << endl;

	vec.push_back(3);
	cout << "push_back" << endl;

	cout << "vector: ";
	for (int i = 0; i < vec.size(); ++i)
		cout << vec[i] << " ";
	cout << " size = " << vec.size() << " capacity = " << vec.capacity() << endl;

	ft::vector<int>::iterator it = vec.begin() + 2;
	vec.insert(it, 83);
	it += 5;
	vec.insert(it, 3, 19);
	it += 5;
	cout << *it << endl;
	cout << "vector: ";
	for (int i = 0; i < vec.size(); ++i)
		cout << vec[i] << " ";
	cout << " size = " << vec.size() << " capacity = " << vec.capacity() << endl;
	vec.insert(it, 16, 11);
	// cout << "insert" << endl;

	cout << "vector: ";
	for (int i = 0; i < vec.size(); ++i)
		cout << vec[i] << " ";
	cout << " size = " << vec.size() << " capacity = " << vec.capacity() << endl;

	cout << endl;

	}
	
	return (0);
}