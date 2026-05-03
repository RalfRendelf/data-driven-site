#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 2, 3, 2, 4, 2, 5};
    int target = 2;

    // Подсчёт количества вхождений числа 2
    int count = std::count(numbers.begin(), numbers.end(), target);

    std::cout << "Число " << target << " встречается " << count << " раз(а)." << std::endl;

    return 0;
}
