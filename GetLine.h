#ifndef _GETLINE_H_
#define _GETLINE_H_

#include <string>

using namespace std;

class GetLine
{   public:
        // gets user string and checks if it doesnt contain unwanted values 
        // if passwoedEntry is true, any thing is accepted as input
        string & myGetLine(const string & message, string & value, bool passwordEntry);
        string & myGetChar(const string & message, string & value, bool passwordEntry);
        // gets user int using isdigit
        int & intGetLine(const string & message, int & value);
        // gets user int and only accepts values within the option value eg 0 - 6(option)
        int & intGetLineWithOption(const string & message, int & value, int option);
        // checks if any input is digit
        static bool isDigit(const string & value);
};

#endif
