#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
using namespace std;

const int NUM_GROUPS = 27;
const int OTHER_GROUP = 26;

struct Node {
    string english;
    string vietnamese;
    Node* next;
};

enum InsertResult { INSERT_OK, INSERT_DUPLICATE, INSERT_INVALID };

class Dictionary {
    private:
    Node* table[NUM_GROUPS];
    int count;

    int hashIndex(const string& w) const;
    static string toLower(const string& s);
    static string trim(const string& s);

    public:
    Dictionary();
    ~Dictionary();
    Dictionary(const Dictionary&) = delete;
    Dictionary& operator=(const Dictionary&) = delete;

    InsertResult insertWord(const string& english, const string& vietnamese);
    bool searchWord(const string& english, string& meaning) const;
    bool updateWord(const string& english, const string& newMeaning);
    bool deleteWord(const string& english);

    void displayGroup(char c) const;
    void displayAll() const;

    int loadFromFile(const string& path);
    bool saveToFile(const string& path) const;

    int size() const;
    bool isEmpty() const;
};

#endif