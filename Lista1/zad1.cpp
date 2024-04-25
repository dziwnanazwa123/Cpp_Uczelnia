#include <iostream>
#include <cmath>

using namespace std;

double a(int n) {
    double sum = 0.0;
    for (int j = 1; j <=n; ++j)
    {double terma = pow(-1, j + 1) / (2.0 * j - 1.0);
    sum += terma;
    }
    return 4 * sum;
}

double b(int n) {
    double product = 1.0;
    for (int j = 1; j <=n; ++j)
    {double termb = (4.0 * j * j) / (4.0 * j * j - 1.0);
    product *= termb;
    }
    return 2 * product;
}

double c(int n) {
    double sum = 0.0;
    for (int j = 1; j <= n; ++j)
    {double termc = 1.0 / pow(2 * j - 1, 2);
    sum += termc;
    }
    return sum;
}
double cpierwiastek(int n) {
    double sum = c(n);
    return sqrt(8 * sum);
}

int main() {
    int n = 1000000;
    double piApproximationa = a(n);
    double piApproximationb = b(n);
    double piApproximationc = cpierwiastek(n);
    double piValue = M_PI;

    cout << "Przyblizona wartosc pi (a): " << piApproximationa << endl;
    cout << "Przyblizona wartosc pi (b): " << piApproximationb << endl;
    cout << "Przyblizona wartosc pi (c): " << piApproximationc << endl;
    cout << "Wartosc pi z biblioteki cmath: " << piValue << endl;

    return 0;
}
