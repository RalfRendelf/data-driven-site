// 1. Подключите заголовок <algorithm>
#include <algorithm>

// 2. Определите диапазоны
auto first1 = container1.begin();
auto last1 = container1.end();
auto first2 = container2.begin();

// 3. Вызовите std::mismatch
auto mismatchPair = std::mismatch(first1, last1, first2);

// 4. Проверьте результат
if (mismatchPair.first != last1) {
    // Найдено несовпадение
    auto pos = mismatchPair.first - first1;
    // *mismatchPair.first - элемент из первого диапазона
    // *mismatchPair.second - элемент из второго диапазона
} else {
    // Все элементы совпадают
}

// Для сравнения с предикатом:
auto mismatchPred = std::mismatch(first1, last1, first2, predicate);
