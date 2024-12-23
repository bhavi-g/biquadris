#ifndef IBLOCK_H
#define IBLOCK_H

#include "block.h"
#include <vector>
#include <string>

class IBlock : public Block {
private:
    int rotationState; // Tracks the current rotation state (0: horizontal, 1: vertical)

public:
    // Constructors
    IBlock(int level); // Default constructor
    IBlock(bool levelHeavy, int level); // Overloaded constructor with heaviness

    // Destructor
    ~IBlock() override;

    // Overridden methods
    void rotate(bool clockwise) override; // Rotate the block
    void display() override; // Display the block in its current state
    std::shared_ptr<Block> cloneBlock() const override; // Create a deep copy of the block
};

#endif // IBLOCK_H
