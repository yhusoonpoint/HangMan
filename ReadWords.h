/**
 * ReadWords Interface for CE221 assignment 2
 */

#ifndef READWORDS_H
#define READWORDS_H
/**
 * ReadWords class. Provides mechanisms to read a text file, and return
 * lower-case versions of words from that file.
 */

#include <string>
#include <fstream>
#include <set>

using namespace std;

 class ReadWords
 {
    public:
    /**
     * Constructor. Opens the file with the given filename and associates in
     * with the wordfile stream.
     * Initailises the other members.
     * Prints an error message then terminates the program if thr file cannot be opened.
     * Must not perform any other processing
     * @param filename - a C string naming the file to read.
     */
      ReadWords(const char *filename);
    
    /** 
     * deconstructor
     */
     ~ReadWords();

    /**
     * Closes the file.
     */
     void close();

    /**
     * Returns a string, being the next word in the file. 
     * All letters should be converted to lower case
     * Leading and trailing punctuation symbols should not be included in the word
     * but punctuation elsewhere should not be removed
     * Returns an empty string if next word contains no letters
     * @return - string - next word.
     */
     string getNextWord();

    /**
     * Returns true if there is a further word in the file, false if we have reached the
     * end of file.
     * @return - bool - !eof
     */
     bool isNextWord();

     /**
      * This method should get all phrases based on the words randomly selected before
      * the return type is bool so that true means the function was succesfully executed
      * and false otherwise. Phrases should be stored in the phrases set.
      **/
     bool getPhrases();

     /**
      * The method getWords should select randomly five words and store them in the words 
      * private member array. The return type is bool so that true means the function was succesfully 
      * executed and false otherwise
      * */
     bool getWords();

    /**
     * @brief Set the Difficulty Range object
     * 
     * @param min 
     * @param max 
     * @param difficultyInt 
     * points to the array from main
     */
     void setRange(int min[3], int max[3], int & difficultyInt);

    /**
     * @brief gets a word from words set
     * 
     * @return string 
     */
     string  getAWord();

    /**
     * @brief Get a Phrase from phrase set 
     * 
     * @param word 
     * @param newWord 
     * @return string 
     */
     string  getThePhrase(string & word, const string & newWord);

    /**
     * @brief replaces a word in a string 
     * 
     * @param phrase 
     * @param wordToFind 
     * @param newWord 
     */
     static void findAndReplace(string & phrase, const string & wordToFind, const string & newWord);

    /**
     * @brief changes to text lower
     * 
     * @param t 
     * @return string& 
     */
     static string & toLower(const string & t);

    /**
     * @brief returns set of similar words
     * 
     * @param word 
     * @return set<string>& 
     */
     set<string> & similiarWords(string word);

  private:
    ifstream wordfile;
    string nextword;
    bool eoffound;
    set<string> words, allWords;
    set<string> phrases;
    set<string> allSentences;
    bool fullstop;
    int * difficultyMinRange{};
    int * difficultyMaxRange{};
    int difficultyInt;
 };

 

#endif
