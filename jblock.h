#ifndef JBLOCK_H
#define JBLOCK_H

#include "block.h"
#include <vector>
#include <string>

class JBlock : public Block {
private:
    int rotationState; // Tracks the current rotation state (0: default, 1: cw1, 2: cw2, 3: cw3)

public:
    // Constructors
    JBlock(int level); // Default constructor
    JBlock(bool levelHeavy, int level); // Overloaded constructor with heaviness

    // Destructor
    ~JBlock() override;

    // Overridden methods
    void rotate(bool clockwise) override; // Rotate the block
    void display() override; // Display the block in its current state
    std::shared_ptr<Block> cloneBlock() const override; // Create a deep copy of the block
};

#endif 
