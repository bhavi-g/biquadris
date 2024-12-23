#include "block.h"
#include <iostream>

// Default constructor initializes the block without heavy properties
Block::Block(int level) : isLevelHeavy(false), isSpecialHeavy(false), level(level) {}

// Constructor with heavy properties
Block::Block(bool levelHeavy, int level)
    : isLevelHeavy(levelHeavy), isSpecialHeavy(false), level(level) {}

// Destructor
Block::~Block() {}

//Getters
bool Block::getLevelHeavy() const {
    return isLevelHeavy;
}
bool Block::getSpecialHeavy() const {
    return isSpecialHeavy;
}

// Setters for heavy properties
void Block::setLevelHeavy(bool h) {
    isLevelHeavy = h;
}

void Block::setSpecialHeavy(bool h) {
    isSpecialHeavy = h;
}

void Block::moveHorizontal(int dir) {
    for (int i = 0; i < structure.size();i++) {
        if (dir == 0) {
            structure[i].setX(structure[i].getX() - 1);
        } else {
            structure[i].setX(structure[i].getX() + 1);
        }
    }
}

void Block::moveDown() {
    for (int i = 0; i < structure.size(); i++) {
        structure[i].setY(structure[i].getY() + 1);
    }
}
