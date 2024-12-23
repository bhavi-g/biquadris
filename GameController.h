#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <string>
#include <memory>
#include "board.h"
#include "player.h"
#include "window.h"
#include "graphics.h"

class GameController {
    bool isTextOnly; // Text-only mode indicator
    int highScore;   // Track the game's high score
    std::shared_ptr <Player> currentPlayer; // Pointer to the active player
    std::shared_ptr <Player> player1; // Player 1
    std::shared_ptr <Player> player2; // Player 2
    Board gameBoard; // Reference to the shared game board
    Graphics graphics;
    void processCommand(std::istream &i); // Handle a single command

public:
    GameController(int lv, bool textOnly, std::string f1, std::string f2);

    void startGame(); // Main game loop
    void restartGame(); // Restart the game
    void switchTurns(); // Switch turns between players
    void checkWin();
    void promptAbility(std::istream &i);
    ~GameController() = default;
};

#endif 
