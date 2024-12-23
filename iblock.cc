#include "iblock.h"
#include <iostream>
#include <algorithm>

// Default constructor
IBlock::IBlock(int level): Block(level), rotationState(0) {
    // Initialize in the horizontal orientation at the bottom-left corner
    structure = {
        Cell(0, 3, 'I'), // Positioned horizontally
        Cell(1, 3, 'I'),
        Cell(2, 3, 'I'),
        Cell(3, 3, 'I'),
    };

    blockGrid =  {
        {'I', 'I', 'I', 'I'},
        {' ', ' ', ' ', ' '}
    };
}

// Constructor with heaviness properties
IBlock::IBlock(bool levelHeavy, int level) : Block(levelHeavy, level), rotationState(0) {
    structure = {
        Cell(0, 3, 'I'), // Positioned horizontally
        Cell(1, 3, 'I'),
        Cell(2, 3, 'I'),
        Cell(3, 3, 'I'),
    };
    blockGrid =  {
        {'I', 'I', 'I', 'I'},
        {' ', ' ', ' ', ' '}
    };
}

// Destructor
IBlock::~IBlock() {}

// Rotate the block
void IBlock::rotate(bool clockwise) {
    // Preserve the lower-left corner as the fixed point
    int baseX = structure[0].getX();
    int baseY = structure[0].getY();
    if (rotationState == 0) {
        for (int i = 1; i < 4; i++) {
            structure[i].setX(baseX);
            structure[i].setY(baseY - i);
        }
    } else {
        for (int i = 1; i < 4; i++) {
            structure[i].setX(baseX + i);
            structure[i].setY(baseY);
        }
    }
    // Update rotationState based on direction
    rotationState = (rotationState + 1) % 2; // 0 -> 1 -> 0
}

// Display the block in its current state
void IBlock::display() {
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
std::shared_ptr<Block> IBlock::cloneBlock() const {
    return std::make_shared<IBlock>(*this);
}
