#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <memory>
#include <string>
#include "block.h"
#include "cell.h"
#include "level.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"

class Player{
    public:
    std::vector<std::vector<Cell>> grid;
    std::shared_ptr <Block> curBlock;
    std::shared_ptr <Block> nextBlock;
    std::vector<std::shared_ptr <Block>> prevBlocks;
    int score;
    int level;
    bool hasLost;
    bool isBlind;
    bool hasSpecial;
    int blocksDropped;//number of blocks dropped without clear
    std::shared_ptr <Level> pLevel;
    std::string seqfile;
    Player(int lv, std::string f);
    
    
    void reset(int lv); //resets player members to default values
    void changeLevel(int lv);
    int getLevel() { return level; }
    void getNextBlock(); //gets players next block from level 
    void placeBlock(); //updates player when its block is placed
    void addBlock(); //adds cells from current block to grid
    void removeBlock(); //removes current block cells from grid
    void forceBlock(char b); //players current block to become provided block
    void checkLost(); //checks if current lock overlaps with filled grid cells
    void makeBlind(bool b); // makes coluns 3-9 and rows 3-12 of grid blind
    void makeSpecialHeavy(); // sets current block to special heavy
};

#endif
