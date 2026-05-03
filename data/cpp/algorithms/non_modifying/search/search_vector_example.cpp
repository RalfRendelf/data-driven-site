#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> pattern = {4, 5, 6};

    auto it = std::search(data.begin(), data.end(), pattern.begin(), pattern.end());

    if (it != data.end()) {
        std::cout << "Подпоследовательность найдена на позиции: "
                  << (it - data.begin()) << std::endl;
    } else {
        std::cout << "Подпоследовательность не найдена." << std::endl;
    }

    return 0;
}
