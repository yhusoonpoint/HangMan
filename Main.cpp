/**
 * @file Main.cpp
 * @author AA20997 - AB - 2000161
 * @brief - Completed Hangman game with all functions working
 * @version 0.1
 * @date 2022-01-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Gamer.h"
#include "Manager.h"
#include "GetLine.h"
#include "MyLinkedList.h"
#include "IOFile.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <windows.h> 
#include "ReadWords.h"
#include "Random.h"

using namespace std;

// converts difficulty index to the correct string value
string difficulty[3];

//overloading the * for string to print the string the number of times required
string operator * (const string & word, unsigned int amount) {
    string newWord;
    while (amount--) 
        newWord += word;
    return newWord;
}

//split words to vector using delimiter provided.
vector<string> * splitter(const string & word, char delimiter) 
{
    vector<string> * tempVector = new vector<string>;
    istringstream iss(word);
    string eachData;
    while (getline(iss, eachData, delimiter)) 
        tempVector->push_back(eachData);
    return tempVector;
}

// reads line from file and splits into vector
// if readAll is true then all file are split and added into another vector
vector<string> * readFile(const char * path, const string & name, const char del, vector<vector<string>> * allData, const bool readAll)
{
    ifstream * ifs = new ifstream(path);
    string * line = new string;
    vector<string> * temp;
    while (getline(*ifs, *line)) 
    {
        if(readAll)
        {
            temp = splitter(*line, del);
            allData->push_back(*temp);
        }
        else
        {
            if((*line).find(name) != string::npos) 
            { 
                temp = splitter(*line, del);
                delete line;
                return temp;
            }
        }
    }
    delete line;
    return nullptr;
}

//method to change the first word to alphabet and the others if available to lower
string & nameFormatting(string & t)
{
    for (int i = 0; i < t.size(); i++)
    {
        char & a = t[i];
        if (i == 0 || t[i-1] == ' ') //checks if the first letter or the letter after a space is lower the converts
            if((a>='a')&&(a<='z'))
                a+='A' - 'a';
            else 
                continue;
        else if((a>='A')&&(a<='Z') && (i != 0 || t[i-1] != ' '))
            a-='A' - 'a';
    }
    return t;
}

//converts lower case string into upper 
string & toUpper(const string & t)
{
    string * upper = new string;
    *upper = t;
    for (int i = 0; i < t.size(); i++)
    {
        char & a = (*upper)[i];
            if((a>='a')&&(a<='z'))
                a+='A' - 'a';
    }
    return *upper; //Does replace the old variable intentionally in case I want it untouched.
}

//template method to create either a manager or gamer object
template<class T>
T * login(string & name)
{
    const char * fileName = "users.txt";
    vector<string> * data = readFile(fileName,name,' ',nullptr,false); //reads from file and store into vector
    return new T((data->at(1) + " " + data->at(2)),stoi(data->at(0))); //creates new object depending on type and returns
}

//method containing a vector of hangman drawings
vector<string> * hangmanDrawings()
{
    vector<string> * hangman = new vector<string>;
    hangman->push_back(" ___________.._________________" );
    hangman->push_back("|X.__________))_______________X|                S C O R E :         ");
    hangman->push_back("|X|       // ||              |X|");
    hangman->push_back("|X|      //  ||              |X|");
    hangman->push_back("|X|     //   ||              |X|");
    hangman->push_back("|X|    //    ||              |X|" );
    hangman->push_back("|X|   //     ||              |X|" );
    hangman->push_back("|X|  //      ()              |X|" );
    hangman->push_back("|X| //                       |X|                W O R D :           " );
    hangman->push_back("|X|//                        |X|");
    hangman->push_back("|X|/                         |X|");
    hangman->push_back("|X|                          |X|");
    hangman->push_back("|X|                          |X|" );
    hangman->push_back("|X|                          |X|" );
    hangman->push_back("|X|                          |X|" );
    hangman->push_back("|X|                          |X|" );
    hangman->push_back("|X|                          |X|                M I S S E S :       " );
    hangman->push_back("|X|                          |X|" );
    hangman->push_back("|X|                          |X|" );
    hangman->push_back("|XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|" );
    hangman->push_back("|X|    \\ \\            / /    |X|");
    hangman->push_back("|X|     \\ \\          / /     |X|");
    hangman->push_back("|X|      \\ \\        / /      |X|");
    hangman->push_back("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" );
    hangman->push_back(" ___________.._________________" );
    hangman->push_back("|X.__________))_______________X|                S C O R E :         ");
    hangman->push_back("|X|       // ||              |X|");
    hangman->push_back("|X|      //  ||              |X|");
    hangman->push_back("|X|     //   ||.-\'\'.         |X|");
    hangman->push_back("|X|    //    |/  _  \\        |X|" );
    hangman->push_back("|X|   //     ||  `/,|        |X|" );
    hangman->push_back("|X|  //      (\\`_.'          |X|" );
    hangman->push_back("|X| //                       |X|                W O R D :           " );
    hangman->push_back("|X|//                        |X|");
    hangman->push_back("|X|/                         |X|");
    hangman->push_back("|X|                          |X|");
    hangman->push_back("|X|                          |X|" );
    hangman->push_back("|X|                          |X|" );
    hangman->push_back("|X|                          |X|" );
    hangman->push_back("|X|                          |X|" );
    hangman->push_back("|X|                          |X|                M I S S E S :       " );
    hangman->push_back("|X|                          |X|" );
    hangman->push_back("|X|                          |X|" );
    hangman->push_back("|XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|" );
    hangman->push_back("|X|    \\ \\            / /    |X|");
    hangman->push_back("|X|     \\ \\          / /     |X|");
    hangman->push_back("|X|      \\ \\        / /      |X|");
    hangman->push_back("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" );
    hangman->push_back(" ___________.._________________" );
    hangman->push_back("|X.__________))_______________X|                S C O R E :         ");
    hangman->push_back("|X|       // ||              |X|");
    hangman->push_back("|X|      //  ||              |X|");
    hangman->push_back("|X|     //   ||.-\'\'.         |X|");
    hangman->push_back("|X|    //    |/  _  \\        |X|" );
    hangman->push_back("|X|   //     ||  `/,|        |X|" );
    hangman->push_back("|X|  //      (\\`_.'          |X|" );
    hangman->push_back("|X| //       .`--.           |X|                W O R D :           " );
    hangman->push_back("|X|//        |. .|           |X|");
    hangman->push_back("|X|/         |   |           |X|");
    hangman->push_back("|X|          | . |           |X|");
    hangman->push_back("|X|          |   |           |X|" );
    hangman->push_back("|X|                          |X|" );
    hangman->push_back("|X|                          |X|" );
    hangman->push_back("|X|                          |X|" );
    hangman->push_back("|X|                          |X|                M I S S E S :       " );
    hangman->push_back("|X|                          |X|" );
    hangman->push_back("|X|                          |X|" );
    hangman->push_back("|XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|" );
    hangman->push_back("|X|    \\ \\            / /    |X|");
    hangman->push_back("|X|     \\ \\          / /     |X|");
    hangman->push_back("|X|      \\ \\        / /      |X|");
    hangman->push_back("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" );
    hangman->push_back(" ___________.._________________" );
    hangman->push_back("|X.__________))_______________X|                S C O R E :         ");
    hangman->push_back("|X|       // ||              |X|");
    hangman->push_back("|X|      //  ||              |X|");
    hangman->push_back("|X|     //   ||.-\'\'.         |X|");
    hangman->push_back("|X|    //    |/  _  \\        |X|" );
    hangman->push_back("|X|   //     ||  `/,|        |X|" );
    hangman->push_back("|X|  //      (\\`_.'          |X|" );
    hangman->push_back("|X| //      .-`--.           |X|                W O R D :           " );
    hangman->push_back("|X|//      /Y . .|           |X|");
    hangman->push_back("|X|/      // |   |           |X|");
    hangman->push_back("|X|      //  | . |           |X|");
    hangman->push_back("|X|     ')   |   |           |X|" );
    hangman->push_back("|X|                          |X|" );
    hangman->push_back("|X|                          |X|" );
    hangman->push_back("|X|                          |X|" );
    hangman->push_back("|X|                          |X|                M I S S E S :       " );
    hangman->push_back("|X|                          |X|" );
    hangman->push_back("|X|                          |X|" );
    hangman->push_back("|XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|" );
    hangman->push_back("|X|    \\ \\            / /    |X|");
    hangman->push_back("|X|     \\ \\          / /     |X|");
    hangman->push_back("|X|      \\ \\        / /      |X|");
    hangman->push_back("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" );
    hangman->push_back(" ___________.._________________" );
    hangman->push_back("|X.__________))_______________X|                S C O R E :         ");
    hangman->push_back("|X|       // ||              |X|");
    hangman->push_back("|X|      //  ||              |X|");
    hangman->push_back("|X|     //   ||.-\'\'.         |X|");
    hangman->push_back("|X|    //    |/  _  \\        |X|" );
    hangman->push_back("|X|   //     ||  `/,|        |X|" );
    hangman->push_back("|X|  //      (\\`_.'          |X|" );
    hangman->push_back("|X| //      .-`--'.          |X|                W O R D :           " );
    hangman->push_back("|X|//      /Y . . Y\\\\        |X|");
    hangman->push_back("|X|/      // |   |  \\\\       |X|");
    hangman->push_back("|X|      //  | . |   \\\\      |X|");
    hangman->push_back("|X|     ')   |   |    (`     |X|" );
    hangman->push_back("|X|                          |X|" );
    hangman->push_back("|X|                          |X|" );
    hangman->push_back("|X|                          |X|" );
    hangman->push_back("|X|                          |X|                M I S S E S :       " );
    hangman->push_back("|X|                          |X|" );
    hangman->push_back("|X|                          |X|" );
    hangman->push_back("|XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|" );
    hangman->push_back("|X|    \\ \\            / /    |X|");
    hangman->push_back("|X|     \\ \\          / /     |X|");
    hangman->push_back("|X|      \\ \\        / /      |X|");
    hangman->push_back("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" );
    hangman->push_back(" ___________.._________________" );
    hangman->push_back("|X.__________))_______________X|                S C O R E :         ");
    hangman->push_back("|X|       // ||              |X|");
    hangman->push_back("|X|      //  ||              |X|");
    hangman->push_back("|X|     //   ||.-\'\'.         |X|");
    hangman->push_back("|X|    //    |/  _  \\        |X|" );
    hangman->push_back("|X|   //     ||  `/,|        |X|" );
    hangman->push_back("|X|  //      (\\`_.'          |X|" );
    hangman->push_back("|X| //      .-`--'.          |X|                W O R D :           " );
    hangman->push_back("|X|//      /Y . . Y\\\\        |X|");
    hangman->push_back("|X|/      // |   |  \\\\       |X|");
    hangman->push_back("|X|      //  | . |   \\\\      |X|");
    hangman->push_back("|X|     ')   |   |    (`     |X|" );
    hangman->push_back("|X|          ||              |X|" );
    hangman->push_back("|X|          ||              |X|" );
    hangman->push_back("|X|          ||              |X|" );
    hangman->push_back("|X|          ||              |X|                M I S S E S :       " );
    hangman->push_back("|X|         / |              |X|" );
    hangman->push_back("|X|         `-'              |X|" );
    hangman->push_back("|XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|" );
    hangman->push_back("|X|    \\ \\            / /    |X|");
    hangman->push_back("|X|     \\ \\          / /     |X|");
    hangman->push_back("|X|      \\ \\        / /      |X|");
    hangman->push_back("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" );
    hangman->push_back(" ___________.._________________" );
    hangman->push_back("|X.__________))_______________X|                S C O R E :         ");
    hangman->push_back("|X|       // ||              |X|");
    hangman->push_back("|X|      //  ||              |X|");
    hangman->push_back("|X|     //   ||.-\'\'.         |X|");
    hangman->push_back("|X|    //    |/  _  \\        |X|" );
    hangman->push_back("|X|   //     ||  `/,|        |X|" );
    hangman->push_back("|X|  //      (\\`_.'          |X|" );
    hangman->push_back("|X| //      .-`--'.          |X|                W O R D :           " );
    hangman->push_back("|X|//      /Y . . Y\\\\        |X|");
    hangman->push_back("|X|/      // |   |  \\\\       |X|");
    hangman->push_back("|X|      //  | . |   \\\\      |X|");
    hangman->push_back("|X|     ')   |   |    (`     |X|" );
    hangman->push_back("|X|          || ||           |X|" );
    hangman->push_back("|X|          || ||           |X|" );
    hangman->push_back("|X|          || ||           |X|" );
    hangman->push_back("|X|          || ||           |X|                M I S S E S :       " );
    hangman->push_back("|X|         / | | \\          |X|" );
    hangman->push_back("|X|         `-' `- '         |X|" );
    hangman->push_back("|XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|" );
    hangman->push_back("|X|    \\ \\            / /    |X|");
    hangman->push_back("|X|     \\ \\          / /     |X|");
    hangman->push_back("|X|      \\ \\        / /      |X|");
    hangman->push_back("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" );
    return hangman;
}

//function to play the game
void game(Gamer * gamer, GetLine * myGet, const char * path)
{
    //variables
    vector<string> * hangman = hangmanDrawings();
    string underscore                =      "_ ";
    string misses;
    string guess ;
    int guessCorrectCount            =         0;
    int difficultyInt                =         0;
    int missesCount                  =         0;
    int skip                         =         0;
    bool error                       =     false;
    // calculated by adding 6 multiplied by the 
    // index of difficulty for every correct 
    // guess, 4 is added if the word is guess 
    // correctly and 10 is also added if there's
    // no misses,3 is deducted if guess is wrong
    // if guess straight 30 * level is added
    float score                      =         0;
    int difficultyMinRange [3];
    int difficultyMaxRange [3];
    ifstream ifs("range.txt");
    int num;
    if(!ifs.good())
    {
        IOFile::quickAdd("range.txt", "1 6 10 5 10 0");
    }
    else
    {
        int idx = 0;
        while(idx < 6)
        {
            ifs >> num;
            if(idx < 3)
                difficultyMinRange[idx] = num;
            else    
                difficultyMaxRange[idx-3] = num;
            idx++;
        }
        difficultyMaxRange[2] = difficultyMaxRange[2] == 0 ? INT_MAX : difficultyMaxRange[2];
    }
    system("cls"); // clear terminal
    difficultyInt = myGet->intGetLineWithOption("SELECT DIFFICULTY:\n   1)Easy -> words with size between " + to_string(difficultyMinRange[0]) + '-' + to_string(difficultyMaxRange[0]) + 
                   "\n   2)Medium -> words with size between " + to_string(difficultyMinRange[1]) + '-' + to_string(difficultyMaxRange[1]) +  
                   "\n   3)High -> words with size between " + to_string(difficultyMinRange[2]) + '-' + to_string(difficultyMaxRange[2]) +  "\nOption:  ", difficultyInt, 3); //picking difficulty
    ReadWords rw(path);
    rw.setRange(difficultyMinRange,difficultyMaxRange, difficultyInt); // passed the array of range to ReadWords
    bool wordCheck = rw.getWords(); 
    rw.getPhrases();
    string word;
    num=0;
    while(word.empty())
    {
      if(!wordCheck || num++ == 2)
      {
          cout << "\nCOULD NOT GET 10 WORDS, PLEASE CHOOSE A DIFFERENT DIFFICULTY.\n";
          system("pause");
          return; 
      }
      word= rw.getAWord();
    }
    string newWord = string("X") * word.size();
    string oldWord = newWord;
    string phrase = rw.getThePhrase(word, newWord);
    word = toUpper(word);
    string guesses =    underscore * word.size();
    /**
     * checks for punctuation between word
     * and adds it to the guess word
     */
    for(int o = 0; o < word.size(); o++)
    {
        if(ispunct(word[o]) || isdigit(word[o]))
        {
            guesses[o*2] = newWord[o] = word[o];
            guessCorrectCount++;
            rw.findAndReplace(phrase, oldWord, newWord);
            oldWord = newWord;
        }
    }
    system("cls"); // clear terminal
    // Game loop
    do
    {
        // looping through the vector
        skip = 0;
        if(missesCount > 2) // gives hint when there's 4 lives left
        {
            cout << "Tip: \"" << phrase << "\"\n";
        }
        if(missesCount > 3 && guessCorrectCount > 0) // gives int when there's 2 lives left and only if the have at least 1 guess
        {
            set<string> similar = rw.similiarWords(oldWord);
            cout << "WORDS MATCHING " << oldWord << " ARE [ ";
            for(auto & i : similar)
            {
                if(toUpper(i) != toUpper(word))
                {
                    cout << toUpper(i) << " ";
                }
            }
            cout << "]\n";
        }
        for (auto i = hangman->begin() + (24 * missesCount); (skip <= 24) & i != hangman->end(); i++)
        {
            // skip is to check the current line and add the corresponding data to it.
            if(skip == 1)
                cout << *i << score   << endl;
            else if(skip == 8)
                cout << *i << guesses << endl;
            else if(skip == 16)
                cout << *i << misses  << endl;
            else
                cout << *i            << endl;
            skip++;
        }
        cout << "                                                G U E S S :         ";
        char * temp = new char[256];
        cin.getline(temp,256);
        guess = temp;
        guess = nameFormatting(guess);
        
        //checks if the player guessed the word
        if(guess.size() == word.size())
        {
            if(nameFormatting(guess) != nameFormatting(word))
            {
                missesCount = 6;
                break;
            }
            else 
            {
                guessCorrectCount = word.size();
                score += (30 * difficultyInt);
            }
        }
        else if( guess.empty() || guess == " " || guess.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos ||guess.size() > 1) // makes sure only alphabet are written
        {
            system("cls");
            cout << "\nINVALID INPUT, PLEASE TRY AGAIN.\n\n";
            error = true;
            continue;
        }
        else
        {
            system("cls");
        }
        if(guesses.find(guess) != string::npos || misses.find(guess) != string::npos)
        {   
            system("cls");
            //tells gamer if input is in missed or guessed
            cout << "\nINPUT HAS BEEN ENTERED PREVIOUSLY!!!\n\n";
            error = true;
            continue;
        }
        error = false;
        //checking if the letter input is in the word
        for(int i = 0; i < word.size() && guessCorrectCount != word.size(); i++)
        {
            if(guess[0] == word[i])
            {
                //displaying position of correct input  and updating score
                guesses[i*2] = word[i];
                newWord[i] = word[i];
                score += (6 * difficultyInt);
                guessCorrectCount++;
            }
        }
        rw.findAndReplace(phrase, rw.toLower(oldWord), newWord); /// replacing the word in the phrase
        oldWord = newWord;
        //updating score and add wrong letter to miss display
        if (word.find(guess) == string::npos) 
        {
            misses += (misses.empty() ? guess : (", " + guess));
            missesCount++;
            score -= score < 3 ? 0 : 1;
        }
        //if the guess count and the word size is correct then it means they won the game
        //it also adds the score to the gamer object
        if(guessCorrectCount == word.size())
        {
            system("cls");
            cout << "CONGRATS, YOU GUESSED THE WORD CORRECTLY!!!\n";
            score += (4 * difficultyInt) + (missesCount == 0 ? 10 : 0);
            break;
        }

    } while (error || missesCount < 6 );    
    //if gamer has no lives yet, then it prints the hang man and message
    skip = 0;
    /*
        gamer failed to guess the word
        then it comes here
    */
    if(missesCount == 6)
    {
        system("cls");
        for (auto i = hangman->begin() + (24 * missesCount); i != hangman->end(); i++)
            if(skip++ == 1)
                cout << *i << score   << endl;
            else    
                cout << *i <<endl;
        cout << "\nSORRY, YOU FAILED TO GUESS THE WORD!!!\n";
    }
    cout << "\nEND OF GAME, THANK YOU FOR PLAYING, " << toUpper(gamer->getName()) 
         << ".\nYOUR SCORE WAS " << score 
         << ".\nDIFFICULT WAS " << toUpper(difficulty[difficultyInt-1])
         << ".\n\n";

    
    rw.findAndReplace(phrase, rw.toLower(oldWord), word);
    cout << "\nTHE WORD WAS: " << word <<  "\n\n" << toUpper(phrase) << "\n\n";
    gamer->addScore(score,difficulty[difficultyInt-1]);
    delete hangman;
    system("pause");
}

