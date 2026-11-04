#include <vector>
#include "ofMain.h"

#ifndef CA_H_INCLUDED
#define CA_H_INCLUDED

class CA
{

public:

    void generateCA();
    int rules(int a, int b, int c);
    void displayGeneration(int gen);
    void displayAllGenerations();
    void nextStep();
    CA() {};
    CA(int); //width
	CA(int, float); //width and randomness of first line
	CA(int, float, int[8]); //width, randomness of first line and ruleset

private:

    std::vector<int> cells;
    std::vector<std::vector<int> > generations;
	int ruleset[8] = { 0, 1, 0, 1, 1, 0, 1, 0 }; // Rule 90
    int cellWidth;
    int colCount;
    // The CA should keep track of how many generations.
    int generation;

};


#endif // CA_H_INCLUDED
