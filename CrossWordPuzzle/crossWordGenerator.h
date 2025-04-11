// CrosswordGenerator.h

#include <string>

// Using the standard namespace so we don't have to write std:: everywhere
using namespace std;

// Global variables
extern string* wordArray;            // Dynamic array of words
extern string** wordsIntersect;     // 2D array to store shared letters
extern int wordCount;               // Number of words

// Function declarations
void loadWordsFromFile(const string& filename);     // Load words from wordlist.txt
void sortWordsByLength();                           // Sort words from longest to shortest
string sharedLetters(const string& s1, const string& s2); // Get common letters (ignores case and symbols)
void buildWordsIntersectMatrix();                   // Fill the 2D shared-letter matrix
void writeCSV(const string& filename);              // Output results to CSV file
void cleanup();                                     // Free all dynamically allocated memory
