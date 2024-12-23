#include "player.h"
#include <vector>
#include <memory>

Player::Player(int lv, std::string f): level{lv}, score{0}, seqfile{f}, hasLost{false}, isBlind{false}, hasSpecial{false}, blocksDropped{0}{
    for(int y = 0; y < 18; y++){
        grid.push_back(std::vector<Cell>());
        for(int x = 0; x < 11; x++){
            grid[y].push_back(Cell(x,y,' '));
        }
    }
    changeLevel(level);
    getNextBlock();
    curBlock = nextBlock;
    getNextBlock();
}

void Player::changeLevel(int lv) {
    level = lv;
    if (level < 0) { 
        level = 0;
    } else if (level > 4) {
        level = 4;
    }

    if (level == 0) {
        pLevel = std::make_shared<Level0>(seqfile);
    } else if (level == 1) {
        pLevel = std::make_shared<Level1>();
    } else if (level == 2) {
        pLevel = std::make_shared<Level2>();
    } else if (level == 3) {
        pLevel = std::make_shared<Level3>(seqfile);
    } else if (level == 4) {
        pLevel = std::make_shared<Level4>(seqfile);
    }
}

void Player::reset(int lv){
    score = 0;
    blocksDropped = 0;
    hasLost = false;
    changeLevel(lv);

    getNextBlock();
    curBlock = nextBlock;
    getNextBlock();

    for(int y = 0; y < 18; y++){
		for(int x = 0; x < 11; x++){
			grid[y][x].setFill(' ');
		}
	}
}

void Player::placeBlock(){
    for(auto c: curBlock -> structure){
        grid[c.getY()][c.getX()].setFill(c.getFill());
    }
    prevBlocks.push_back(curBlock);
    curBlock = nextBlock;
    getNextBlock();
    if(isBlind){
        makeBlind(false);
    }
    checkLost();
}

void Player::addBlock(){
    for(auto c: curBlock -> structure){
        grid[c.getY()][c.getX()].setFill(c.getFill());
    }
}

void Player::removeBlock(){
    for(auto c: curBlock -> structure){
        grid[c.getY()][c.getX()].setFill(' ');
    }
}
void Player::getNextBlock() {
    nextBlock = pLevel->createBlock();
}

void Player::forceBlock(char b) {
    if (level == 3 || level == 4) {
        switch(b){
            case 'j' : curBlock = std::make_shared<JBlock>(level, true); break;
            case 'o' : curBlock = std::make_shared<OBlock>(level, true); break;
            case 'l' : curBlock = std::make_shared<LBlock>(level, true); break;
            case 'i' : curBlock = std::make_shared<IBlock>(level, true); break;
            case 's' : curBlock = std::make_shared<SBlock>(level, true); break;
            case 'z' : curBlock = std::make_shared<ZBlock>(level, true); break;
            case 't' : curBlock = std::make_shared<TBlock>(level, true); break;  
        }
    } else {
        switch(b){
            case 'j' : curBlock = std::make_shared<JBlock>(level); break;
            case 'o' : curBlock = std::make_shared<OBlock>(level); break;
            case 'l' : curBlock = std::make_shared<LBlock>(level); break;
            case 'i' : curBlock = std::make_shared<IBlock>(level); break;
            case 's' : curBlock = std::make_shared<SBlock>(level); break;
            case 'z' : curBlock = std::make_shared<ZBlock>(level); break;
            case 't' : curBlock = std::make_shared<TBlock>(level); break;  
        }
    }
    checkLost();
}

void Player::checkLost(){
    for(auto c: curBlock -> structure){
        if(grid[c.getY()][c.getX()].isFilled()){
            hasLost = true;
        }
    }
}

void Player::makeBlind(bool b){
    isBlind = b;
    for(int y = 5; y < 15; y++ ){
        for(int x = 2; x < 9; x++){
            grid[y][x].blind(b);
        }
    }
}

void Player::makeSpecialHeavy(){
    curBlock -> setSpecialHeavy(true);
}
