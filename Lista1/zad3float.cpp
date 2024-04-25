#include <iostream>

float down_float(int N) {
    float sum = 0.0f;
    for (int i = 1; i <= N; ++i) {
        sum += 1.0f / i;
    }
    return sum;
}

float up_float(int N) {
    double sum = 0.0f;
    for (int i = N; i>= 1; --i) {
        sum += 1.0f / i;
    }
    return sum;
}

int main() {
    int wartosci_N[] = {100, 100000, 100000000};

    for (int i = 0; i < 3; ++i) {
        int N = wartosci_N[i];
        float down_sum = down_float(N);
        float up_sum = up_float(N);
        float diff = up_sum - down_sum;
        std::cout << "N = " << N << ", down(N) = " << down_sum << ", up(N) = " << up_sum << ", różnica = " << diff << std::endl;
    }

    return 0;
}
