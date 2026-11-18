#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
#include <iostream>
#include "dictionary.h"
#include "menu.h"

const string DATA_FILE = "dictionary.txt";

int main() {
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif
    Dictionary dict;

    int n = dict.loadFromFile(DATA_FILE);
    if (n < 0) cout << "Chua co file du lieu, bat dau tu dien rong.\n";
    else cout << "Da nap " << n << " tu tu file.\n";

    runMenu(dict);

    if (dict.saveToFile(DATA_FILE)) cout << "Da luu " << dict.size() << " tu. Tam biet!\n";
    else cout << "Khong luu duoc file khi thoat!\n";
    return 0;
}