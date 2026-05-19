#pragma once

#include <string>
#include <map>
#include <vector>
#include <set>

class Analyzer {
private:
    std::map<std::string, int> wordCount_;
    std::map<std::string, std::vector<int>> crossRef_;
    std::set<std::string> urls_;

    void cleanWord(std::string& word);

public:
    Analyzer();

    // nuskaito tekstą iš failo
    void loadText(const std::string& filename);

    std::map<std::string, int> getWordCounts() const;
    std::map<std::string, std::vector<int>> getCrossRef() const;
    std::set<std::string> getUrls() const;

    void saveWordFreq(const std::string& filename) const;
    void saveCrossRef(const std::string& filename) const;
    void saveUrls(const std::string& filename) const;
};
