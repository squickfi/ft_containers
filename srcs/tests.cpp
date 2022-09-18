#include "test_utils.hpp"

int main() {

	std::map<int, int> map;

    for (int i = 0; i < 15; ++i) {
        map.insert(std::make_pair(i, i * 3));
    }

    std::map<int, int> map2;

    map2 = map;

    auto iter = map.begin();
    auto iter2 = map2.begin();

    iter->second = 7;
    cout << iter2->second << endl;

}