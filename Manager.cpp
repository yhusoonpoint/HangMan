#include "Manager.h"
#include <iostream>
#include "IOFile.h"

Manager::Manager(const string &name, int regNo) : Person(name)
{
    this->name = name;
    this->regNo = regNo;
}

int Manager::getRegNo() const
{
    return regNo;
}

void Manager::updateFile()
{
    string line = to_string(regNo);
    string zero;
    while(zero.size() + line.size() < 4)
    {
        zero += "0";
    }
    line = zero + to_string(regNo);
    line += " " + getName();

    if(!IOFile::replaceLineInFile("users.txt", name, line))
    {
        cout << "\nERROR OCCURRED WHILE UPDATING FILE\n\n";
        return;
    }
    name = getName();
}