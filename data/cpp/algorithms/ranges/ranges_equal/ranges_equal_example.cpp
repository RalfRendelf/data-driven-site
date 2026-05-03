#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

int main() {
    std::vector<int> a = {1, 2, 3, 4, 5};
    std::vector<int> b = {1, 2, 3, 4, 5};
    std::vector<int> c = {1, 2, 3, 5, 4};

    bool equal_ab = std::ranges::equal(a, b);
    bool equal_ac = std::ranges::equal(a, c);

    std::cout << "a == b: " << (equal_ab ? "true" : "false") << std::endl;
    std::cout << "a == c: " << (equal_ac ? "true" : "false") << std::endl;

    return 0;
}
