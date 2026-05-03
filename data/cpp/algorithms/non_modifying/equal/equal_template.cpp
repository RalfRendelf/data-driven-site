// 1. Подключите заголовок <algorithm>
#include <algorithm>

// 2. Определите диапазоны
auto first1 = container1.begin();
auto last1 = container1.end();
auto first2 = container2.begin();

// 3. Вызовите std::equal
bool areEqual = std::equal(first1, last1, first2);

// 4. Используйте результат
if (areEqual) {
    // Диапазоны равны
} else {
    // Диапазоны не равны
}

// Для сравнения с предикатом:
bool areEqualPred = std::equal(first1, last1, first2, predicate);
