#pragma once

#include <iostream>
#include <vector>
#include "Vector.hpp"
#include <map>
#include <stack>
#include "Stack.hpp"
#include <type_traits>
#include <algorithm>
#include <typeinfo>

using std::cout;
using std::endl;

#define _vector ft::Vector<T>

template <class T, class ContainerWithInputIt = std::vector<T> >
class VectorTest {

	private:

		T	_value;
		int	numberOfTests = 5;

		void printVector(std::vector<T> &vec)
		{
			cout << "std::vector: ";
			typename std::vector<T>::iterator it_begin = vec.begin();
			typename std::vector<T>::iterator it_end = vec.end();
			for (; it_begin != it_end; ++it_begin)
				cout << *it_begin << " ";
			cout << "; size = " << vec.size() << " capacity = " << vec.capacity() << endl;
		}

		void printVector(_vector &vec)
		{
			cout << "ft::vector:  ";
			typename _vector::iterator it_begin = vec.begin();
			typename _vector::iterator it_end = vec.end();
			for (; it_begin != it_end; ++it_begin)
				cout << *it_begin << " ";
			cout << "; size = " << vec.size() << " capacity = " << vec.capacity() << endl;
		}

		void printBoth(std::vector<T> v, _vector vv)
		{
			printVector(v);
			printVector(vv);
			cout << endl;
		}

		void printTestName(const char* str)
		{
			cout << str << " TEST" << endl << endl;
		}

		void printDone()
		{
			cout << "Done." << endl << endl;
		}

	public:

		VectorTest(T value) : _value(value) { cout << "Object for testing vector is ready! Good luck c:" << endl << endl; }
		~VectorTest() { cout << "Testing of vector is done." << endl; }

		/*void chooseTest(std::string str) ?? TO DO: how it works?
		{
			std::string lowercase[] =
			{
				"default constructor",
				"constructor with values",
				"constructor with iterators",
				"copy constructor",
				"copy assigment operator"
			};

			std::string uppercase[] = 
			{
				"DEFAULT CONSTRUCTOR",
				"CONSTRUCTOR WITH VALUES",
				"CONSTRUCTOR WITH ITERATORS",
				"COPY CONSTRUCTOR",
				"COPY ASSIGMENT OPERATOR"
			};

			void (*testFoo[])() =
			{
				&VectorTest::defaultConstructorTest,
				&VectorTest::constructorWithValueTest,
				&VectorTest::constructorWithIterators,
				&VectorTest::copyConstrucorTest,
				&VectorTest::copyAssigmentOperatorTest
			};

			if (str == "")
			{
				for (int i = 0; i < numberOfTests; ++i)
					(this->*testFoo[i])();
				return;
			}

		}*/

		void defaultConstructorTest()
		{
			printTestName("DEFAULT CONSTRUCTOR");
			std::vector<T> v;
			_vector vv;
			printDone();
		}

		void constructorWithValueTest()
		{
			printTestName("CONSTRUCTOR WITH VALUES");
			cout << "vector(20):" << endl;
			std::vector<T> v1(10);
			_vector vv1(10);
			printBoth(v1, vv1);
			cout << "vector(20, _value):" << endl;
			std::vector<T> v2(10, _value);
			_vector vv2(10, _value);
			printBoth(v2, vv2);
			printDone();
		}

		void constructorWithIterators()
		{
			printTestName("CONSTRUCTOR WITH ITERATORS");
			cout << "begin() and end() from ContainerWithInputIt<T> (default std::vector<T>) with 10 values from default to default + 10" << endl;
			ContainerWithInputIt obj;
			T* value = new T;
			for (int count = 0; count < 10; ++count, ++(*value))
				obj.push_back(*value);
			std::vector<T> v(obj.begin(), obj.end());
			_vector vv(obj.begin(), obj.end());
			printBoth(v, vv);

			delete value;
			printDone();
		}

		void copyConstrucorTest()
		{
			printTestName("COPY CONSTRUCOR");

			cout << "vector(vector(10, 1))" << endl;
			std::vector<T> v1(10, _value);
			_vector vv1(10, _value);
			std::vector<T> v2(v1);
			_vector vv2(vv1);
			printBoth(v2, vv2);

			std::vector<T> v3;
			_vector vv3;
			for (int i = 0; i < 3; ++i)
			{
				v3.push_back(_value + i);
				vv3.push_back(_value + i);
			}
			cout << "vector(vector with size == " << vv3.size() << ", capacity == " << vv3.capacity() << ")" << endl;
			std::vector<T> v4;
			_vector vv4;
			v4 = v3;
			vv4 = vv3;
			printBoth(v4, vv4);
			printDone();
		}

