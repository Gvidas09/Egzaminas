#include "analyzer.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

Analyzer::Analyzer() {
    // konstruktorius - konteineriai inicializuojasi automatiškai
}

void Analyzer::loadText(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Nepavyko atidaryti failo: " + filename);

    std::string line;
    int lineNum = 1;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string word;

        while (iss >> word) {
            // TODO: čia reiks valyti žodžius nuo skyrybos ženklų
            wordCount_[word]++;
            crossRef_[word].push_back(lineNum);
        }

        lineNum++;
    }

    file.close();
}
