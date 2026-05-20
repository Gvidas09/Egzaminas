#include <iostream>
#include "analyzer.h"

int main() {
    Analyzer a;

    try {
        a.loadText("data/tekstas.txt");
        a.saveWordFreq("output/zodziu_daznis.txt");
        std::cout << "Issaugota: output/zodziu_daznis.txt\n";
    } catch (const std::exception& e) {
        std::cerr << "Klaida: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
