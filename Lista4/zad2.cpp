#include <iostream>
#include <cmath>
#include <stdexcept>
#include <functional>

double root(double (*f) (double), double a, double b, double tolerance = 1e-10) {
    if (f(a) * f(b) > 0) {
        throw std::invalid_argument("Funkcja musi zmieniać znak na końcach przedziału.");
    }
    double mid;
    while ((b - a) / 2 > tolerance) {
        mid = (a + b) / 2;
        if(f(mid) == 0.0) {
            return mid;
        }
        else if (f(a) * f(mid) < 0) {
            b = mid;
        }
        else {
            a = mid;
        }
    }
    return (a + b) / 2;
}

double func1(double x) {
    return cos(x) - x;
}
double func2(double x) {
    return cos(x) - 0.5;
}

int main() {
    try {
        double root1 = root(func1, 0, 2, 1e-10);
        std::cout << "Pierwiastek równania cos(x) = x w przediale [0, 2]: " << root1 << std::endl;
        double root2 = root(func2, 0, 1.5, 1e-10);
        std::cout << "Pierwiastek równania cos(x) = 1/2 w przediale [0, 1.5]: " << root2 << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Błąd: " << e.what() << std::endl;
    }
    return 0;
}
