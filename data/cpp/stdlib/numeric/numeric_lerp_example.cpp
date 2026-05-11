#include <iostream>
#include <numeric>

int main() {
    double a = 0.0;
    double b = 100.0;
    double t = 0.5; // Коэффициент интерполяции

    double result = std::lerp(a, b, t);
    std::cout << "Интерполяция между " << a << " и " << b << " с коэффициентом " << t << " = " << result << std::endl;

    return 0;
}
