#include <iostream>
#include <chrono>

int main() {
    // Создание длительности в секундах
    std::chrono::seconds sec(60);

    // Преобразование в минуты
    std::chrono::minutes min = std::chrono::duration_cast<std::chrono::minutes>(sec);
    std::cout << "60 секунд = " << min.count() << " минут" << std::endl;

    // Преобразование в миллисекунды
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(sec);
    std::cout << "60 секунд = " << ms.count() << " миллисекунд" << std::endl;

    return 0;
}
