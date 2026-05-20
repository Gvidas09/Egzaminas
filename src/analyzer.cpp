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
            findUrls(word);
            cleanWord(word);
            if (word.empty()) continue;
            wordCount_[word]++;
            crossRef_[word].push_back(lineNum);
        }

        lineNum++;
    }

    file.close();
}

std::map<std::string, int> Analyzer::getWordCounts() const {
    return wordCount_;
}

std::map<std::string, std::vector<int>> Analyzer::getCrossRef() const {
    return crossRef_;
}

std::set<std::string> Analyzer::getUrls() const {
    return urls_;
}

void Analyzer::saveWordFreq(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open())
        throw std::runtime_error("Nepavyko sukurti failo: " + filename);

    for (const auto& [word, count] : wordCount_) {
        if (count > 1)
            out << word << ": " << count << "\n";
    }

    out.close();
}

void Analyzer::findUrls(const std::string& token) {
    bool isUrl = (token.find("https://") == 0 ||
                  token.find("http://")  == 0 ||
                  token.find("www.")     == 0);
    if (!isUrl) return;

    // šalinam baigiančius skyrybos ženklus
    std::string url = token;
    while (!url.empty() && !std::isalnum((unsigned char)url.back()))
        url.pop_back();

    if (!url.empty())
        urls_.insert(url);
}

void Analyzer::saveCrossRef(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open())
        throw std::runtime_error("Nepavyko sukurti failo: " + filename);

    for (const auto& [word, lines] : crossRef_) {
        if (lines.size() <= 1) continue;

        out << word << " -> eilutes: ";
        for (int i = 0; i < (int)lines.size(); i++) {
            if (i > 0) out << ", ";
            out << lines[i];
        }
        out << "\n";
    }

    out.close();
}

void Analyzer::saveUrls(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open())
        throw std::runtime_error("Nepavyko sukurti failo: " + filename);

    for (const auto& url : urls_)
        out << url << "\n";

    out.close();
}
