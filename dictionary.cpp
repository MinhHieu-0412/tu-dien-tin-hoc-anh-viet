#include "dictionary.h"
#include <cctype>
#include <fstream>
#include <iostream>
using namespace std;

Dictionary::Dictionary() {
    for (int i = 0; i < NUM_GROUPS; i++)
        table[i] = nullptr;
    count = 0;
}

Dictionary::~Dictionary() {
    for (int i = 0; i < NUM_GROUPS; i++) {
        Node* cur = table[i];
        while (cur != nullptr) {
            Node* temp = cur;
            cur = cur->next;
            delete temp;
        }
        table[i] = nullptr;
    }
    count = 0;
}

int Dictionary::hashIndex(const string& w) const {
    if (w.empty()) return OTHER_GROUP;
    
    char c = (char)tolower((unsigned char)w[0]);
    if (c >= 'a' && c <= 'z') return c - 'a';
    return OTHER_GROUP;
}

string Dictionary::trim(const string& s) {
    int start = 0;
    int end = (int)s.size() - 1;

    while (start <= end && isspace((unsigned char)s[start]))
        start++;
    while (end >= start && isspace((unsigned char)s[end]))
        end--;
    return s.substr(start, end - start + 1);
}

string Dictionary::toLower(const string& s) {
    string result = s;
    for (int i = 0; i < (int)result.size(); i++)
        result[i] = (char)tolower((unsigned char)result[i]);
    return result;
}

int Dictionary::size() const {
    return count;
}

bool Dictionary::isEmpty() const {
    return count == 0;
}

InsertResult Dictionary::insertWord(const string& english, const string& vietnamese) {
    string w = trim(english);
    string meaning = trim(vietnamese);
    if (w.empty() || meaning.empty()) return INSERT_INVALID;

    int idx = hashIndex(w);
    string key = toLower(w);

    Node* prev = nullptr;
    Node* cur = table[idx];
    while (cur != nullptr && toLower(cur->english) < key) {
        prev = cur;
        cur = cur->next;
    }

    if (cur != nullptr && toLower(cur->english) == key) return INSERT_DUPLICATE;

    Node* newNode = new Node;
    newNode->english = w;
    newNode->vietnamese = meaning;
    newNode->next = cur;

    if (prev == nullptr) table[idx] = newNode;
    else prev->next = newNode;

    count++;
    return INSERT_OK;
}

bool Dictionary::searchWord(const string& english, string& meaning) const {
    string w = trim(english);
    if (w.empty()) return false;

    int idx = hashIndex(w);
    string key = toLower(w);

    Node* cur = table[idx];
    while (cur != nullptr) {
        string curkey = toLower(cur->english);
        if (curkey == key) {
            meaning = cur->vietnamese;
            return true;
        }
        if (curkey > key) return false;
        cur = cur->next;
    }
    return false;
}

void Dictionary::displayGroup(char c) const {
    int idx = hashIndex(string(1, c));
    Node* cur = table[idx];

    if (cur == nullptr) {
        cout << "Nhom rong\n";
        return;
    }
    while (cur != nullptr) {
        cout << cur->english << " : " << cur->vietnamese << endl;
        cur = cur->next;
    }
}

void Dictionary::displayAll() const {
    if (isEmpty()) {
        cout << "Tu dien rong\n";
        return;
    }
    for (int i = 0; i < NUM_GROUPS; i++) {
        if (table[i] == nullptr) continue;
        char label = (i < OTHER_GROUP) ? (char)('a' + i) : '#';
        cout << "=== Nhom " << label << " ===\n";
        Node* cur = table[i];
        while (cur != nullptr) {
            cout << cur->english << " : " << cur->vietnamese << endl;
            cur = cur->next;
        }
    }
}

bool Dictionary::deleteWord(const string& english) {
    string w = trim(english);
    if (w.empty()) return false;

    int idx = hashIndex(w);
    string key = toLower(w);

    Node* prev = nullptr;
    Node* cur = table[idx];
    while (cur != nullptr && toLower(cur->english) < key) {
        prev = cur;
        cur = cur->next;
    }

    if (cur == nullptr || toLower(cur->english) != key) return false;

    if (prev == nullptr) table[idx] = cur->next;
    else prev->next = cur->next;

    delete cur;
    count--;
    return true;
}

bool Dictionary::updateWord(const string& english, const string& newMeaning) {
    string w = trim(english);
    string meaning = trim(newMeaning);
    if (w.empty() || meaning.empty()) return false;

    int idx = hashIndex(w);
    string key = toLower(w);
    
    Node* cur = table[idx];
    while (cur != nullptr) {
        string curKey = toLower(cur->english);
        if (curKey == key) {
            cur->vietnamese = meaning;
            return true;
        }
        if (curKey > key) return false;
        cur = cur->next;
    }
    return false;
}

bool Dictionary::saveToFile(const string& path) const {
    ofstream out(path);
    if (!out) return false;

    for (int i = 0; i < NUM_GROUPS; i++) {
        Node* cur = table[i];
        while (cur != nullptr) {
            out << cur->english << '|' << cur->vietnamese << '\n';
            cur = cur->next;
        }
    }
    return true;
}

int Dictionary::loadFromFile(const string& path) {
    ifstream in(path);
    if (!in) return -1;

    int loaded = 0;
    string line;
    bool firstLine = true;
    while (getline(in, line)) {
        if (firstLine && line.size() >= 3 && line.compare(0, 3, "\xEF\xBB\xBF") == 0) line.erase(0, 3);
        firstLine = false;

        if (trim(line).empty()) continue;

        size_t pos = line.find('|');
        if (pos == string::npos) continue;

        string eng = line.substr(0, pos);
        string vie = line.substr(pos + 1);

        if (insertWord(eng, vie) == INSERT_OK) loaded++;
    }
    return loaded;
}