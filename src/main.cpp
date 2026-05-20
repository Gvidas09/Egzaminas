#include <iostream>
#include <filesystem>
#include "analyzer.h"

int main() {
    Analyzer a;

    try {
        std::filesystem::create_directories("output");

        a.loadText("data/tekstas.txt");

        a.saveWordFreq("output/zodziu_daznis.txt");
        std::cout << "Issaugota: output/zodziu_daznis.txt\n";

        a.saveCrossRef("output/cross_reference.txt");
        std::cout << "Issaugota: output/cross_reference.txt\n";

        a.saveUrls("output/url_adresas.txt");
        std::cout << "Issaugota: output/url_adresas.txt\n";
    } catch (const std::exception& e) {
        std::cerr << "Klaida: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
