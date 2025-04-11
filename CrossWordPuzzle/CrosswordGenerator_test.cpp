#include "CrosswordGenerator.h"
#include <iostream>
using namespace std;

int main() {
    loadWordsFromFile("wordlist.txt");
    sortWordsByLength();
    buildWordsIntersectMatrix();
    writeCSV("wordsIntersect.csv");
    cleanup();

    cout << "Crossword intersect file created: wordsIntersect.csv" << endl;
    return 0;
}
