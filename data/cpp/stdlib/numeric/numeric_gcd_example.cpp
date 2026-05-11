#include <iostream>
#include <numeric>

int main() {
    int a = 56;
    int b = 98;

    int gcd = std::gcd(a, b);
    std::cout << "НОД(" << a << ", " << b << ") = " << gcd << std::endl;

    return 0;
}
