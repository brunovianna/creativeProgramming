#pragma once

#include "ofMain.h"
#include <stack> // <-- Include the stack library

// Cell struct is identical to before
struct Cell {
    bool visited = false;
    bool walls[4] = {true, true, true, true}; // Top, Right, Bottom, Left
    int x, y;

    void draw(float cellSize) {
        float drawX = x * cellSize;
        float drawY = y * cellSize;

        ofSetColor(255);

        if (walls[0]) ofDrawLine(drawX, drawY, drawX + cellSize, drawY);
        if (walls[1]) ofDrawLine(drawX + cellSize, drawY, drawX + cellSize, drawY + cellSize);
        if (walls[2]) ofDrawLine(drawX, drawY + cellSize, drawX + cellSize, drawY + cellSize);
        if (walls[3]) ofDrawLine(drawX, drawY, drawX, drawY + cellSize);
    }
};

class ofApp : public ofBaseApp {

public:
    void setup();
    void update();
    void draw();
    void mousePressed(int x, int y, int button);
    void keyPressed(int key);

    // --- Maze Generation (Iterative) ---
    
    // This function will perform ONE step of the algorithm
    void stepMaze(); 

    // Helper functions (identical to before)
    vector<Cell*> getUnvisitedNeighbors(int x, int y);
    void removeWall(Cell* a, Cell* b);
    void resetGrid();

    // --- Maze Properties ---
    int cols, rows;
    float cellSize;
    vector<vector<Cell>> grid;
    
    // --- State Management ---
    std::stack<Cell*> history; // The explicit stack to replace recursion
    bool generationComplete;
};