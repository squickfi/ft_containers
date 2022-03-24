#include <iostream>
#include <vector>
#include <map>
#include <type_traits>
#include <algorithm>
#include "ft_vector.hpp"

int main() {

	{ //copy constructor

	std::cout << "COPY CONSTRUCTOR" << std::endl << std::endl;
	std::vector<int> vec;
	vec.push_back(7);
	vec.push_back(7);
	vec.push_back(7);
	std::vector<int> vec2(vec);
	std::vector<int>::iterator it_begin = vec.begin();
	std::vector<int>::iterator it_end = vec.end();
	std::vector<int>::iterator it_begin2 = vec2.begin();
	std::vector<int>::iterator it_end2 = vec2.end();

	std::cout << "Copied." << std::endl;
	std::cout << "vector1 capasity: " << vec.capacity() << std::endl;
	std::cout << "vector2 capasity: " << vec2.capacity() << std::endl;
	std::cout << std::endl;

	std::cout << "vector1: ";
	for (; it_begin != it_end; ++it_begin)
		std::cout << *it_begin << " ";
	std::cout << std::endl;

	std::cout << "vector2: ";
	for (; it_begin2 != it_end2; ++it_begin2)
		std::cout << *it_begin2 << " ";
	std::cout << std::endl;
	std::cout << std::endl;
	
	}

	{ //operator =

	std::cout << "OPERATOR =" << std::endl << std::endl;
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

	std::cout << " =" << std::endl;
	std::cout << "vector1 capasity: " << vec.capacity() << std::endl;
	std::cout << "vector2 capasity: " << vec2.capacity() << std::endl;
	std::cout << std::endl;

	std::cout << "vector1: ";
	for (; it_begin != it_end; ++it_begin)
		std::cout << *it_begin << " ";
	std::cout << std::endl;

	std::cout << "vector2: ";
	for (; it_begin2 != it_end2; ++it_begin2)
		std::cout << *it_begin2 << " ";
	std::cout << std::endl;
	std::cout << std::endl;

	}

	return (0);
}