// Creates collection and add to Collection in main
template<typename T>
T createCollection(const char * path)
{
    T collectionsOfGamers;
    Gamer * gamer = nullptr;
    vector<vector<string>> * allFileLines = new vector<vector<string>>; //hold the vectors of all line
    readFile(path,string(""),' ',allFileLines, true); //reads the file and store to 2d vector
    for (auto it = allFileLines->begin(); it != allFileLines->end(); it++) 
    {
        if(it->empty() || (it->at(0).size() > 4 && it->size() <= 2) || it->size() < 4)
            continue;
        if(it->at(0).size() > 4)
        {            
            string name = (it->at(1) + " " + it->at(2));
            gamer = login<Gamer>(name); //uses template to login
            int index = 0;
            for (auto i = it->begin() + 3; i != it->end(); ++i) // adds score to gamer object for each difficult if they exist 
            {
                if(*i == "e")
                    index = 0;
                else if(*i == "m")
                    index =  1;
                else if(*i == "h")
                    index = 2;
                i++;
                gamer->addScore(stof(*i),difficulty[index]);
                
            }
            collectionsOfGamers.push_back(*gamer); //adds to the tail of the link list
        }
    }  
    return collectionsOfGamers;
}

template<typename T>
void changeName(string & newName, T * user)
{
    user->changeName(newName);
    user->updateFile();
}

