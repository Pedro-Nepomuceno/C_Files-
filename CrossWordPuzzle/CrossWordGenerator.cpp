#include "CrosswordGenerator.h"
#include <iostream>
#include <fstream>

using namespace std;

string* wordArray = nullptr;
string** wordsIntersect = nullptr;
int wordCount = 0;

// Helper: convert uppercase letters to lowercase manually
char toLower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A');
    }
    return c;
}

// Helper: check if character is alphabetic
bool isAlpha(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

void loadWordsFromFile(const string& filename) {
    ifstream infile(filename);
    string word;
    wordCount = 0;

    while (infile >> word) wordCount++;

    infile.clear();
    infile.seekg(0, ios::beg);

    wordArray = new string[wordCount];
    int index = 0;
    while (infile >> word) {
        wordArray[index++] = word;
    }

    infile.close();
}

void sortWordsByLength() {
    for (int i = 0; i < wordCount - 1; ++i) {
        for (int j = i + 1; j < wordCount; ++j) {
            if (wordArray[i].length() < wordArray[j].length()) {
                string temp = wordArray[i];
                wordArray[i] = wordArray[j];
                wordArray[j] = temp;
            }
        }
    }
}

string sharedLetters(const string& s1, const string& s2) {
    bool letters[26] = { false };
    string result = "";

    for (int i = 0; i < s1.length(); ++i) {
        char c = s1[i];
        if (isAlpha(c)) {
            letters[toLower(c) - 'a'] = true;
        }
    }

    for (int i = 0; i < s2.length(); ++i) {
        char c = s2[i];
        if (isAlpha(c)) {
            char lower = toLower(c);
            if (letters[lower - 'a'] && result.find(lower) == string::npos) {
                result += lower;
            }
        }
    }

    return result;
}

void buildWordsIntersectMatrix() {
    wordsIntersect = new string*[wordCount];
    for (int i = 0; i < wordCount; ++i) {
        wordsIntersect[i] = new string[wordCount];
    }

    for (int i = 0; i < wordCount; ++i) {
        for (int j = 0; j < wordCount; ++j) {
            if (i != j) {
                wordsIntersect[i][j] = sharedLetters(wordArray[i], wordArray[j]);
            } else {
                wordsIntersect[i][j] = "";
            }
        }
    }
}

void writeCSV(const string& filename) {
    ofstream outfile(filename);

    for (int i = 0; i < wordCount; ++i) {
        for (int j = 0; j < wordCount; ++j) {
            outfile << i << "," << j << "," << wordsIntersect[i][j] << endl;
        }
    }

    outfile.close();
}

void cleanup() {
    if (wordArray) {
        delete[] wordArray;
        wordArray = nullptr;
    }

    if (wordsIntersect) {
        for (int i = 0; i < wordCount; ++i) {
            delete[] wordsIntersect[i];
        }
        delete[] wordsIntersect;
        wordsIntersect = nullptr;
    }
}
