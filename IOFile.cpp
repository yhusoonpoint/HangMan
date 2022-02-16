#include "IOFile.h"
#include <iostream>
#include <fstream>
#include <set>

using namespace std;

// replaces a line by looping and searching for the word
// once found it adds to set and the rest of the line
// then the set is copied into the file
bool IOFile::replaceLineInFile(const char * path, const std::string & word, std::string & newWord)
{

    ifstream * ifs = new ifstream(path);
    string * line = new string;
    if(!(*ifs))
    {
        cout << "FILE OPENING ERROR!!!" << endl;
        return false;
    }
    set<string> copyData;
    while (getline(*ifs, *line)) 
    {
        if((*line).find(word) != string::npos) 
        { 
            *line = newWord;
        }
        copyData.insert(*line);
    }

    ofstream ofs(path);
    if( !(ofs))
    {
        cout << "FILE OPENING ERROR!!!" << endl;
        return false;
    }
    for(auto & i : copyData)
        if(!i.empty())
            ofs << i << '\n';
    

    copyData.clear();
    delete line;
    return true;   
}

//adds line to the end of file
int IOFile::addLine(const string & data,const char * path)
{
    ofstream * ofs = new ofstream;
    (*ofs).open(path,std::ios_base::app);
    if(!(*ofs << data << endl)){
        delete ofs;
        return 1;
    }
    delete ofs;
    return 0;
}

//creates path if it doesnt exist and replace all words
void IOFile::quickAdd(const char * path, const std::string & word)
{
    ofstream ofs(path);
    ofs << word;
    ofs.close();    
}