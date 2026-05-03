#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> sorted = {1, 2, 3, 4, 5};
    std::vector<int> unsorted = {1, 3, 2, 4, 5};

    bool is_sorted1 = std::is_sorted(sorted.begin(), sorted.end());
    bool is_sorted2 = std::is_sorted(unsorted.begin(), unsorted.end());

    std::cout << "sorted отсортирован: " << (is_sorted1 ? "true" : "false") << std::endl;
    std::cout << "unsorted отсортирован: " << (is_sorted2 ? "true" : "false") << std::endl;

    return 0;
}
