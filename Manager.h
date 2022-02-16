#ifndef _MANAGER_H_
#define _MANAGER_H_

#include <string>
#include <vector>
#include <stdexcept>
#include "Person.h"

using namespace std;

class Manager: public Person
{   public:
        // constructor initialise name and registration number using arguments
        Manager(const string &name, int regNo);

	   // method to return registration number
	   int getRegNo() const;

	   //changes line in file, eg name
	   //the way it works has been discussed in Gamer.cpp	
	   void updateFile();
    private:
	   int regNo;
	   string name;
};

#endif
