// #include "test_utils.hpp"

// #include "../system/system_methods.ipp"
// #include "__service.ipp"
#include <vector>
#include "Vector.hpp"
class B {
public:
	char *l;
	int i;
	B():l(nullptr), i(1) {};
	B(const int &ex) {
		this->i = ex;
		this->l = new char('a');
	};
	virtual ~B() {
		delete this->l;
		this->l = nullptr;
	};
};

class A : public B {
public:
	A():B(){};
	A(const B* ex){
		this->l = new char(*(ex->l));
		this->i = ex->i;
		if (ex->i == -1) throw "n";
	}
	~A() {
		delete this->l;
		this->l = nullptr;
	};
};
int _ratio = 10000;
template <typename T>
void insert_test_1(std::vector<T> vector) {
    std::vector<int> v;
    vector.assign(2600 * _ratio, 1);
    // g_start1 = timer();
    v.push_back(*(vector.insert(vector.end() - 800 * _ratio, 44)));
    // g_end1 = timer();
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    std::unique_ptr<B> k2(new B(3));
    std::unique_ptr<B> k3(new B(4));
    std::unique_ptr<B> k4(new B(-1));
    std::vector<A> vv;
    std::vector<B*> v1;

	// v.erase();

    v1.push_back(&(*k2));
    v1.push_back(&(*k3));
    v1.push_back(&(*k4));
    try { vv.insert(vv.begin(), v1.begin(), v1.end()); }
    catch (...) {
    	v.push_back(vv.size());
    	v.push_back(vv.capacity());
    }
	std::cout << "STD: \n";
	typename std::vector<T>::iterator it;
	for (it = v.begin(); it != v.end(); ++it) {
		std::cout << *it << " ";
	}
    // return v;
}

template <typename T>
void insert_test_1(ft::Vector<T> vector, int) {
    std::vector<int> v;
    vector.assign(2600 * _ratio, 1);
    // g_start2 = timer();
    v.push_back(*(vector.insert(vector.end() - 800 * _ratio, 44)));
    // g_end2 = timer();
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    std::unique_ptr<B> k2(new B(3));
    std::unique_ptr<B> k3(new B(4));
    std::unique_ptr<B> k4(new B(-1));
    ft::Vector<A> vv;
    ft::Vector<B*> v1;

    v1.push_back(&(*k2));
    v1.push_back(&(*k3));
    v1.push_back(&(*k4));
    try { vv.insert(vv.begin(), v1.begin(), v1.end()); }
    catch (...) {
    	v.push_back(vv.size());
    	v.push_back(vv.capacity());
    }
	std::cout << "FT: \n";
	typename ft::Vector<T>::iterator it;
	for (it = v.begin(); it != v.end(); ++it) {
		std::cout << *it << " ";
	}
    // return v;
}

// int main() {

//     exit(run_vector_unit_test<int>("insert(value)", insert_test_1, insert_test_1));
// }

// void insertTest() {

	// ft::Vector<int> ftVec;
	// std::vector<int> stdVec;

	// for (int i = 0; i < 8; ++i) {
	// 	ftVec.push_back(1);
	// 	stdVec.push_back(1);
	// }
	// // ftVec[20] = 1;
	// // stdVec[20] = 1;
	// cout << *ftVec.insert(ftVec.end(), 3);
	// cout << endl;
	// cout << *stdVec.insert(stdVec.end(), 3);
	// cout << endl;
	
	// cout << *ftVec.insert(ftVec.end(), 7);
	// cout << endl;
	// cout << *stdVec.insert(stdVec.end(), 7);
	// cout << endl;
	
	// printVector(ftVec);
	// printVector(stdVec);
// }