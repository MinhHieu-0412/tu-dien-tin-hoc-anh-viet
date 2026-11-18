#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <cstdlib>
#include "dictionary.h"

// đo 3 lần lấy trung bình tránh nhiễu 
const int REPEAT = 3;

string randomWord(bool skewed) {
    int len = 5 + rand() % 6;
    string w;
    for (int i = 0; i < len; i++)
        w += (char)('a' + rand() % 26);
    if (skewed) w[0] = 'a';
    return w;
}

using Clock = chrono::steady_clock;
long long usBetween(Clock::time_point a, Clock::time_point b) {
    return chrono::duration_cast<chrono::microseconds>(b - a).count();
}

void runCase(ofstream& csv, const string& scenario, int n, bool skewed) {
    srand(12345);
    vector<string> words;
    for (int i = 0; i < n; i++)
        words.push_back(randomWord(skewed));

    long long sumIns = 0, sumSea = 0, sumDel = 0;
    int finalSize = 0;

    for (int r = 0; r < REPEAT; r++) {
        Dictionary dict;

        auto t0 = Clock::now();
        for (int i = 0; i < n; i++) dict.insertWord(words[i], "x");
        auto t1 = Clock::now();

        finalSize = dict.size();

        string meaning;
        for (int i = 0; i < n; i++) dict.searchWord(words[i], meaning);
        auto t2 = Clock::now();

        for (int i = 0; i < n; i++) dict.deleteWord(words[i]);
        auto t3 = Clock::now();

        sumIns += usBetween(t0, t1);
        sumSea += usBetween(t1, t2);
        sumDel += usBetween(t2, t3);
    }

    csv << scenario << ',' << n << ',' << finalSize << ','
        << sumIns / REPEAT << ',' << sumSea / REPEAT << ',' << sumDel / REPEAT << '\n';

    cout << scenario << " n=" << n << " xong\n";
}

int main() {
    ofstream csv("bench_result.csv");
    csv << "scenario,n,distinct,insert_us,search_us,delete_us\n";

    int randomSizes[] = {100, 500, 1000, 2000, 5000, 10000, 20000, 50000, 100000};
    for (int n : randomSizes) runCase(csv, "random", n, false);

    int skewedSizes[] = {100, 500, 1000, 2000, 5000, 10000, 20000};
    for (int n : skewedSizes) runCase(csv, "skewed", n, true);

    cout << "Da ghi bench_result.csv\n";
    return 0;
}