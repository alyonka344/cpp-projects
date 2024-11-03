#include <lib/number.h>
#include <iostream>

int main() {
    uint32_t b = 57687856;
    std::string a = "55678797706867";
    std::string f = "45688879666376900890898";
    uint2022_t b1 = from_uint(b);
    uint2022_t a1 = from_string(&a[0]);
    uint2022_t f1 = from_string(&f[0]);
    uint2022_t k = a1*f1;
    std::cout << k;
    std::cout << std::endl << "2543901888397588493326269691752396566";
    return 0;

}