		void copyAssigmentOperatorTest()
		{
			printTestName("COPY ASSIGMENT OPERATOR");

			cout << "empty vector = vector(10, 1)" << endl;
			std::vector<T> v1(10, _value);
			_vector vv1(10, _value);
			std::vector<T> v2(v1);
			_vector vv2(vv1);
			printBoth(v2, vv2);

			std::vector<T> v3;
			_vector vv3;
			for (int i = 0; i < 3; ++i)
			{
				v3.push_back(_value + i);
				vv3.push_back(_value + i);
			}
			cout << "empty vector = vector with size == " << vv3.size() << ", capacity == " << vv3.capacity() << endl;
			std::vector<T> v4;
			_vector vv4;
			v4 = v3;
			vv4 = vv3;
			printBoth(v4, vv4);

			std::vector<T> v5(10, _value);
			_vector vv5(10, _value);
			cout << "vector(10, value) = vector with size == " << vv3.size() << ", capacity == " << vv3.capacity() << endl;
			v5 = v3;
			vv5 = vv3;
			printBoth(v5, vv5);

			printDone();
		}

		void assignWithCountAndValuesTest()
		{
			printTestName("ASSIGN WITH COUNT AND VALUE");

			cout << "empty vector.assign(0, value)" << endl;
			std::vector<T> v1;
			_vector vv1;
			v1.assign(0, _value);
			vv1.assign(0, _value);
			printBoth(v1, vv1);

			cout << "vector(10, value).assign(0, value)" << endl;
			std::vector<T> v2(10, _value);
			_vector vv2(10, _value);
			v2.assign(0, _value);
			vv2.assign(0, _value);
			printBoth(v2, vv2);

			std::vector<T> v3;
			_vector vv3;
			for (int i = 0; i < 3; ++i)
			{
				v3.push_back(_value + i);
				vv3.push_back(_value + i);
			}
			cout << "vector(with size == " << vv3.size() << ", capacity == " << vv3.capacity() << ").assign(0, value)" << endl;
			v3.assign(0, _value);
			vv3.assign(0, _value);
			printBoth(v3, vv3);

			std::vector<T> v4;
			_vector vv4;
			for (int i = 0; i < 3; ++i)
			{
				v4.push_back(_value + i);
				vv4.push_back(_value + i);
			}
			cout << "vector(with size == " << vv4.size() << ", capacity == " << vv4.capacity() << ").assign(10, value)" << endl;
			v4.assign(10, _value);
			vv4.assign(10, _value);
			printBoth(v4, vv4);

			std::vector<T> v5;
			_vector vv5;
			for (int i = 0; i < 3; ++i)
			{
				v5.push_back(_value + i);
				vv5.push_back(_value + i);
			}
			cout << "vector(with size == " << vv5.size() << ", capacity == " << vv5.capacity() << ").assign(-10, value)" << endl;
			try
			{
				v5.assign(-10, _value);
			}
			catch (const std::exception& e)
			{
				cout << "Exception! right :3 \"" << e.what() << "\"" << endl;
			}
			try
			{
				vv5.assign(-10, _value);
			}
			catch (const std::exception& e)
			{
				cout << "Exception! right :3 \"" << e.what() << "\"" << endl;
			}
			printBoth(v5, vv5);

			printDone();
		}

		void assignWithIteratorsTest()
		{
			printTestName("ASSIGN WITH ITERATORS");

			cout << "! test on begin() and end() from ContainerWithInputIt<T> (default std::vector<T>) with 8 values from default to default + 8" << endl << endl;
			ContainerWithInputIt obj;
			T* value = new T(_value);
			for (int count = 0; count < 8; ++count, ++(*value))
				obj.push_back(*value);

			cout << "empty vector.assign(begin(), end())" << endl;
			std::vector<T> v1;
			_vector vv1;
			v1.assign(obj.begin(), obj.end());
			vv1.assign(obj.begin(), obj.end());
			printBoth(v1, vv1);

			cout << "vector(10, value).assign(begin(), end()))" << endl;
			std::vector<T> v2(10, _value);
			_vector vv2(10, _value);
			v2.assign(obj.begin(), obj.end());
			vv2.assign(obj.begin(), obj.end());
			printBoth(v2, vv2);
			
			delete value;
			printDone();
		}

