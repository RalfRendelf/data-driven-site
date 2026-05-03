#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec1 = {1, 2, 3, 4, 5};
    std::vector<int> vec2 = {1, 2, 3, 4, 5};
    std::vector<int> vec3 = {1, 2, 3, 4, 6};

    // Проверка равенства vec1 и vec2
    bool isEqual1 = std::equal(vec1.begin(), vec1.end(), vec2.begin());
    std::cout << "vec1 == vec2: " << (isEqual1 ? "true" : "false") << std::endl;

    // Проверка равенства vec1 и vec3
    bool isEqual2 = std::equal(vec1.begin(), vec1.end(), vec3.begin());
    std::cout << "vec1 == vec3: " << (isEqual2 ? "true" : "false") << std::endl;

    return 0;
}
