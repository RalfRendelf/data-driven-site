// 1. Подключите заголовок <algorithm>
#include <algorithm>

// 2. Определите диапазон [first, last)
auto first = container.begin();
auto last = container.end();

// 3. Вызовите std::find
auto it = std::find(first, last, value);

// 4. Проверьте результат
if (it != last) {
    // Элемент найден: *it — найденный элемент
    // (it - first) — индекс элемента
} else {
    // Элемент не найден
}
