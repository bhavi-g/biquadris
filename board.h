#ifndef BOARD_H
#define BOARD_H

#include "player.h"
#include "cell.h"
#include "block.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "tblock.h"
#include "sblock.h"
#include "zblock.h"
#include "graphics.h"
#include <memory>

class Graphics; //forward declaration

class Board{
    
public:
    std::shared_ptr <Player> player1;
    std::shared_ptr <Player> player2;
    Board(std::shared_ptr <Player> player1, std::shared_ptr <Player> player2, Graphics *g);
    Graphics *graphics;
    int highScore = 0;
    
    // displays board
    void printBoard(bool hasGraphic);
    void resetBoard(int p1Level, int p2Level);

    //movement functions
    bool moveDown(std::shared_ptr <Player>& player);
    bool moveLeft(std::shared_ptr <Player>& player);
    bool moveRight(std::shared_ptr <Player>& player);
    bool rotate(std::shared_ptr <Player>& player, bool clockwise);

    //checks if moving block would collide with a placed block
    bool checkDown(std::shared_ptr <Player>& player);
    bool checkLeft(std::shared_ptr <Player>& player);
    bool checkRight(std::shared_ptr <Player>& player);
    bool checkRotate(std::shared_ptr <Player>& player, bool clockwise);

    //removes the cells from a block from a players grid
    void replaceCells(std::shared_ptr <Player>& player, Block* remove);

    //drops players current block
    void drop(std::shared_ptr <Player>& player);

    //clears any full rows on the grid and updates score
    void clearLines(std::shared_ptr <Player>& player);

    //drops 1x1 cell in level 4 if 5 block places without clear
    void dropStar(std::shared_ptr <Player>& player);
};

#endif
