#include <iostream>
#include <numeric>

int main() {
    int a = 12;
    int b = 18;

    int lcm = std::lcm(a, b);
    std::cout << "НОК(" << a << ", " << b << ") = " << lcm << std::endl;

    return 0;
}
