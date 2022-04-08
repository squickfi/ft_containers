#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <type_traits>
#include <algorithm>
#include "Vector.hpp"

using std::cout;
using std::endl;

template <class T>
void printVector(std::vector<T> &vec) {

	cout << "std::vector: ";
	typename std::vector<T>::iterator it_begin = vec.begin();
	typename std::vector<T>::iterator it_end = vec.end();
	for (; it_begin != it_end; ++it_begin)
		cout << *it_begin << " ";
	cout << "size = " << vec.size() << " capacity = " << vec.capacity() << endl;
}

template <class T>
void printVector(ft::Vector<T> &vec) {

	cout << "ft::vector: ";
	typename ft::Vector<T>::iterator it_begin = vec.begin();
	typename ft::Vector<T>::iterator it_end = vec.end();
	for (; it_begin != it_end; ++it_begin)
		cout << *it_begin << " ";
	cout << "size = " << vec.size() << " capacity = " << vec.capacity() << endl;
}

void insertTest();

void reverseIteratorTest();

void eraseTest();