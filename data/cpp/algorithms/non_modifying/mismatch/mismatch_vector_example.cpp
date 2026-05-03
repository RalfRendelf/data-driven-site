#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

int main() {
    std::vector<int> vec1 = {1, 2, 3, 4, 5};
    std::vector<int> vec2 = {1, 2, 8, 4, 5};

    auto mismatchPair = std::mismatch(vec1.begin(), vec1.end(), vec2.begin());

    if (mismatchPair.first != vec1.end()) {
        std::cout << "Первое несовпадение на позиции: "
                  << (mismatchPair.first - vec1.begin()) << std::endl;
        std::cout << "Элементы: " << *mismatchPair.first << " и "
                  << *mismatchPair.second << std::endl;
    } else {
        std::cout << "Все элементы совпадают." << std::endl;
    }

    return 0;
}
