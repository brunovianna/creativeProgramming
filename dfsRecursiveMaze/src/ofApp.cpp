#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(20); // Dark background
    ofSetWindowTitle("Recursive Maze Generator (Press Spacebar)");

    // Set up grid dimensions
    cols = 40;
    rows = 30;
    
    // Calculate cell size to fit the window
    // We use the smaller dimension to ensure it fits
    cellSize = (ofGetWidth() / (float)cols < ofGetHeight() / (float)rows ? ofGetWidth() / (float)cols : ofGetHeight() / (float)rows );

    // Initialize the grid
    resetGrid();
    
    // Start the recursive generation from the top-left corner
    generateMaze(0, 0);
}

//--------------------------------------------------------------
void ofApp::resetGrid(){
    // Clear any existing grid data
    grid.clear();

    // Resize the grid to the correct dimensions
    grid.resize(cols);
    for (int i = 0; i < cols; i++) {
        grid[i].resize(rows);
        
        // Initialize each cell with its coordinates
        for (int j = 0; j < rows; j++) {
            grid[i][j].x = i;
            grid[i][j].y = j;
        }
    }
}

//--------------------------------------------------------------
// This is the core RECURSIVE algorithm
void ofApp::generateMaze(int x, int y) {
    
    // 1. Mark the current cell as visited
    Cell& current = grid[x][y];
    current.visited = true;

    // 2. Get all unvisited neighbors
    vector<Cell*> neighbors = getUnvisitedNeighbors(x, y);

    // 3. Randomize the order of neighbors
    ofShuffle(neighbors);

    // 4. Visit each neighbor in the random order
    for (Cell* neighbor : neighbors) {
        
        // This check is slightly redundant since getUnvisitedNeighbors
        // only returns unvisited ones, but it's safe.
        if (!neighbor->visited) {
            
            // 5. Remove the wall between the current cell and the neighbor
            removeWall(&current, neighbor);
            
            // 6. RECURSE: Call this function on the neighbor.
            // This adds the neighbor to the "call stack" and pauses
            // execution of *this* function call until it returns.
            generateMaze(neighbor->x, neighbor->y);
        }
    }
    
    // 7. BASE CASE: If there are no unvisited neighbors, the loop
    //    finishes, the function ends, and execution "backtracks"
    //    to the function that called this one (the previous cell).
}

//--------------------------------------------------------------
vector<Cell*> ofApp::getUnvisitedNeighbors(int x, int y) {
    vector<Cell*> neighbors;

    // Check Top
    if (y > 0 && !grid[x][y - 1].visited) {
        neighbors.push_back(&grid[x][y - 1]);
    }
    // Check Right
    if (x < cols - 1 && !grid[x + 1][y].visited) {
        neighbors.push_back(&grid[x + 1][y]);
    }
    // Check Bottom
    if (y < rows - 1 && !grid[x][y + 1].visited) {
        neighbors.push_back(&grid[x][y + 1]);
    }
    // Check Left
    if (x > 0 && !grid[x - 1][y].visited) {
        neighbors.push_back(&grid[x - 1][y]);
    }

    return neighbors;
}

//--------------------------------------------------------------
void ofApp::removeWall(Cell* a, Cell* b) {
    // Calculate the difference in x and y
    int dx = a->x - b->x;
    int dy = a->y - b->y;

    if (dx == 1) { // 'a' is to the right of 'b'
        a->walls[3] = false; // Remove 'a's left wall
        b->walls[1] = false; // Remove 'b's right wall
    } else if (dx == -1) { // 'a' is to the left of 'b'
        a->walls[1] = false; // Remove 'a's right wall
        b->walls[3] = false; // Remove 'b's left wall
    }

    if (dy == 1) { // 'a' is below 'b'
        a->walls[0] = false; // Remove 'a's top wall
        b->walls[2] = false; // Remove 'b's bottom wall
    } else if (dy == -1) { // 'a' is above 'b'
        a->walls[2] = false; // Remove 'a's bottom wall
        b->walls[0] = false; // Remove 'b's top wall
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    // Nothing to do here, the maze is generated in setup()
}

//--------------------------------------------------------------
void ofApp::draw(){
    // We can center the maze for a nicer look
    ofPushMatrix();
    float mazeWidth = cols * cellSize;
    float mazeHeight = rows * cellSize;
    ofTranslate((ofGetWidth() - mazeWidth) / 2.0, (ofGetHeight() - mazeHeight) / 2.0);

    // Draw all cells
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            grid[i][j].draw(cellSize);
        }
    }
    
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') {
        // Reset the grid and generate a new maze
        resetGrid();
        generateMaze(0, 0);
    }
}