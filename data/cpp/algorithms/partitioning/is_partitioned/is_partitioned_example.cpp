#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers1 = {2, 4, 6, 8, 1, 3, 5, 7, 9}; // Разделён
    std::vector<int> numbers2 = {1, 2, 3, 4, 5, 6, 7, 8, 9}; // Не разделён

    bool isPartitioned1 = std::is_partitioned(numbers1.begin(), numbers1.end(),
                                            [](int x) { return x % 2 == 0; });
    bool isPartitioned2 = std::is_partitioned(numbers2.begin(), numbers2.end(),
                                            [](int x) { return x % 2 == 0; });

    std::cout << "numbers1 разделён: " << (isPartitioned1 ? "true" : "false") << std::endl;
    std::cout << "numbers2 разделён: " << (isPartitioned2 ? "true" : "false") << std::endl;

    return 0;
}
