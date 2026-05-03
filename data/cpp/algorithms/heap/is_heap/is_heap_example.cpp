#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers1 = {9, 5, 6, 2, 3, 1, 4}; // Куча
    std::vector<int> numbers2 = {1, 2, 3, 4, 5, 6, 9}; // Не куча

    bool isHeap1 = std::is_heap(numbers1.begin(), numbers1.end());
    bool isHeap2 = std::is_heap(numbers2.begin(), numbers2.end());

    std::cout << "numbers1 является кучей: " << (isHeap1 ? "true" : "false") << std::endl;
    std::cout << "numbers2 является кучей: " << (isHeap2 ? "true" : "false") << std::endl;

    return 0;
}
