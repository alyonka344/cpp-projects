#include <vector>
#include "Allocator.h"

int main() {
//    Allocator<int> allocator({{3, 4}, {1, 2}});
//    Allocator<bool> allocator1(allocator);
//
//
//    int* a = allocator.allocate(2);
//    int* b = allocator.allocate(1);
//
//    allocator.deallocate(a, 3);
//    int* c = allocator.allocate(3);
//    std::cout << a << '\n' << b << '\n'<< c;
    auto alloc = Allocator<int>({{2, 1000}});
    std::vector<int, Allocator<int>> vec(alloc);
    for (int i = 0; i < 10; ++i) {
        vec.push_back(i);
        for (int j: vec) {
            std::cout << j << ' ';
        }
        std::cout << '\n';
    }
}