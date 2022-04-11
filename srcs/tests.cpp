#include "test_utils.hpp"

int main() {

	ft::pair<int, float> p1(7, 42.1f);
	ft::pair<int, float> p2(11, 21.3f);

	ft::pair<double, int> p3(5.3, -7);

	ft::pair<int, float> p4 = ft::make_pair(7, 0.2);

	cout << p3.first << " " << p3.second << endl;
	cout << p4.first << " " << p4.second << endl;

	std::less<ft::pair<int, float> > l;

	// std::map<int, int>::iterator

	cout << l(p2, p1) << endl;
}