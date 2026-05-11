#include <iostream>
#include <chrono>
#include <thread>

int main() {
    auto start = std::chrono::steady_clock::now();

    // Симуляция работы
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Прошло времени: " << duration.count() << " мс" << std::endl;

    return 0;
}
