#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> a = {1, 2, 3, 4};
    std::vector<int> b = {5, 6, 7, 8};
    std::vector<int> result(a.size());

    // Складываем элементы из a и b
    std::transform(a.begin(), a.end(), b.begin(), result.begin(),
                  [](int x, int y) { return x + y; });

    // Выводим результат
    for (int num : result) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
