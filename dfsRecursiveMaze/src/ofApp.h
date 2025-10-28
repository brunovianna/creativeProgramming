#pragma once

#include "ofMain.h"

// A struct to hold the state of each cell in the maze
struct Cell {
    bool visited = false;
    bool walls[4] = {true, true, true, true}; // Top, Right, Bottom, Left
    int x, y; // Grid coordinates

    // Helper function to draw the cell's walls
    void draw(float cellSize) {
        float drawX = x * cellSize;
        float drawY = y * cellSize;

        ofSetColor(255); // White walls

        if (walls[0]) { // Top
            ofDrawLine(drawX, drawY, drawX + cellSize, drawY);
        }
        if (walls[1]) { // Right
            ofDrawLine(drawX + cellSize, drawY, drawX + cellSize, drawY + cellSize);
        }
        if (walls[2]) { // Bottom
            ofDrawLine(drawX, drawY + cellSize, drawX + cellSize, drawY + cellSize);
        }
        if (walls[3]) { // Left
            ofDrawLine(drawX, drawY, drawX, drawY + cellSize);
        }
    }
};


class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);

    // --- Maze Generation ---
    
    // The main recursive function
    void generateMaze(int x, int y); 

    // Helper to get all valid, unvisited neighbors
    vector<Cell*> getUnvisitedNeighbors(int x, int y); 
    
    // Helper to remove the wall between two cells
    void removeWall(Cell* a, Cell* b); 

    // Helper to reset the grid
    void resetGrid();

    // --- Maze Properties ---
    int cols, rows;
    float cellSize;
    
    // The 2D grid that stores our maze
    vector<vector<Cell>> grid;
};