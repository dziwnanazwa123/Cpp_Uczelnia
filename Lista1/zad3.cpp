#include <iostream>

double down(int N) {
    double sum = 0.0;
    for (int i = 1; i <= N; ++i) {
        sum += 1.0 / i;
    }
    return sum;
}

double up(int N) {
    double sum = 0.0;
    for (int i = N; i>= 1; --i) {
        sum += 1.0 / i;
    }
    return sum;
}

int main() {
    int wartosci_N[] = {100, 100000, 100000000};

    for (int i = 0; i < 3; ++i) {
        int N = wartosci_N[i];
        double down_sum = down(N);
        double up_sum = up(N);
        double diff = up_sum - down_sum;
        std::cout << "N = " << N << ", down(N) = " << down_sum << ", up(N) = " << up_sum << ", różnica = " << diff << std::endl;
    }

    return 0;
}
