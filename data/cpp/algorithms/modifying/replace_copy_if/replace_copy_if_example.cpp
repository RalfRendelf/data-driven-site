#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> source = {1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int> destination(source.size());

    // Копируем элементы, заменяя чётные числа на 0
    std::replace_copy_if(source.begin(), source.end(), destination.begin(),
                        [](int x) { return x % 2 == 0; }, 0);

    // Выводим результат
    for (int num : destination) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
