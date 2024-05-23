#include <iostream>

int suma(const int tab[], unsigned size) {
    int sum = 0;
    for (unsigned i = 0; i < size; ++i) {
        sum += tab[i];
    }
    return sum;
}


void suma(const int tab[], unsigned size, int* result) {
    *result = 0;
    for (unsigned i = 0; i < size; ++i) {
        *result += tab[i];
    }
}


void pisz(const int* tab, size_t size, std::ostream* out) {
    for (size_t i = 0; i < size; ++i) {
        *out << tab[i] << " ";
    }
    *out << std::endl;
}


void iota(int tab[], unsigned size) {
    for (unsigned i = 0; i < size; ++i) {
        tab[i] = i;
    }
}


void reverse(int* tab, size_t size) {
    for (size_t i = 0; i < size / 2; ++i) {
        int temp = tab[i];
        tab[i] = tab[size - 1 - i];
        tab[size - 1 - i] = temp;
    }
}


int dot_product(const int* tab1, const int* tab2, size_t size) {
    int product = 0;
    for (size_t i = 0; i < size; ++i) {
        product += tab1[i] * tab2[i];
    }
    return product;
}


int main() {

    int tab1[] = {1, 2, 3, 4, 5};
    std::cout << "Test suma: " << suma(tab1, 5) <<std::endl;

    int result;
    suma(tab1, 5, &result);
    std::cout << "Test suma (przez wskaźnik): " << result << std::endl;

    std::cout << "Test pisz: ";
    pisz(tab1, 5, &std::cout);

    iota(tab1, 5);
    std::cout << "Test iota: ";
    pisz(tab1, 5, &std::cout);

    reverse(tab1, 5);
    std::cout << "Test reverse: ";
    pisz(tab1, 5, &std::cout);

    int tab2[] = {1, 2, 3, 4, 5};
    std::cout << "Test dot_product: " << dot_product(tab1, tab2, 5) << std::endl;

    return 0;
}
