// 1. Подключите заголовок <algorithm>
#include <algorithm>

// 2. Определите диапазоны
auto first1 = container.begin();
auto last1 = container.end();
auto first2 = pattern.begin();
auto last2 = pattern.end();

// 3. Вызовите std::search
auto it = std::search(first1, last1, first2, last2);

// 4. Проверьте результат
if (it != last1) {
    // Подпоследовательность найдена на позиции (it - first1)
} else {
    // Подпоследовательность не найдена
}

// Для поиска с предикатом:
auto itPred = std::search(first1, last1, first2, last2, predicate);
