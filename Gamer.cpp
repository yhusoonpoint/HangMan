#include "Gamer.h"
#include "IOFile.h"
#include <iostream>
#include <map>
#include <iomanip> 
#include <cmath>

Gamer::Gamer() : Person("DEFAULT")
{
     for(int i = 0; i < 3; i++)
        finalScore[i] = 0.0;
}

Gamer::Gamer(const string &name, int regNo) : Person(name)
{
    this->name = name;
    this->regNo = regNo;
    for(int i = 0; i < 3; i++)
        finalScore[i] = 0.0;
}

int Gamer::getRegNo() const
{
    return regNo;
}

void Gamer::addScore(float score, const string & difficulty)
{
    scores.insert({difficulty,score});
    updateAccumulativeScore(difficulty,score);
    averageCalculation();
    updateFile();
}

void Gamer::updateFile()
{    

    string line = to_string(regNo);
    string zero;
    while(zero.size() + line.size() < 5)
    {
        zero += "0";
    }
    line = zero + to_string(regNo);
    line += " " + getName();
    for(auto & i : scores)
    {
        line += " ";
        line += i.first[0];
        line += " " + to_string(i.second);
    }
    if(!IOFile::replaceLineInFile("users.txt", name, line))
    {
        cout << "\nERROR OCCURRED WHILE UPDATING FILE\n\n";
        return;
    }
    name = getName();
}

// gets the float of a map by looping and comparing
template <class T, class T2>
float & getFloat(const map<T,T2> & mp, const string difficulty)
{
    float * value = new float;
    typename map<T,T2>::const_iterator it = mp.find(difficulty);
    if (it == mp.end()) 
    {
        *value = 0;
        return *value;
    } 
    else 
    {
        *value = it->second;
        return *value;
    }
}

bool Gamer::updateAccumulativeScore(const string & difficulty,float score)
{
	try
    {
        if(scores.empty())
        {
            throw NoScoreException();
        }
        float difficultyFloat = getFloat(accumulative_scores,difficulty) + score;
        accumulative_scores.erase(difficulty);
        accumulative_scores.insert({difficulty,round(difficultyFloat)});
        if(difficulty == "easy")
            finalScore[0] = difficultyFloat;
        else if(difficulty == "medium")
            finalScore[1] = difficultyFloat;
        else if(difficulty == "high")
            finalScore[2] = difficultyFloat;
        return true;        
    }
    catch (const NoScoreException & e)
    {
        cout << endl << e.what() << endl;
    }
    return false;
}

void Gamer::setIndex(int index)
{
    this->index = index;
}

void Gamer::averageCalculation()
{
    map<string,float>::iterator it; 
    float easy = 0.0, medium = 0.0, high = 0.0;
    int difficultyCount[] = {0,0,0};
    for (it = scores.begin(); it != scores.end(); it++) 
    {
        if(it->first == "easy")
        {
            easy += it->second;
            difficultyCount[0]++;
        }
        else if (it->first == "medium")
        {
            medium += it->second;
            difficultyCount[1]++;
        }
        else if(it->first == "high")
        {
            high += it->second;
            difficultyCount[2]++;
        }
    }
    easy = easy == 0 ? easy : easy / difficultyCount[0];
    medium = medium == 0 ? medium : medium / difficultyCount[1];
    high = high == 0 ? high : high / difficultyCount[2];
    average_scores.erase("easy");
    average_scores.erase("medium");
    average_scores.erase("high");
    average_scores.insert({"easy",round(easy)});
    average_scores.insert({"medium",round(medium)});
    average_scores.insert({"high",round(high)});    
}

template <class T, class T2>
string & findInMap(const map<T,T2> & mp, const string difficulty)
{
    string * value = new string;
    typename map<T,T2>::const_iterator it = mp.find(difficulty);
    if (it == mp.end()) 
    {
        *value = to_string(0.000000);
        return *value;
    } 
    else 
    {
        *value = to_string(it->second);
        return *value;
    }
}

std::ostream & operator << (std::ostream & str, const Gamer & s)
{
    str << setw(27) <<"Name: " << s.getName() << " Reg No: " << s.getRegNo() << endl;
    if(s.scores.empty())
        return str << endl << setw(35) <<"HAS NO SCORE\n\n";
    
    map<string,float>::const_iterator it; 
    float min[3] = {0,0,0};
    float max[3] = {0, 0, 0};
    for (it = s.scores.begin(); it != s.scores.end(); it++) 
    {
        if(it->first == "easy")
        {
            if(min[0] == 0)
            {
                min[0] = it->second;
            }
            max[0] = it->second > max[0] ? it->second : max[0];
            min[0] = it->second < min[0] ? it->second : min[0];
        }
        else if(it->first == "medium")
        {
            if(min[1] == 0)
            {
                min[1] = it->second;
            }
            max[1] = it->second > max[1] ? it->second : max[1];
            min[1] = it->second < min[1] ? it->second : min[1];
        }
        else if(it->first == "high")
        {
            if(min[2] == 0)
            {
                min[2] = it->second;
            }
            max[2] = it->second > max[2] ? it->second : max[2];
            min[2] = it->second < min[2] ? it->second : min[2];
        }
    }
    str << "\n";
    str << setw(25) << "MODE" << setw(25) << "MINIMUM" << setw(25) << "MAXIMUM" << setw(25) << "AVERAGE" << setw(25) << "ACCUMULATIVE" << endl; 
    str << setw(25) << "EASY" << setw(25) << min[0] << setw(25) << max[0] << setw(25) <<findInMap<string,float>(s.average_scores, "easy") << setw(25) << findInMap<string,float>(s.accumulative_scores, "easy") << endl; 
    str << setw(25) << "MEDIUM" << setw(25) << min[1] << setw(25) << max[1] << setw(25) <<findInMap<string,float>(s.average_scores, "medium") << setw(25) << findInMap<string,float>(s.accumulative_scores, "medium") << endl; 
    str << setw(25) << "HIGH" << setw(25) << min[2] << setw(25) << max[2] << setw(25) <<findInMap<string,float>(s.average_scores, "high") << setw(25) << findInMap<string,float>(s.accumulative_scores, "high") << endl; 
   return str;

}

float Gamer::getFinalScore(int position)const
{
    return finalScore[position];
}

bool Gamer::operator<( const Gamer & other) const
{
    return (this->getFinalScore(this->index) < other.getFinalScore(other.index));
}

bool Gamer::operator>( const Gamer & other) const
{
    return (this->getFinalScore(this->index) > other.getFinalScore(other.index));
}

Gamer Gamer::operator-(const Gamer & other) const
{
    Gamer temp;
    temp.value =  getFinalScore(this->index) - other.getFinalScore(other.index);
    return temp;
}