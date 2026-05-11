#include <iostream>
#include <chrono>

int main() {
    // Начало измерения
    auto start = std::chrono::high_resolution_clock::now();

    // Симуляция работы
    for (int i = 0; i < 1000000; ++i) {
        // Некоторая работа
    }

    // Конец измерения
    auto end = std::chrono::high_resolution_clock::now();

    // Вычисление длительности
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Время выполнения: " << duration.count() << " мс" << std::endl;

    return 0;
}
