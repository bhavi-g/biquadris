#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <memory>
#include "cell.h"

class Block {
    
protected:
    bool isLevelHeavy;           // Indicates level-based heavy behavior
    bool isSpecialHeavy;         // Indicates special heavy behavior
public:
    std::vector<Cell> structure; // Block's cells (relative to its origin)
    std::vector<std::vector<char>> blockGrid; // Grid of chars used for printing next block in board
    int level;
    // Constructors
    Block(int level); // Default constructor
    Block(bool levelHeavy, int level); // Overloaded constructor

    virtual ~Block(); // Destructor

    // Pure virtual methods to be implemented by derived classes
    virtual void rotate(bool clockwise) = 0; // Rotate block
    virtual void display() = 0; // Render the block
    virtual  std::shared_ptr<Block> cloneBlock() const = 0; // Create a clone of the block

    // Getters
    bool getLevelHeavy() const;
    bool getSpecialHeavy() const;
    const std::vector<Cell>& getStructure(); // Get the structure
    char getBlockType(); // Get the block type from the first Cell
    //setters
    void setLevelHeavy(bool h);
    void setSpecialHeavy(bool h);
    void moveHorizontal(int dir); // dir = 0, translate left, dir = 1, translate right
    void moveDown();
};

#endif
