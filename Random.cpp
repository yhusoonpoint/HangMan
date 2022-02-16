#include "Random.h"
#include <random>

using namespace std;

//method to generate random numbers within given range
int & Random::random(int min, int max)
{
    random_device rand; // obtain a random number from hardware
    mt19937 generate(rand()); // seed the generator
    uniform_int_distribution<int> generateRandom(min, max); // define the range
    int * temp =  new int;
    *temp = generateRandom(generate); //generates random
    return *temp; // returns random
}