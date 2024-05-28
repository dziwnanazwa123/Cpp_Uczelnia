#include <iostream>
#include <vector>
#include <stdexcept>

double operator*(const std::vector<double>& v, const std::vector<double>& w) {
    if (v.size() != w.size()) {
        throw std::invalid_argument("Wektory muszą mieć tę samą liczbę współrzędnych.");
    }
    double dot_product = 0.0;
    for (size_t i = 0; i < v.size(); ++i) {
        dot_product += v[i] * w[i];
    }
    return dot_product;
}

int main() {
    std::vector<double> v = {1.0, 2.0, 3.0};
    std::vector<double> w = {4.0, 5.0, 6.0};
    try {
        double result = v * w;
        std::cout << "Iloczyn skalarny v i w: " << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Błąd: " << e.what() << std::endl;
    }
    return 0;
}
