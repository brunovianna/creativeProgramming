#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(20);
    ofSetWindowTitle("Step-by-Step Maze Generator (Click to advance, Space to reset)");

    cols = 40;
    rows = 30;
    cellSize = (ofGetWidth() / (float)cols < ofGetHeight() / (float)rows ? ofGetWidth() / (float)cols : ofGetHeight() / (float)rows );

    // Set up the grid for the first time
    resetGrid();
}

//--------------------------------------------------------------
void ofApp::resetGrid(){
    // Clear the grid
    grid.clear();
    grid.resize(cols);
    for (int i = 0; i < cols; i++) {
        grid[i].resize(rows);
        for (int j = 0; j < rows; j++) {
            grid[i][j].x = i;
            grid[i][j].y = j;
        }
    }

    // Clear the stack
    while (!history.empty()) {
        history.pop();
    }
    
    // 1. Start the process
    Cell* start = &grid[0][0];
    start->visited = true;
    history.push(start); // Push the starting cell onto the stack
    
    generationComplete = false;
}

//--------------------------------------------------------------
// This is the new core logic, replacing the recursive function
void ofApp::stepMaze() {
    // If the stack is empty, we're done!
    if (history.empty()) {
        generationComplete = true;
        return;
    }

    // 1. Get the current cell from the top of the stack
    Cell* current = history.top();

    // 2. Get all unvisited neighbors
    vector<Cell*> neighbors = getUnvisitedNeighbors(current->x, current->y);

    // 3. Check if we have any valid neighbors
    if (!neighbors.empty()) {
        // 3a. YES: We have neighbors
        
        // Pick one at random
        Cell* next = neighbors[ofRandom(neighbors.size())];
        
        // Carve the wall between current and next
        removeWall(current, next);
        
        // Mark 'next' as visited
        next->visited = true;
        
        // Push 'next' onto the stack to be the new 'current'
        // This is the equivalent of the recursive call: generateMaze(next)
        history.push(next);
        
    } else {
        // 3b. NO: We are at a dead end. Time to backtrack.
        
        // By popping the stack, the 'current' cell in the *next*
        // step will be the one we came from.
        // This is the equivalent of the recursive function returning.
        history.pop();
    }
}

//--------------------------------------------------------------
// Helper functions are identical to the recursive version
//--------------------------------------------------------------
vector<Cell*> ofApp::getUnvisitedNeighbors(int x, int y) {
    vector<Cell*> neighbors;
    if (y > 0 && !grid[x][y - 1].visited) neighbors.push_back(&grid[x][y - 1]);
    if (x < cols - 1 && !grid[x + 1][y].visited) neighbors.push_back(&grid[x + 1][y]);
    if (y < rows - 1 && !grid[x][y + 1].visited) neighbors.push_back(&grid[x][y + 1]);
    if (x > 0 && !grid[x - 1][y].visited) neighbors.push_back(&grid[x - 1][y]);
    return neighbors;
}

void ofApp::removeWall(Cell* a, Cell* b) {
    int dx = a->x - b->x;
    if (dx == 1) { a->walls[3] = false; b->walls[1] = false; }
    else if (dx == -1) { a->walls[1] = false; b->walls[3] = false; }

    int dy = a->y - b->y;
    if (dy == 1) { a->walls[0] = false; b->walls[2] = false; }
    else if (dy == -1) { a->walls[2] = false; b->walls[0] = false; }
}
//--------------------------------------------------------------
// End of helper functions
//--------------------------------------------------------------

void ofApp::update(){
    // All logic is now driven by mouse clicks, so update is empty.
    if (ofGetMousePressed(0))
        if (!generationComplete) {
            stepMaze();
        }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushMatrix();
    float mazeWidth = cols * cellSize;
    float mazeHeight = rows * cellSize;
    ofTranslate((ofGetWidth() - mazeWidth) / 2.0, (ofGetHeight() - mazeHeight) / 2.0);

    // 1. Draw all the cells
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            grid[i][j].draw(cellSize);
        }
    }

    // 2. Highlight the "current" cell (the head of the algorithm)
    if (!history.empty()) {
        Cell* current = history.top();
        ofSetColor(0, 255, 0, 150); // Bright green, semi-transparent
        ofDrawRectangle(current->x * cellSize, current->y * cellSize, cellSize, cellSize);
    }
    
    // 3. Show a "Complete" message
    if (generationComplete) {
        ofSetColor(255);
        string msg = "Generation Complete!\nPress Spacebar to restart.";
        // Draw the text in the middle of the maze
        ofDrawBitmapString(msg, 
            (mazeWidth - 200) / 2.0, // Aprox text width
            mazeHeight / 2.0);
    }

    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    // Each mouse click calls stepMaze() once.
    // if (!generationComplete) {
    //     stepMaze();
    // }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') {
        resetGrid();
    }
    if (key =='s') {
        if (!generationComplete) {
            stepMaze();
        }
    }
}