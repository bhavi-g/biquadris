#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "board.h"
#include "window.h"

class Board; //forward declaration;

class Graphics {
    
    int cellSize = 25; // Each cell is 25x25 pixels
    int spacing = 50;  // Space between Player 1 and Player 2 boards

public:
    std::unique_ptr<Xwindow> window;
    Graphics();                                // Initialize graphics with default dimensions
    void renderBoard(const Board& board);      // Draw the graphical representation of the board
    void renderScores(std::shared_ptr <Player> player1, std::shared_ptr <Player> player2); // Draw scores for both players
};

#endif
