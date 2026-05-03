// 1. Подключите заголовок <algorithm>
#include <algorithm>

// 2. Определите диапазон [first, last)
auto first = container.begin();
auto last = container.end();

// 3. Вызовите std::count
auto count = std::count(first, last, value);

// 4. Используйте результат
std::cout << "Количество вхождений: " << count << std::endl;
