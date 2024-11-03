#include <iostream>
#include <algorithm>
#include <vector>
#include "Algorithms/Algorithms.h"
#include "Algorithms/xrange.h"
#include <vector>
#include <list>
#include "Algorithms/zip.h"

struct leastsix {
    template<typename T>
    bool operator()(T x) {
        if (x < 6) {
            return true;
        }
        return false;
    }
};

int main() {
    std::vector<int> a = {1, 8, 3, 9, 3, 8, 1};
    auto x = xrange(4);
    std::vector<int> v{x.begin(), x.end()};
//    std::sort(a.begin(), a.end(), std::greater<>());
    for (int i: v) {
        std::cout << i << ' ';
    }
    bool b = Algorithm::all_of(a.begin(), a.end(), leastsix());
//    std::cout << '\n' << b << '\n';
//
//    for (double i: xrange(1, 10, 2)) {
//        std::cout << i << ' ';
//    }

//    std::list<int> l = {1, 2, 3, 4, 5};
//    std::vector<char> v = {'a', 'b', 'c', 'd'};
//
//    for(auto value : zip(l, v)) {
//        std::cout << value.first << " " << value.second << std::endl;
//    }
}