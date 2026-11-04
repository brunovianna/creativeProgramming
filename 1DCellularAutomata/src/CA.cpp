#include "CA.h"
#include <iostream>
#include <string>

CA::CA(int cellW)
{
	//make middle cell 1
    cellWidth = cellW;
    colCount = ofGetWidth()/cellWidth;
    cells.assign(colCount,0);
    generation = 0;
}


CA::CA(int cellW, float randomness) {
	cellWidth = cellW;
	colCount = ofGetWidth() / cellWidth;
	cells.assign(colCount, 0);
	generation = 0;
	for (int i = 0; i < colCount; i++) {
		if (ofRandom(1) < randomness) {
			cells[i] = 1;
		}
	}
}

CA::CA(int cellW, float randomness, int _rules[8]) {
	cellWidth = cellW;
	colCount = ofGetWidth() / cellWidth;
	cells.assign(colCount, 0);
	generation = 0;
	for (int i = 0; i < colCount; i++) {
		if (ofRandom(1) < randomness) {
			cells[i] = 1;
		}
	}
	for (int i = 0; i < 8; i++) {
		ruleset[i] = _rules[i];
	}
}

void CA::generateCA()
{
    if(generation==0)
    {
        cells[colCount/2] = 1;
    }
    else
    {
        std::vector<int> nextgen(colCount,0); // initialise a vector of ints all with value 0
        for (int i = 1; i < cells.size()-1; i++)
        {
            int left   = cells[i-1];
            int me     = cells[i];
            int right  = cells[i+1];
            nextgen[i] = rules(left, me, right);
        }
        cells = nextgen;
    }
    // Erase the first record if we have filled the max height
    if(generations.size() > ofGetHeight()/cellWidth) generations.erase(generations.begin());

    generations.push_back(cells);
    generation++;
    //std::cout << "Generate gen: " << generation << ".\n";
}

void CA::displayAllGenerations()
{
    for(int i = 0; i < generations.size(); i++)
    {
        displayGeneration(i);
    }
}

void CA::nextStep()
{
   // if(generation < ofGetHeight()/cellWidth)
   // {
        generateCA();
   // }
}

int CA::rules(int a, int b, int c)
{

    std::stringstream sstm;
    sstm << a << b << c;
    string result = sstm.str();
    int decimal = 0;
    for(int counter = 0; counter < result.size(); counter++)
    {
        if(result.c_str()[counter] == '1')
            decimal += pow(2, counter);
    }

   // std::cout << "Rules value: " << a << b << c << " Decimal: " << decimal << ".\n";
    return ruleset[decimal];
}

void CA::displayGeneration(int gen)
{
    //std::cout << "Display gen: " << generation << ".\n";

    vector<int> genCells = generations[gen];

    for (int i = 0; i < genCells.size(); i++)
    {
        if (genCells[i] == 1)
        {
            ofSetColor(0,0,0,255);
        }
        else
        {
            ofSetColor(255,255,255,255);
        }
        // Set the y-location according to the generation.
        ofRect(i*cellWidth, gen*cellWidth, cellWidth, cellWidth);
    }
}
