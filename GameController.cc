#include "GameController.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cctype>

GameController::GameController(int lv, bool textOnly, std::string f1, std::string f2)
    : isTextOnly{textOnly}, graphics{Graphics()}, gameBoard{Board(std::make_shared<Player>(lv, f1), std::make_shared<Player>(lv, f2), &graphics)} {
    player1 = gameBoard.player1;
    player2 = gameBoard.player2;
    currentPlayer = player1;
}

void GameController::startGame() {
    
    if (!isTextOnly) {
        gameBoard.printBoard(true);
    } else {
        gameBoard.printBoard(false);
    }
    while (true) {
        processCommand(std::cin);
       
        if (!isTextOnly) { 
            gameBoard.printBoard(True);
        } else {
            gameBoard.printBoard(false);
        }
        checkWin();
        /* // Display the updated game board
        gameBoard->display(isTextOnly); */
        if (std::cin.eof()) {
            break;
        }
    }
}

void GameController::processCommand(std::istream &in) {
    std::string input;
    std::cout << "Player " << (currentPlayer == player1 ? "1" : "2") << "'s turn. Enter command: \n";
    int multiplier = 1;
    int n;
    in >> n;
    // Check for a multiplier
    if (in) {
        multiplier = n;
        std::getline(in, input);
        if (input == "" || input[0] == ' ') {
            std::cerr << "Need command after multiplier." << std::endl;
            return;
        }
    } else {
        in.clear();
        if (!(in >> input)) {
            return;
        }
    }
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    std::string cw = "clockwise";
    std::string ccw = "counterclockwise";
    std::string norand = "norandom";
    std::string rand = "random";
    std::string restart = "restart";
    std::string sequence = "sequence";

    if (input == "left" || input == "lef") {
        for (int i = 0; i < multiplier; i++) 
        { 
            if (gameBoard.moveLeft(currentPlayer)) {
                promptAbility(in);
                switchTurns();
                break;
            } 
        }
    } else if (input == "right" || input == "ri" || input == "rig" || input == "righ") {
        for (int i = 0; i < multiplier; i++) 
        { 
            if (gameBoard.moveRight(currentPlayer)) {
                promptAbility(in);
                switchTurns();
                break;
            } 
        }
    } else if (input == "down" || input == "do" || input == "dow") {
        for (int i = 0; i < multiplier; i++) 
        { 
            if (gameBoard.moveDown(currentPlayer)) {
                promptAbility(in);
                switchTurns();
                break;
            } 
        }
    } else if (input == "drop" || input == "dr" || input == "dro") {
        for (int i = 0; i < multiplier; i++) { gameBoard.drop(currentPlayer); }
        promptAbility(in);
        switchTurns();
    } else if (input.substr(0, 2) == "cl"  && cw.find(input) != std::string::npos) {
        for (int i = 0; i < multiplier; i++) { 
            if(gameBoard.rotate(currentPlayer, true)) {
                promptAbility(in);
                switchTurns();
                break;
            }
        }
    } else if (input.substr(0, 2) == "co"  && ccw.find(input) != std::string::npos) {
        for (int i = 0; i < multiplier; i++) { 
            if(gameBoard.rotate(currentPlayer, false)) {
                promptAbility(in);
                switchTurns();
                break;
            }
        }
    } else if (input == "levelup" || input == "levelu") {
        for (int i = 0; i < multiplier; i++) { currentPlayer->changeLevel(currentPlayer->getLevel() + 1); }
    } else if (input == "leveldown" || input == "leveld") {
        for (int i = 0; i < multiplier; i++) { currentPlayer->changeLevel(currentPlayer->getLevel() - 1); }
    } else if (input.substr(0, 1) == "n"  && norand.find(input) != std::string::npos) {
        std::string file;
        if (in >> file) { 
            currentPlayer->pLevel->removeRandom(file);
        } else {
            std::cerr << "Must specificy file name" << std::endl;
        }
    } else if (input.substr(0, 2) == "ra"  && rand.find(input) != std::string::npos) {
        currentPlayer->pLevel->makeRandom();
    } else if (input.substr(0, 2) == "re"  && restart.find(input) != std::string::npos) {
        restartGame();
    } else if (input == "i" || input == "j" || input == "l" || input == "o" || input == "s" || input == "t" || input == "z") {
        currentPlayer->forceBlock(input[0]);
    } else if (input.substr(0, 1) == "s"  && sequence.find(input) != std::string::npos) {
        std::string file;
        if (in >> file) { 
            std::ifstream f{file};
            while (!f.eof()) {
                processCommand(f);
                if (!isTextOnly) { 
                    gameBoard.printBoard(True);
                } else {
                    gameBoard.printBoard(false);
                }
            }
        } else {
            std::cerr << "Must specificy file name" << std::endl;
        }
    } else {
        std::cerr << "Invalid command: " << input << std::endl;
    }
}

void GameController::switchTurns() {
    currentPlayer = (currentPlayer == player1) ? player2 : player1;
}

void GameController::restartGame() {
    std::cout << "Game restarted.\n";
    gameBoard.resetBoard(player1->level, player2->level);
    currentPlayer = player1;
}

void GameController::checkWin() {
    if (player1->hasLost) {
        std::cout << "Player 2 has won! Enter \"restart\" to replay" << std::endl;
        if (!isTextOnly) {
            graphics.window->drawString(10, 200, "Player 2 has won! Enter \"restart\" to replay");
        }
    } else if (player2->hasLost) {
        std::cout << "Player 1 has won! Enter \"restart\" to replay" << std::endl;
        if (!isTextOnly) {
            graphics.window->drawString(350, 200, "Player 1 has won! Enter \"restart\" to replay");
        }
    }
}

void GameController::promptAbility(std::istream &i) {
    if (currentPlayer->hasSpecial) {
        std::string blind = "blind";
        std::string force = "force";
        std::string heavy = "heavy";
        std::cout << "Please choose one of the following special effects: \n" << "Blind\n" << "Heavy\n" << "Force \n";
        std::string input;
        if (i >> input) {
            std::transform(input.begin(), input.end(), input.begin(), ::tolower);
            if (input.substr(0, 1) == "b"  && blind.find(input) != std::string::npos) {
                ((currentPlayer == player1) ? player2 : player1)->makeBlind(true);
                currentPlayer->hasSpecial = false;
            } else if (input.substr(0, 1) == "h"  && heavy.find(input) != std::string::npos) {
                ((currentPlayer == player1) ? player2 : player1)->makeSpecialHeavy();
                currentPlayer->hasSpecial = false;
            } else if (input.substr(0, 1) == "f"  && blind.find(input) != std::string::npos) {
                if (i >> input && (input == "i" || input == "j" || input == "l" || 
                                   input == "o" || input == "s" || input == "t" || input == "z")) {
                    ((currentPlayer == player1) ? player2 : player1)->forceBlock(input[0]);
                    currentPlayer->hasSpecial = false;
                } else {
                    std::cerr << "Invalid Block Chosen" << std::endl;
                }
            } else {
                std::cerr << "Invalid Effect" << std::endl;
            }
        }
    }
}
