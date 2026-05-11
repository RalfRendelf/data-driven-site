#include <iostream>
#include <numeric>

int main() {
    int a = 10;
    int b = 20;

    int mid = std::midpoint(a, b);
    std::cout << "Середина между " << a << " и " << b << " = " << mid << std::endl;

    return 0;
}
