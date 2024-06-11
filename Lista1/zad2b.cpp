#include <iostream>
#include <cmath>
#include <iomanip>

double calculate_pi_b(int iterations) {
    double t = 1 / std::sqrt(3);
    for (int i = 0; i < iterations; ++i) {
        t = t / (std::sqrt(t * t + 1) + 1);
    }
    double pi = 6 * std::pow(2, iterations) * t;
    double error = std::abs(M_PI - pi);
    return pi;
}

int main() {
    int iterations = 30;

    for (int i = 0; i <= iterations; ++i) {
        double pi = calculate_pi_b(i);
        double error = std::abs(M_PI - pi);
        std::cout << "i = " << std::setw(2) << i << ", przybliżenie pi: " << std::fixed << std::setprecision(5) << pi << ", Error: " << error << std::endl;
    }

    return 0;
}
