#include "GetLine.h"
#include <iostream>
#include <algorithm>

//checks if it's int or not
bool GetLine::isDigit(const string & value)
{
    return std::all_of(value.cbegin(), value.cend(), [](const char & i){ return std::isdigit(i) != 0; });
}

// Getline function that recurs if the input is empty 
// gets input via char and converts to string, so it can be passed around easily
string & GetLine::myGetLine(const string & message, string & value, bool passwordEntry)
{
    char * temp = new char[256];
    cout << message;
    cin.getline(temp,256);
    value = temp;
    delete [] temp;
    if( value.empty() || value == " " || (!passwordEntry && value.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") != string::npos)) // makes sure no special character is written
    {
        cout << "\nError, Please Try Again.\n\n";
        value = myGetLine(message,value, passwordEntry);
    }
    return value;
}
string & GetLine::myGetChar(const string & message, string & value, bool passwordEntry)
{
    while(myGetLine(message,value,passwordEntry).size() > 1)
    {
        cout << "\nError, Please Try Again.\n\n";
    }
    return value;
}
/*
    Function to display message and ask for int
    loop makes sure an int is being entered.
*/
int & GetLine::intGetLine(const string & message, int & value)
{ 
    string * tempValue = new string;
    *tempValue = myGetLine(message,*tempValue,true);
    while(!isDigit(*tempValue))
    {
        cout << "\nError, Please Try Again.\n\n";
        *tempValue =  myGetLine(message,*tempValue,true);
    }
    return value = stoi(*tempValue);    
}
/*
    Function to display message and ask for int
    loop makes sure an int is being entered.
*/
int & GetLine::intGetLineWithOption(const string & message, int & value, const int option)
{ 
    string * tempValue = new string;
    *tempValue = myGetLine(message,*tempValue,true);
    while(!isDigit(*tempValue) || stoi(*tempValue) < 1 || stoi(*tempValue) > option)
    {
        cout << "\nError, Please Try Again.\n\n";
        *tempValue =  myGetLine(message,*tempValue,true);
    }
    return value = stoi(*tempValue);    
}


