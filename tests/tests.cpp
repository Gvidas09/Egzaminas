#include <iostream>
#include <fstream>
#include <cassert>
#include "analyzer.h"

static void writeFile(const std::string& path, const std::string& content) {
    std::ofstream f(path);
    f << content;
}

static int passed = 0;
static int failed = 0;

static void check(bool ok, const std::string& name) {
    if (ok) {
        std::cout << "PASS: " << name << "\n";
        passed++;
    } else {
        std::cout << "FAIL: " << name << "\n";
        failed++;
    }
}

int main() {
    // test 1 - wordCount skaiciuoja teisingai
    {
        writeFile("tests/tmp1.txt", "hello world hello\nhello world\n");
        Analyzer a;
        a.loadText("tests/tmp1.txt");
        auto counts = a.getWordCounts();
        check(counts["hello"] == 3, "wordCount hello == 3");
        check(counts["world"] == 2, "wordCount world == 2");
    }

    // test 2 - cleanWord salina skyrybos zenklus
    {
        writeFile("tests/tmp2.txt", "hello, world. hello!\n");
        Analyzer a;
        a.loadText("tests/tmp2.txt");
        auto counts = a.getWordCounts();
        check(counts.count("hello") && counts["hello"] == 2, "cleanWord: hello, ir hello! -> hello");
        check(counts.count("world") && counts["world"] == 1, "cleanWord: world. -> world");
        check(counts.count("hello,") == 0, "cleanWord: hello, nera su kableliu");
    }

    // test 3 - URL radimas
    {
        writeFile("tests/tmp3.txt", "ziurek https://www.google.com ir www.example.com\n");
        Analyzer a;
        a.loadText("tests/tmp3.txt");
        auto urls = a.getUrls();
        check(urls.count("https://www.google.com") > 0, "URL radimas: https://www.google.com");
        check(urls.count("www.example.com") > 0, "URL radimas: www.example.com");
        check(urls.count("ziurek") == 0, "URL radimas: paprastas zodis nera URL");
    }

    std::cout << "\nPraejo: " << passed << "/" << (passed + failed) << "\n";
    return failed > 0 ? 1 : 0;
}