// using vector to print top 10
void printTopTen(vector<Gamer> & mainCollectionsOfGamers, const char * path, Gamer * curGamer)
{
    vector<Gamer> collectionsOfGamers = createCollection<vector<Gamer>>(path);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for(int j = 0; j < 3; j++)
    {
        system("cls");
        sort(collectionsOfGamers.begin(), collectionsOfGamers.end(), [&](Gamer & g1, Gamer & g2) {return g1.getFinalScore(j) > g2.getFinalScore(j); });
        cout << setw(25) << "RANK" << setw(25) << "NAME" << setw(25) << "REG NO" << setw(25) << "SCORE" << setw(25) << "DIFFICULTY\n";
        int i = 1;
        for(auto itr = collectionsOfGamers.begin(); itr != collectionsOfGamers.end() && i < 11; itr++)
        {
            if((*itr).getRegNo() == curGamer->getRegNo())
            {
                SetConsoleTextAttribute(hConsole, 23); //changes text colour
            }
            cout << endl << setw(25) << i++ << setw(25) << toUpper((*itr).getName()) << setw(25) << (*itr).getRegNo() << setw(25) << (*itr).getFinalScore(j) << setw(25) << toUpper(difficulty[j]) << endl;    
            
                SetConsoleTextAttribute(hConsole, 7);            
        }
        cout<<'\n';
        system("pause");
    }
    mainCollectionsOfGamers = collectionsOfGamers;
}

