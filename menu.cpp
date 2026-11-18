#include <iostream>
#include <cstdlib>
#include <cctype>
#include "menu.h"

static string readLine(const string& prompt) {
    cout << prompt;
    string s;
    getline(cin, s);
    return s;
}

static void printMenu() {
    cout << "\n===== TU DIEN TIN HOC ANH - VIET =====\n"
         << "1. Them tu\n2. Tra cuu tu\n3. Sua nghia\n4. Xoa tu\n"
         << "5. Hien thi mot nhom\n6. Hien thi tat ca\n"
         << "7. Nap tu file\n8. Luu ra file\n0. Thoat (tu dong luu)\n";
}

static int readChoice() {
    string s = readLine("Chon chuc nang: ");
    if (s.empty() || s.size() > 3) return - 1;
    for (size_t i = 0; i < s.size(); i++) 
        if (!isdigit((unsigned char)s[i]))
            return -1;
    return atoi(s.c_str());
}

static void handleInsert(Dictionary& dict) {
    string e = readLine("Nhap tu tieng Anh: ");
    string v = readLine("Nhap nghia tieng Viet: ");
    switch (dict.insertWord(e, v)) {
        case INSERT_OK:        cout << "Them thanh cong.\n"; break;
        case INSERT_DUPLICATE: cout << "Tu da ton tai.\n"; break;
        case INSERT_INVALID:   cout << "Tu hoac nghia khong hop le (rong).\n"; break;
    }
}

static void handleSearch(Dictionary& dict) {
    string e = readLine("Nhap tu can tra: ");
    string meaning;
    if (dict.searchWord(e, meaning))
        cout << "Nghia: " << meaning << endl;
    else
        cout << "Khong tim thay.\n";
}

static void handleUpdate(Dictionary& dict) {
    string e = readLine("Nhap tu can sua: ");
    string v = readLine("Nhap nghia moi: ");
    if (dict.updateWord(e, v))
        cout << "Sua thanh cong.\n";
    else
        cout << "Khong tim thay tu hoac nghia moi rong.\n";
}

static void handleDelete(Dictionary& dict) {
    string e = readLine("Nhap tu can xoa: ");
    if (dict.deleteWord(e))
        cout << "Xoa thanh cong.\n";
    else
        cout << "Khong tim thay.\n";
}

static void handleDisplayGroup(Dictionary& dict) {
    string g = readLine("Nhap chu cai dau (ky tu khac chu cai se hien thi nhom khac): ");
    if (g.empty())
        cout << "Ban chua nhap gi.\n";
    else
        dict.displayGroup(g[0]);
}

static void handleLoad(Dictionary& dict) {
    string p = readLine("Nhap duong dan file: ");
    int k = dict.loadFromFile(p);
    if (k < 0) cout << "Khong mo duoc file.\n";
    else       cout << "Da nap " << k << " tu.\n";
}

static void handleSave(Dictionary& dict) {
    if (dict.saveToFile("dictionary.txt")) cout << "Da luu vao dictionary.txt.\n";
    else cout << "Luu that bai.\n";
}

void runMenu(Dictionary& dict) {
    int choice = -1;
    while (choice != 0) {
        printMenu();
        choice = readChoice();

        switch (choice) {
            case 1: handleInsert(dict);       break;
            case 2: handleSearch(dict);       break;
            case 3: handleUpdate(dict);       break;
            case 4: handleDelete(dict);       break;
            case 5: handleDisplayGroup(dict); break;
            case 6: dict.displayAll();        break;
            case 7: handleLoad(dict);         break;
            case 8: handleSave(dict);         break;
            case 0:                           break;
            default: cout << "Lua chon khong hop le.\n";
        }
    }
}