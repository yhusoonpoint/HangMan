#ifndef _GAMER_H_
#define _GAMER_H_

#include <string>
#include <map>
#include <stdexcept>
#include "Person.h"

using namespace std;

class NoScoreException: public exception
{
	public:
    	const char * what() const noexcept override
		{
       		return "HAS NO SCORE";
    	}
};

class Gamer: public Person
{   public:
		Gamer();
        // constructor should initialise name and registration number using arguments
        // and initialise score map to be empty
        Gamer(const string &name, int regNo);

	   // method to return registration number
	   int getRegNo() const;

	   // method to add the score to the map
	   void addScore(float score, const string & difficulty);

	   // method to update the accumulative score map
	   // should throw NoScoreException if gamer has no score yet
	   bool updateAccumulativeScore(const string & difficulty,float score);

	   // method to iterate through scores and calculate the average
	   void averageCalculation();

		// stores accumulated store for easy acess
	   float getFinalScore( int position) const;

		//overloading operator for sorting
	   bool operator<( const Gamer & other) const;

	   bool operator>(const  Gamer & other) const ;

		//overloading for sorting purpose
	   Gamer operator-(const Gamer & other) const;

		// used for sorting to know what score needs to be sorted
	   void setIndex(int index);

		//updates file in case a gamer changes name or has  new score
	   void updateFile();

    private:
	    int regNo;
	    int index = 0;
	    string name;
	    float value;
	    multimap<string,float> scores;  // scores map, with each in range 0.0 to 100.0, and an
	   							//associated level of difficulty 
	    map<string,float> accumulative_scores;  // scores map
	   							//associated level of difficulty 
	    map<string,float> average_scores;  // scores map
	   							//associated level of difficulty 
		float finalScore[3]; //stores accumulated score

    	// friend function to output details of gamer to stream
    	// should output name, regNo, and minimum, maximum and average score on a single line
    	// if the gamer has no scores "has no scores" should be output instead of the scores
    	friend ostream& operator<<(ostream &str, const Gamer &s);
};

#endif
