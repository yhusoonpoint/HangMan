#include "ReadWords.h"
#include <iostream>
#include <cctype>
#include <random>
#include "Random.h"

using namespace std;

//converts lower case string into upper 
string & ReadWords::toLower(const string & t)
{
    string * upper = new string;
    *upper = t;
    for (int i = 0; i < t.size(); i++)
    {
        char & a = (*upper)[i];
            if((a>='A')&&(a<='Z'))
                a+= -'A' + 'a';
    }
    return *upper; 
}

// finds ll given word in a string and replaces it with a new word
// convert to lower to make sure they can be found if cases are different
void ReadWords::findAndReplace(string & phrase, const string & wordToFind, const string & newWord)
{
  if(wordToFind.empty())
    return;
  size_t start_pos = 0;
  while((start_pos = toLower(phrase).find(toLower(wordToFind), start_pos)) != std::string::npos) 
  {
    phrase.replace(start_pos, wordToFind.length(), newWord);
    start_pos += newWord.length(); 
  }
}

// removes any symbol that isn't in between a word.
string removePunct(string word)
{ // should return a copy of the word with all leading and trailing punctuation      
  // removed
  // punctuation elsewhere in the word should not be removed
  // note that a word could havce more than one leading/trailing punctuation symbols
  // you need to write this
  string newWord;
  for(int i = 0; i < word.size(); i++)
  {
    if((ispunct(word[i]) && (ispunct(word[i+1]) || word[i-1] == '\0' || word[i-1] == ' ') || (i == word.size() - 1 && (ispunct(word[i]) && word[i] != '\'' ))))
    {}
    else
    {
      newWord += word[i];
    }
  }
  return newWord;
}

// reads all words in file
// adds the sentences into a set
ReadWords::ReadWords(const char *fname)
{   
  wordfile.open(fname);//open file
  if(!wordfile)
  {   
    cout << "Failed to open " << fname << endl;
    exit(1);
  }
  wordfile >> nextword;
  eoffound = false;

  string sentence = nextword;
  allWords.insert(toLower(removePunct(sentence)));
  while(isNextWord())
  {
    nextword = getNextWord();
    sentence += sentence.empty() ? nextword : " " + nextword;
    
    if(fullstop)
    {
      allSentences.insert(sentence);
      sentence = "";
      fullstop = false;
    }    
  }

  if(!fullstop && *allSentences.end() != sentence && !sentence.empty())
    allSentences.insert(sentence);

  close();
}

// deconstruct
ReadWords::~ReadWords()
{
  words.clear();
  allWords.clear();
  phrases.clear();
  allSentences.clear();
}

// returns next word in file, converted to lower case and adds to allWords set
// if next word contains no letters, it's not added to set
string ReadWords::getNextWord()
{
  wordfile >> nextword;
  string word = nextword;

  if (wordfile.eof())
     eoffound = true;

  // if there's full stop, it sets to true to know it's a sentence and a new line is needed
  if (word.find('.') != std::string::npos || word.find('?') != std::string::npos || word.find('!') != std::string::npos)
    fullstop = true;


  string filter = word;
  filter = toLower(removePunct(filter));

  if(filter.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos)
    allWords.insert(filter);
    
  return word;
}

// returns if it's end of line or not
bool ReadWords::isNextWord()
{ 
  return !eoffound;
}

// gets 5 phrases for each word in words set
bool ReadWords::getPhrases()
{ 
  for(const string & i : words)
  { 
    int count = 0;
    for(auto & i2 : allSentences)
    {
      if(toLower(removePunct(i2)).find(i) != std::string::npos && i2.size() > 3)
      {
        phrases.insert(i2);
        count++;
        if(count == 5)
          break;
      }
    } 
  }
  return phrases.size() == 5;
}

// adds 10 words to the word set depending on range of difficulty
bool ReadWords::getWords()
{ 
  int wordCount=0;
  if(difficultyMinRange[difficultyInt-1] > difficultyMaxRange[difficultyInt-1] )
    swap(difficultyMinRange[difficultyInt-1], difficultyMaxRange[difficultyInt-1]);
  for(auto i : allWords)
    if(!(i.size() < difficultyMinRange[difficultyInt-1] || i.size() > difficultyMaxRange[difficultyInt-1]))
      wordCount++;
    

  if(wordCount < 10)
    return false;

  while(words.size() < 10)
  {
    const string & word = *next(allWords.begin(), Random::random(0,allWords.size())); //gets a random word set
    if(word.size() < difficultyMinRange[difficultyInt-1] || word.size() > difficultyMaxRange[difficultyInt-1])
      continue;

    if(words.find(word) == words.end())
    {
      words.insert(word);
    }
  }
  return words.size() == 10;
}

// closes file
void ReadWords::close()
{ 
  wordfile.close();
}

// recieves array from main to know the range of difficulties.
void ReadWords::setRange(int min[3], int max[3], int & difficultyInt)
{
  difficultyMinRange = min;
  difficultyMaxRange = max;
  this->difficultyInt = difficultyInt;
}

// randomly selects a word from words set
string ReadWords::getAWord() 
{
  return  *next(words.begin(), Random::random(0,words.size())); 
}

// get the phrase for the word and replace the word in the phrase with new word
string ReadWords::getThePhrase(string & word, const string & newWord)
{
  for(auto & i : phrases)
    {
      if(toLower(i).find(word) != std::string::npos)
      {
        string newI = i;
        findAndReplace(newI,word, newWord);
        return newI;
      }
    }
    return "";
}

// returns a set of similar words
// it first gets the indexes of letter
// compares if the word in set has the same index as the word supplied
set<string> & ReadWords::similiarWords(string word)
{
  set<string> * similar = new set<string>;
  set<int> indexes;
  word = toLower(word);
  for(int i2 = 0; i2 < word.size(); i2++)
    if(tolower(word[i2]) != 'x')
      indexes.insert(i2);

  for(auto & i : allWords)
  {
    if(i.size() == word.size())
    {
      int i4 = 0;
      for(auto & i3 : indexes)
        if(i[i3] == word[i3])
          i4++;
      if(i4 == indexes.size())
        similar->insert(i);
    }
  }
  return *similar;
}

