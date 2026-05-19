#include "analyzer.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <cctype>

Analyzer::Analyzer() {
    // konstruktorius - konteineriai inicializuojasi automatiškai
}

void Analyzer::cleanWord(std::string& word) {
    // šalinam skyrybos ženklus iš pradžios ir pabaigos
    while (!word.empty() && !std::isalpha((unsigned char)word.front()))
        word.erase(word.begin());
    while (!word.empty() && !std::isalpha((unsigned char)word.back()))
        word.pop_back();

    std::transform(word.begin(), word.end(), word.begin(),
        [](unsigned char c) { return std::tolower(c); });
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
            cleanWord(word);
            if (word.empty()) continue;
            wordCount_[word]++;
            crossRef_[word].push_back(lineNum);
        }

        lineNum++;
    }

    file.close();
}