		void getAlloacatorTest()
		{
			printTestName("GET ALOOCATOR");
			cout << "TO DO: idk" << endl;
			printDone();
		}

		void atTest()
		{
			printTestName("AT");

			cout << "! test on vector(10, value)" << endl << endl;
			std::vector<T> v(10, _value);
			_vector vv(10, _value);
			cout << "std::vector.at(7): " << v.at(7) << endl;
			cout << "ft::vector.at(7):  " << vv.at(7) << endl << endl;

			cout << "std::vector.at(-7): " << endl;
			try
			{
				cout << v.at(-7) << endl;
			}
			catch(const std::exception& e)
			{
				cout << "Exception! right :3 \"" << e.what() << "\"" << endl;
			}
			try
			{
				cout << vv.at(-7) << endl;
			}
			catch(const std::exception& e)
			{
				cout << "Exception! right :3 \"" << e.what() << "\"" << endl << endl;
			}

			cout << "std::vector.at(vector.size()): " << endl;
			try
			{
				cout << v.at(v.size()) << endl;
			}
			catch(const std::exception& e)
			{
				cout << "Exception! right :3 \"" << e.what() << "\"" << endl;
			}
			try
			{
				cout << vv.at(vv.size()) << endl;
			}
			catch(const std::exception& e)
			{
				cout << "Exception! right :3 \"" << e.what() << "\"" << endl << endl;
			}

			printDone();
		}

		void squiareBracketstest()
		{
			printTestName("SQUARE BRACKETS");

			cout << "! test on vector(10, value), the test will print all elements" << endl;
			cout << "! out of range values shall cause an ERROR while assignment, you can uncomment lines in the test's code to make sure" << endl << endl;
			std::vector<T> v(10, _value);
			_vector vv(10, _value);

			for (typename std::vector<T>::size_type i = 0; i < v.size(); ++i)
				cout << v[i] << " ";
			cout << endl;

			for (typename _vector::size_type i = 0; i < vv.size(); ++i)
				cout << vv[i] << " ";
			cout << endl;
			cout << endl;

			// it is incorrect, it shall cause an ERROR
			// v[-2] = _value;
			// vv[-2] = _value;
			// v[2000] = _value;
			// vv[2000] = _value;

			printDone();
		}

		void frontTest()
		{
			printTestName("FRONT");

			cout << "vector(10, value)" << endl;
			std::vector<T> v1(10, _value);
			_vector vv1(10, _value);
			cout << "std::vector.fornt(): " << v1.front() << endl;
			cout << "ft::vector.fornt():  " << vv1.front() << endl;
			cout << endl;

			cout << "testing on empty vector shall cause an ERROR (probably SEGFAULT), you can uncomment lines in the test's code to make sure" << endl;
			// std::vector<T> v2;
			// _vector vv2;
			// cout << v2.front() << endl;
			// cout << vv2.front() << endl;
			cout << endl;

			printDone();
		}

		void backTest()
		{
			printTestName("BACK");

			cout << "vector(10, value)" << endl;
			std::vector<T> v1(10, _value);
			_vector vv1(10, _value);
			cout << "std::vector.back(): " << v1.back() << endl;
			cout << "ft::vector.back():  " << vv1.back() << endl;
			cout << endl;

			cout << "testing on empty vector shall cause an ERROR (probably SEGFAULT), you can uncomment lines in the test's code to make sure" << endl;
			// std::vector<T> v2;
			// _vector vv2;
			// cout << v2.back() << endl;
			// cout << vv2.back() << endl;
			cout << endl;

			printDone();
		}

		void dataTest()
		{
			printTestName("DATA");

			cout << "emrty vector, result sould be NULL, if it is the test will print 0" << endl;
			std::vector<T> v1;
			_vector vv1;
			cout << "std: " << v1.data() << endl;
			cout << "ft:  " << vv1.data() << endl;
			cout << endl;

			cout << "vector(10, value), the test should print an adress of the poiner to vector's array\n"
					"\tadresses won't be same (but they will probably be close) - different objects are different objects! <3" << endl;
			std::vector<T> v2(10, _value);
			_vector vv2(10, _value);
			cout << "std: " << v2.data() << endl;
			cout << "ft:  " << vv2.data() << endl;
			cout << endl;

			printDone();
		}

};