// using linked list to sort and display top ten.
void printTopTen(MyLinkedList<Gamer> & mainCollectionsOfGamers, const char * path, Gamer * curGamer)
{
    MyLinkedList<Gamer> collectionsOfGamers = createCollection<MyLinkedList<Gamer>>(path);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    //looping three times to print out the top 10 of each difficult
    for(int j = 0; j < 3; j++)
    {
        system("cls");
        collectionsOfGamers.sort(j); // sorting the linked list, the parameter is choosing which difficult needs to be sorted.
        cout << setw(25) << "RANK" << setw(25) << "NAME" << setw(25) << "REG NO" << setw(25) << "SCORE" << setw(25) << "DIFFICULTY\n";
        int i = 1;
        for(auto itr = collectionsOfGamers.begin(); itr != collectionsOfGamers.end() && i < 11; itr++)
        {
            if((*itr).getRegNo() == curGamer->getRegNo())
            {
                SetConsoleTextAttribute(hConsole, 23);
            }
            cout << endl << setw(25) << i++ << setw(25) << toUpper((*itr).getName()) << setw(25) << (*itr).getRegNo() << setw(25) << (*itr).getFinalScore(j) << setw(25) << toUpper(difficulty[j]) << endl;    
            
                SetConsoleTextAttribute(hConsole, 7);    
        }
        cout<<'\n';
        system("pause"); //to display each score one at a time
    }
    mainCollectionsOfGamers = collectionsOfGamers;
}

