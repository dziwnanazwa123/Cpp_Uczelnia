#include <iostream>
#include <cmath>

using namespace std;

double a(int i) {
    double t = 1.0 / sqrt(3);
    double piApprox;

    for (int j = 0; j < i; ++j) {
        t = (sqrt(t * t * + 1.0) - 1.0) / t;
    }

    piApprox = 6 * pow(2, i) * t;
    return piApprox;
}

int main() {
    for (int i = 0; i <= 30; ++i) {
        double piApprox = a(i);
        cout << "i = " << i << ", przybliżenie pi: " << piApprox << ", Error: " << abs(M_PI - piApprox) << endl;
    }
    return 0;
}
