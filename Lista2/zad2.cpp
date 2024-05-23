#include <cstdlib>
#include <iostream>

int compare(const void* a, const void* b) {
    int ia = *(const int*)a;
    int ib = *(const int*)b;

    bool ia_even = (ia % 2 == 0);
    bool ib_even = (ib % 2 == 0);

    if (ia_even && ib_even) {
        return (ia - ib);
    }
    else if (!ia_even && !ib_even) {
        return (ib - ia);
    } else {
        return (ia_even ? -1 : 1);
    }
}

int main() {
    int array[] = {1, 4, 7, 2, 5, 9, 2, 8};
    int n = sizeof(array) / sizeof(array[0]);
    std::qsort(array, n, sizeof(int), compare);
    std::cout << "Posortowana tablica: ";
    for (int i = 0; i < n; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