//main method
// to change what method you want to change the way top 10 is printed, you can uncomment the line of code 725
int main()
{
    system("cls"); //clear terminal
    
    //variables
    MyLinkedList<Gamer>         collectionsOfGamersLinkedList; //custom iterator container
    vector<Gamer> * collectionsOfGamers =  new vector<Gamer>;
    vector<string> * userDetails        = new vector<string>; 
    Manager * manager                   =            nullptr;
    GetLine * myGet                     =        new GetLine;
    string  name;
    Gamer * gamer                       =            nullptr;
    const char * wordFile;                
    const char * path                   =        "users.txt";
    int  choice                         =                  0;
    bool   loop                         =               true;

    difficulty[0] = "easy";
    difficulty[1] = "medium";
    difficulty[2] = "high";

    /**
     * @brief path gets the path of word file
     * if it doesnt exit, it creates and assigns a default value sample to it.
     */
    ifstream ifs("path.txt");
    string line;
    if(!ifs.good())
        IOFile::quickAdd("path.txt", "sample.txt");
     getline(ifs, line);
     wordFile = line.data();
        
    ifs.close();
    if(gamer== nullptr || manager == nullptr)
    {
        // loops until the input has the correct format.
        while(splitter(nameFormatting(myGet->myGetLine("Enter Username (Jane Doe): ",name,false)),' ')->size() != 2) //making sure the user input is two words
            cout << "\nINVALID NAME FORMAT\n\n";
        //name = "Monty Python";
        userDetails = readFile(path,name,' ',nullptr,false); // stores line from file into a vector
        if(userDetails == nullptr) // if it's nullptr then there's no data found for the user then it goes ahead to create a player and store in file
        {
            choice = Random().random(10000,99999); // creates random number for regNo
            while(readFile(path,to_string(choice),' ', nullptr,false) == nullptr) //loop is ensure the regNo create isn't for a member
                if(IOFile::addLine((to_string(choice) + " " + name),path) == 0)
                {
                    gamer =  login<Gamer>(name); // creates a gamer object using template
                    collectionsOfGamers->push_back(*gamer); // adds player to collection
                    cout << "\nNEW GAMER ADDED!!!\n\nWELCOME " << name << "!!!\nREG NO: " << choice << "\n\n";  
                }
                else
                {
                    cout << "A\nN ERROR AS OCCURRED!!!\n\n";
                    break;
                }
        }
        else if ((userDetails->size() == 3 && userDetails->at(0).size() == 4)) // checks if it's a manager by checking the size of the data in line and the reg no
            manager = login<Manager>(name);
        else //if the vector isn't empty, gamer exist and logs gamer in
        {
            gamer = login<Gamer>(name);
            int index = 0;
            for (auto i = userDetails->begin() + 3; i != userDetails->end(); ++i) // adds score to gamer object for each difficult if they exist 
            {
                if(*i == "e")
                    index = 0;
                else if(*i == "m")
                    index =  1;
                else if(*i == "h")
                    index = 2;
                
                i++;
                gamer->addScore(stof(*i),difficulty[index]);
            }
        }
        system("pause");
    }
    
    // depending on if the usr is a gamer or manager, it displays the correct options, method handles error handling if the wrong number is inserted
    while (loop)
    {
        system("cls");
        choice  = myGet->intGetLineWithOption((gamer != nullptr ? "SELECT OPTION:\n   1) Play game \n   2) Your statistics \n   3) Display top 10 \n   4) Change name \n   5) Exit \nOption: " : "SELECT OPTION:\n   1) Reset game \n   2) Change game levels \n   3) Add another manager \n   4) Set the word file \n   5) Change name \n   6) Exit game \nOption: "),choice,(gamer != nullptr ? 5 : 6));
        system("cls");
        switch (choice)
        {
            case 1:
                if(manager != nullptr) //resets difficult word range
                {
                    IOFile::quickAdd("range.txt", "1 6 10 5 10 0");
                    cout << "\nGAME RESET SUCCESSFULLY!!!\n\n";
                    system("pause");
                }
                else if(gamer != nullptr) // loads game by calling function
                    game(gamer,myGet,wordFile);
                break;
            case 2:
                if(gamer != nullptr)
                    cout << *gamer; // displays stats from overloading
                else if(manager != nullptr)
                {
                    int addDiff = 1;
                    line = "";
                    int num = 0;
                    while(addDiff < 7)
                    {
                        if(addDiff < 4)
                            num = myGet->intGetLine(("Enter Min Value for " + difficulty[addDiff - 1] + ": "), num);
                        else
                            num = myGet->intGetLine(("Enter Max Value for " + difficulty[addDiff - 4] + ": "), num);
                        line.append(to_string(num) + " ");
                        addDiff++;
                    }
                    IOFile::quickAdd("range.txt",line);
                }
                system("pause");
                break;
            case 3:
                if(manager != nullptr) // creates a new manager
                {
                    choice = Random().random(0,9999);
                    while(splitter(nameFormatting(myGet->myGetLine("Enter New Manager's Name (Jane Doe): ",name,false)),' ')->size() != 2) //check if the name input is correct
                    {
                        cout << "\nINVALID NAME FORMAT!!!\n";
                    }
                    while(readFile(path,to_string(choice),' ',nullptr,false) == nullptr) //similar to code in gamer
                        if(IOFile::addLine(((to_string(choice).size() < 4 ? (to_string(0) * (4 - choice) + to_string(choice)) : to_string(choice)) + " " + name ),path) == 0)
                            cout << "MANAGER ADDED SUCCESSFULLY!!!\n\n";
                        else
                            {
                               cout << "AN ERROR AS OCCURRED!!!";
                              continue;
                            }
                }
                else if(gamer != nullptr)
                {
                    //printTopTen(*collectionsOfGamers,path,gamer);
                   printTopTen(collectionsOfGamersLinkedList,path,gamer);
                }
                break;
            case 4:
                if(gamer != nullptr)
                {
                    while(splitter(nameFormatting(myGet->myGetLine("Enter New Name (Jane Doe): ",name,false)),' ')->size() != 2) //making sure the user input is two words
                        cout << "\nINVALID NAME FORMAT\n\n";
                    changeName(name, gamer);
                }
                else
                {
                    //wordFile = myGet->myGetLine("Enter New Word File Path: ", name, true).data();
                    IOFile::quickAdd("path.txt", myGet->myGetLine("Enter New Word File Path: ", name, true));
                }
            break;
            case 5: 
                if(gamer == nullptr)
                {
                    while(splitter(nameFormatting(myGet->myGetLine("Enter New Name (Jane Doe): ",name,false)),' ')->size() != 2) //making sure the user input is two words
                        cout << "\nINVALID NAME FORMAT\n\n";
                    changeName(name, manager);
                }
                else
                 loop = false;
                break;
            case 6:
                loop = false;
                break;
        }
    }
    cout << "GOOD BYE!!!\n";
}