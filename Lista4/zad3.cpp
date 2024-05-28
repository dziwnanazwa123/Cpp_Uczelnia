#include <iostream>
#include <string>
#include <vector>

bool isHelpArgument(const std::string& arg) {
    return arg == "--help" || arg == "-h";
}

void optimalMove(const std::vector<int>& piles) {
    int nim_sum = 0;
    for (int stones : piles) {
        nim_sum ^= stones;
    }
    if (nim_sum == 0) {
        std::cout << "rób co chcesz, strategia wygrywająca nie istnieje" << std::endl;
    }
    else {
        for (size_t i = 0; i < piles.size(); ++i) {
            int stones_left = piles[i] ^ nim_sum;
            if (stones_left < piles[i]) {
                int stones_to_remove = piles[i] - stones_left;
                std::cout << "z rzędu nr " << (i + 1) << " zabierz " << stones_to_remove << " kamienie" << std::endl;
                return;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc <= 1 || isHelpArgument(argv[1])) {
        std::cout << "Program pomaga wygrać w grę nim." << std::endl;
        std::cout << "składnia:" << std::endl;
        std::cout << "nim liczba_1 liczba_2 ..." << std::endl;
        std::cout << "gdzie liczba_1, liczba_2, ... to liczby kamieni w kolejnych rzędach" << std::endl;
        return 0;
    }
    std::vector<int> piles;
    for (int i = 1; i < argc; ++i) {
        piles.push_back(std::stoi(argv[i]));
    }
    optimalMove(piles);
    return 0;
}
// zroibłem w konsolce g++ zad3.cpp -o program i aby sprawdzić wpisywałem w konsolkę ustawienia kombinacji, np.: ./program 1 2 3 4
