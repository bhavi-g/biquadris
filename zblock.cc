#include "zblock.h"
#include <iostream>
#include <algorithm>

// Default constructor
ZBlock::ZBlock(int level) : Block(level), rotationState(0) {
    // Initialize in the default orientation at the bottom-left corner
    structure = {
        Cell(0, 2, 'Z'), Cell(1, 2, 'Z'), 
                         Cell(1, 3, 'Z'), Cell(2, 3, 'Z')
    };

    blockGrid =  {
        {'Z', 'Z', ' ', ' '},
        {' ', 'Z', 'Z', ' '}
    };
}

// Constructor with heaviness properties
ZBlock::ZBlock(bool levelHeavy, int level) : Block(levelHeavy, level), rotationState(0) {
    structure = {
        Cell(0, 2, 'Z'), Cell(1, 2, 'Z'), 
                         Cell(1, 3, 'Z'), Cell(2, 3, 'Z')
    };

    blockGrid =  {
        {'Z', 'Z', ' ', ' '},
        {' ', 'Z', 'Z', ' '}
    };
}

// Destructor
ZBlock::~ZBlock() {}

// Rotate the block
void ZBlock::rotate(bool clockwise) {
    if (rotationState == 0) {
        structure[0].setX(structure[1].getX() + 1);
        structure[0].setY(structure[1].getY() - 1);
        structure[2].setY(structure[2].getY() - 1);
        structure[2].setX(structure[2].getX() - 1);
        structure[3].setX(structure[3].getX() - 2);
    } else {
        structure[0].setX(structure[1].getX() - 1);
        structure[0].setY(structure[1].getY() + 1);
        structure[2].setY(structure[2].getY() + 1);
        structure[2].setX(structure[2].getX() + 1);
        structure[3].setX(structure[3].getX() + 2);
    }
    // Update rotationState based on direction
    rotationState = (rotationState + 1) % 2; // 0 -> 1 -> 0
    
}

// Display the block in its current state
void ZBlock::display() {
    const int gridHeight = 6; // Fixed grid height to include spaces above the block
    const int gridWidth = 10; // Adjust as needed for horizontal blocks
    char grid[gridHeight][gridWidth];

    // Initialize the grid with spaces
    for (int i = 0; i < gridHeight; ++i) {
        for (int j = 0; j < gridWidth; ++j) {
            grid[i][j] = ' ';
        }
    }

    // Fill in the cells occupied by the block
    for (auto& cell : structure) {
        int x = cell.getX();
        int y = cell.getY();
        if (y >= 0 && y < gridHeight && x >= 0 && x < gridWidth) {
            grid[y][x] = cell.getFill(); // Note: grid[y][x] to match row-major order
        }
    }

    // Determine the lowest row containing the block
    int lowestRow = gridHeight - 1;
    for (int i = gridHeight - 1; i >= 0; --i) {
        bool rowHasBlock = false;
        for (int j = 0; j < gridWidth; ++j) {
            if (grid[i][j] != ' ') {
                rowHasBlock = true;
                break;
            }
        }
        if (rowHasBlock) {
            lowestRow = i;
            break;
        }
    }

    // Print the grid from top to the lowest row containing the block
    for (int i = 0; i <= lowestRow; ++i) {
        for (int j = 0; j < gridWidth; ++j) {
            std::cout << grid[i][j];
        }
        std::cout << std::endl;
    }
}

// Clone the block
std::shared_ptr<Block> ZBlock::cloneBlock() const {
    return std::make_shared<ZBlock>(*this);
}
