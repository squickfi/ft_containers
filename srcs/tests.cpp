#include "test_utils.hpp"

int main() {

	ft::Map<int, int> map;
    for (int i = 0; i < 7; ++i) {
        map.insert(ft::make_pair(i + 1, i * 7));

        for (auto i = map.begin(); i != map.end(); ++i) {
            cout << " " << map.at(i->first) << " ";
        }
    }

    cout << endl;

	ft::Map<int, int> map2 = map;

    auto it = map2.begin();
    it++;
    cout << it->second << "!!!!!......!!!!!" << endl;
//    it++;
//    it++;
    map2.erase(it);
    cout << "!!!!!!!!!!!!!!" << endl;

    for (auto i = map2.begin(); i != map2.end(); ++i) {
        cout << "Hi " << i->second << " ";
    }

    cout << endl;
}