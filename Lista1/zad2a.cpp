#include <iostream>
#include <cmath>
#include <iomanip>

double calculate_pi_a(int iterations) {
    double t = 1 / std::sqrt(3);
    for (int i = 0; i < iterations; ++i) {
        t = (std::sqrt(t * t + 1) - 1) / t;
    }
    double pi = 6 * std::pow(2, iterations) * t;
    double error = std::abs(M_PI - pi);
    return pi;
}

int main() {
    int iterations = 25; //od i=27 wynik to niezdefiniowana wartość

    for (int i = 0; i <= iterations; ++i) {
        double pi = calculate_pi_a(i);
        double error = std::abs(M_PI - pi);
        std::cout << "i = " << std::setw(2) << i << ", przybliżenie pi: " << std::fixed << std::setprecision(5) << pi << ", Error: " << error << std::endl;
    }

    return 0;
}
